/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */
#include "stdafx.h"

#include "QtApp.h"
#include "SettingsDialog.h"

//#define GET_VARIABLE_NAME(Variable) (#Variable)

QtApp::QtApp(QWidget* parent) : QMainWindow(parent), ui(std::make_unique<Ui::QtGuiApplicationClass>()), settingsDialog(std::make_unique<SettingsDialog>(this))
{
	ui->setupUi(this);

	LoadSettings();
	SetupStyle();

	UpdateRecentFiles();
}

QtApp::~QtApp()
{
	SaveSettings();
	SaveDialog();
}

void QtApp::on_actionSettings_triggered()
{
	settingsDialog->show();
}

void QtApp::ConnectRecent(QStringList& files)
{
	// more work to check recent are valid still, just reset connected actions TODO think about
	//while (recentFileActions.size() > 0)
	for (auto size{recentFileActions.size()}; size > 0u; --size)
	{
		QObject::disconnect(recentFileActions.back().get());
		recentFileActions.pop_back();
	}

	recentFileActions.reserve(files.size());

	for (const auto& val : files)
	{
		auto& recentFileAction{recentFileActions.emplace_back(std::make_unique<QAction>(this))};

		recentFileAction->setVisible(true);
		recentFileAction->setText(val);
		recentFileAction->setData(val);

		QObject::connect(recentFileAction.get(), &QAction::triggered, this, &QtApp::OpenRecent);
		ui->menuOpen_Recent->addAction(recentFileAction.get());
	}

	recentFileActions.shrink_to_fit();
}

/*
	could avoid doing work if currentFile = files.at(0), but may as well just cleanup the recentFileActions
	in case the settings have been altered since last time the program ran (reflect fewer recent entries allowed)
*/
void QtApp::UpdateRecentFiles()
{
	auto files{GetRecentFiles()};

	if (!currentFile.isEmpty()) [[likely]]
	{
		files.push_front(currentFile);
	}

	if (files.isEmpty()) [[unlikely]]
	{
		files.push_front("<No Recent File History>");
	}
	else [[likely]]
	{
		files.removeDuplicates();

		// if max allowed recent files has been lowered, discard excess entries
		// Why does Qt use signed values for qsizetype? This is madness!
		while ((size_t)files.size() > settings->value("System/MaxRecent", 5u).value<size_t>())
		{
			files.pop_back();
		}

		settings->beginGroup("RecentFiles");
		std::ranges::for_each(settings->childKeys(), [&](auto&& key){ settings->remove(key); });
		settings->endGroup();

		// I like limiting variable scopes too much, maybe
		{
			size_t i{0u};
			std::ranges::for_each(files, [&](auto&& key){ settings->setValue(tr("RecentFiles/recent%1").arg(i), key); ++i; });
		}
		SaveSettings();
	}

	ConnectRecent(files);
}

void QtApp::LoadFile(QFile& file)
{
	currentFile = file.fileName();

	const auto tokens{currentFile.split('/')};

	//initialize local with immediate lambda call
	const auto name{[&]{ return tokens.length() ? tokens.at(tokens.length() - 1u) : tr("New File"); }()};

	// TODO move tab setup to a new function
	auto textEdit{new QTextEdit()};

	if (QTextStream in(&file); in.status() == QTextStream::Status::Ok) [[likely]]
	{
		textEdit->setPlainText(in.readAll());
		// should we check if in.readAll() succeeds? how does setPlainText handle failure TODO
	}

	// setup tabs for text alignment, default is atrocious
	QFontMetrics metrics(QApplication::font());
	textEdit->setTabStopDistance((qreal)4.0 * (qreal)metrics.horizontalAdvance(' '));

	auto mainLayout{new QVBoxLayout()};
	mainLayout->addWidget(textEdit);

	auto tab{new QWidget()};
	tab->setWindowFilePath(currentFile);
	tab->setLayout(mainLayout);

	// NOTE Qt uses int for index of widget, so don't use unsigned literals here Qt 6.0
	ui->tabWidget->insertTab(0, tab, name);
	ui->tabWidget->setCurrentIndex(0); // update view to display the new tab

	UpdateRecentFiles();
}

// sadly this can't be done in a new thread, because QtApp::LoadFile() has to be done in the QtGui thread b/c of API
void QtApp::OpenFile(QString fileName)
{
	if (fileName.isNull()) [[unlikely]]
	{
		// user cancelled action during QFileDialog
		return;
	}

	QFile file(fileName);

	if (!file.exists()) [[unlikely]]
	{
		// invalid filename, try to locate if the file was moved (or just open something else)
		fileName = QFileDialog::getOpenFileName(this, tr("Locate File..."));

		if (fileName.isNull()) [[unlikely]]
		{
			// user cancelled action during QFileDialog
			return;
		}
		else [[likely]]
		{
			file.setFileName(fileName);
		}
	}

	if (!file.open(QIODevice::ReadOnly | QFile::Text)) [[unlikely]]
	{
		// genuine error state
		QMessageBox::warning(this, tr("Warning"), tr("Cannot open file [%1]:\n{%2}").arg(QDir::toNativeSeparators(fileName), file.errorString()));
	}
	else [[likely]]
	{
		LoadFile(file);
	}

	file.close();
}

void QtApp::OpenRecent()
{
	if (const auto action{qobject_cast<QAction*>(sender())}; !action) [[unlikely]]
	{
		// how did we get here?
		return;
	}
	else [[likely]]
	{
		OpenFile([&]
		{
			if (!action->data().isNull()) [[likely]]
			{
				return action->data().toString();
			}
			else [[unlikely]]
			{
				// missing filename in recent entry, try to recover with QFileDialog
				return QFileDialog::getOpenFileName(this, tr("Locate File..."));
			}
		}()
		);
	}
}

void QtApp::LoadSettings()
{
	QCoreApplication::setOrganizationName("WastedLessons");
	QCoreApplication::setApplicationName("WTF");

	settings = std::make_unique<QSettings>(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());

	if (settings->status() != QSettings::NoError) [[unlikely]]
	{
		QMessageBox::warning(this, tr("Error"), tr("[Error] Loading Settings; Status Code: {%1}").arg(settings->status()));
	}
	else if (!settings->isWritable()) [[unlikely]]
	{
		QMessageBox::warning(this, tr("Warning"), tr("[Warning] Loading Settings; Location Non-writable: {%1}").arg(settings->fileName()));
	}
	else if (settings->allKeys().isEmpty()) [[unlikely]]
	{
		GenerateDefaultSettings();
	}
	else [[likely]]
	{
		BackupSettings();
	}
}

void QtApp::BackupSettings()
{
	// backup the settings file in a new thread
	/*
	QFuture<void> back = QtConcurrent::run([&]
	{
	*/
		auto fileName{settings->fileName()};
		if (fileName.isEmpty()) [[unlikely]]
		{
			// can't backup: there isn't any settings file
			return;
		}

		// trim any file ext, NOTE: will also trim part of the name if there is no ext and the name includes any .'s
		if (const auto pos{fileName.lastIndexOf('.')}; pos > 0u) [[likely]]
		{
			// I don't know if truncate checks for bounds, and might as well skip a search if out of bounds
			if (pos <= fileName.size() - 1u) [[likely]]
			{
				// ensure the directory name isn't altered
				if (fileName.lastIndexOf('/') < pos) [[likely]]
				{
					fileName.truncate(pos + 1u);
				}
			}
		}
		fileName = tr("%1backup.ini").arg(fileName);

		if (QFile file(fileName); file.exists()) [[likely]]
		{
			// temporarily enable ntfs permission lookup
			extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;
			++qt_ntfs_permission_lookup;

			// make sure existing backup file permissions allow write
			//if (!(std::bit_and<QFileDevice::Permissions>()(file.permissions(), QFileDevice::WriteUser)))
			if (!(file.permissions() & QFileDevice::WriteUser)) [[unlikely]] // INTENTIONAL BITWISE
			{
				if (!file.remove()) [[unlikely]]
				{
					// can't backup: existing backup won't cooperate
					return;
				}
			}
			--qt_ntfs_permission_lookup;
		}

		Expects(settings->isAtomicSyncRequired());
		auto backup{std::make_unique<QSettings>(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), tr("%1.backup").arg(QCoreApplication::applicationName()))};

		std::ranges::for_each(settings->allKeys(), [&](auto&& key){ backup->setValue(key, settings->value(key)); });

		backup->sync();
	/*
	}); // End QFuture
	*/
}

void QtApp::GenerateDefaultSettings()
{
	// clear any existing data when generating default
	settings->clear();

	settings->setValue("System/MaxRecent", 5u);

	settings->setValue("Style/Name", "Fusion");
	settings->setValue("Style/Font", QApplication::font());
	// Note: SetPointSize take a signed integer. This is Qt design decision, so don't use unsigned literals
	settings->setValue("Style/PointSize", 10);

	// Note: QColor(int, int, int) despite using ushort internally, so don't use unsigned literals here
	settings->setValue("Style/Window",					QColor(53, 53, 53));		//QColor(53, 53, 53)
	settings->setValue("Style/WindowText",				QColor(Qt::white));			//QColor(Qt::white)
	settings->setValue("Style/DisabledWindowText",		QColor(127, 127, 127));		//QColor(127, 127, 127)
	settings->setValue("Style/Base",					QColor(42, 42, 42));		//QColor(42, 42, 42)
	settings->setValue("Style/AlternateBase",			QColor(66, 66, 66));		//QColor(66, 66, 66)
	settings->setValue("Style/ToolTipBase",				QColor(Qt::white));			//QColor(Qt::white)
	settings->setValue("Style/ToolTipText",				QColor(Qt::white));			//QColor(Qt::white)
	settings->setValue("Style/Text",					QColor(Qt::white));			//QColor(Qt::white)
	settings->setValue("Style/DisabledText",			QColor(127, 127, 127));		//QColor(127, 127, 127)
	settings->setValue("Style/Dark",					QColor(35, 35, 35));		//QColor(35, 35, 35)
	settings->setValue("Style/Shadow",					QColor(20, 20, 20));		//QColor(20, 20, 20)
	settings->setValue("Style/Button",					QColor(53, 53, 53));		//QColor(53, 53, 53)
	settings->setValue("Style/ButtonText",				QColor(Qt::white));			//QColor(Qt::white)
	settings->setValue("Style/DisabledButtonText",		QColor(127, 127, 127));		//QColor(127, 127, 127)
	settings->setValue("Style/BrightText",				QColor(Qt::red));			//QColor(Qt::red)
	settings->setValue("Style/Link",					QColor(42, 130, 218));		//QColor(42, 130, 218)
	settings->setValue("Style/Highlight",				QColor(42, 130, 218));		//QColor(42, 130, 218)
	settings->setValue("Style/DisabledHighlight",		QColor(80, 80, 80));		//QColor(80, 80, 80)
	settings->setValue("Style/HighlightedText",			QColor(Qt::white));			//QColor(Qt::white)
	settings->setValue("Style/DisabledHighlightedText",	QColor(127, 127, 127));		//QColor(127, 127, 127)
}

void QtApp::SetupStyle()
{
	qApp->setStyle(QStyleFactory::create(settings->value("Style/Name", "Fusion").value<QString>()));

	// increase font size for better reading
	auto font{settings->value("Style/Font", QApplication::font()).value<QFont>()};
	// Note: SetPointSize take a signed integer. This is Qt design decision, so don't use unsigned literals
	font.setPointSize(settings->value("Style/PointSize", font.pointSize() + 2).value<int>());
	qApp->setFont(font);

	// modify palette to dark theme by default, otherwise user settings values if available
	QPalette palette;
	// Note: QColor(int, int, int) despite using ushort internally, so don't use unsigned literals here
	palette.setColor(QPalette::All,			QPalette::Window,			settings->value("Style/Window",						QColor(53, 53, 53)).value<QColor>());		//QColor(53, 53, 53)
	palette.setColor(QPalette::All,			QPalette::WindowText,		settings->value("Style/WindowText",					QColor(Qt::white)).value<QColor>());		//QColor(Qt::white)
	palette.setColor(QPalette::Disabled,	QPalette::WindowText,		settings->value("Style/DisabledWindowText",			QColor(127, 127, 127)).value<QColor>());	//QColor(127, 127, 127)
	palette.setColor(QPalette::All,			QPalette::Base,				settings->value("Style/Base",						QColor(42, 42, 42)).value<QColor>());		//QColor(42, 42, 42)
	palette.setColor(QPalette::All,			QPalette::AlternateBase,	settings->value("Style/AlternateBase",				QColor(66, 66, 66)).value<QColor>());		//QColor(66, 66, 66)
	palette.setColor(QPalette::All,			QPalette::ToolTipBase,		settings->value("Style/ToolTipBase",				QColor(Qt::white)).value<QColor>());		//QColor(Qt::white)
	palette.setColor(QPalette::All,			QPalette::ToolTipText,		settings->value("Style/ToolTipText",				QColor(Qt::white)).value<QColor>());		//QColor(Qt::white)
	palette.setColor(QPalette::All,			QPalette::Text,				settings->value("Style/Text",						QColor(Qt::white)).value<QColor>());		//QColor(Qt::white)
	palette.setColor(QPalette::Disabled,	QPalette::Text,				settings->value("Style/DisabledText",				QColor(127, 127, 127)).value<QColor>());	//QColor(127, 127, 127)
	palette.setColor(QPalette::All,			QPalette::Dark,				settings->value("Style/Dark",						QColor(35, 35, 35)).value<QColor>());		//QColor(35, 35, 35)
	palette.setColor(QPalette::All,			QPalette::Shadow,			settings->value("Style/Shadow",						QColor(20, 20, 20)).value<QColor>());		//QColor(20, 20, 20)
	palette.setColor(QPalette::All,			QPalette::Button,			settings->value("Style/Button",						QColor(53, 53, 53)).value<QColor>());		//QColor(53, 53, 53)
	palette.setColor(QPalette::All,			QPalette::ButtonText,		settings->value("Style/ButtonText",					QColor(Qt::white)).value<QColor>());		//QColor(Qt::white)
	palette.setColor(QPalette::Disabled,	QPalette::ButtonText,		settings->value("Style/DisabledButtonText",			QColor(127, 127, 127)).value<QColor>());	//QColor(127, 127, 127)
	palette.setColor(QPalette::All,			QPalette::BrightText,		settings->value("Style/BrightText",					QColor(Qt::red)).value<QColor>());			//QColor(Qt::red)
	palette.setColor(QPalette::All,			QPalette::Link,				settings->value("Style/Link",						QColor(42, 130, 218)).value<QColor>());		//QColor(42, 130, 218)
	palette.setColor(QPalette::All,			QPalette::Highlight,		settings->value("Style/Highlight",					QColor(42, 130, 218)).value<QColor>());		//QColor(42, 130, 218)
	palette.setColor(QPalette::Disabled,	QPalette::Highlight,		settings->value("Style/DisabledHighlight",			QColor(80, 80, 80)).value<QColor>());		//QColor(80, 80, 80)
	palette.setColor(QPalette::All,			QPalette::HighlightedText,	settings->value("Style/HighlightedText",			QColor(Qt::white)).value<QColor>());		//QColor(Qt::white)
	palette.setColor(QPalette::Disabled,	QPalette::HighlightedText,	settings->value("Style/DisabledHighlightedText",	QColor(127, 127, 127)).value<QColor>());	//QColor(127, 127, 127)

	qApp->setPalette(palette);
}
