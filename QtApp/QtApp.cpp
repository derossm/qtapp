/* ******************************************************************************** *\

\* ******************************************************************************** */

#include "stdafx.h"

#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun.h>

#include <QtCore/QVariant>

#include "QtApp.h"
#include "SettingsDialog.h"

#include <functional>
//#define GET_VARIABLE_NAME(Variable) (#Variable)

void QtApp::on_actionNew_triggered()
{

}

/*
	Loading/Saving files
*/
void QtApp::LoadFile(QFile& file)
{
	currentFile = file.fileName();

	const auto tokens{currentFile.split('/')};

	const auto name{[&](){ return tokens.length() ? tokens.at(tokens.length()-1) : tr("New File"); }()}; //initialize local with immediate lambda call

	QTextStream in(&file);

	// TODO move tab setup to a new function
	auto textEdit{new QTextEdit()};

	if (in.status() == QTextStream::Status::Ok)
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

	ui->tabWidget->insertTab(0, tab, name);
	ui->tabWidget->setCurrentIndex(0); // update view to display the new tab

	UpdateRecentFiles();
}

void QtApp::SaveDialog()
{
}

void QtApp::on_tabWidget_tabCloseRequested(int index)
{
	// TODO check if Qt already handles memory of child pointers, for now delete everything we new'd
	auto tab{ui->tabWidget->widget(index)};
	auto layout{tab->layout()};
	auto widget{layout->itemAt(0)};

	layout->removeItem(widget);
	ui->tabWidget->removeTab(index);

	delete widget;
	delete layout;
	delete tab;
}

/* ******************************************************************************** *\
	menu setup
\* ******************************************************************************** */
auto QtApp::GetRecentFiles() const
{
	QStringList files;

	settings->beginGroup("RecentFiles");
	std::ranges::for_each(settings->childKeys(), [&](auto&& key){ files.push_back(settings->value(key).value<QString>()); });
	settings->endGroup();

	// TODO confirm RVO is happening
	return files;
}

void QtApp::ConnectRecent(QStringList& files)
{
	// more work to check recent are valid still, just reset connected actions TODO think about
	while (recentFileActions.size() > 0)
	{
		QObject::disconnect(recentFileActions.back().get());
		recentFileActions.pop_back();
	}

	recentFileActions.reserve(files.size());

	for (auto&& val : files)
	{
		auto recentFileAction{std::make_unique<QAction>(this)};

		recentFileAction->setVisible(true);
		recentFileAction->setText(val);
		recentFileAction->setData(val);

		QObject::connect(recentFileAction.get(), &QAction::triggered, this, &QtApp::OpenRecent);
		ui->menuOpen_Recent->addAction(recentFileAction.get());

		recentFileActions.emplace_back(std::move(recentFileAction));
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

	if (!currentFile.isEmpty())
	{
		files.push_front(currentFile);
	}

	if (files.isEmpty())
	{
		files.push_front("<No Recent File History>");
	}
	else
	{
		files.removeDuplicates();

		// if max allowed recent files has been lowered, discard excess entries
		while (files.size() > settings->value("System/MaxRecent", 5).value<int>())
		{
			files.pop_back();
		}

		settings->beginGroup("RecentFiles");
		std::ranges::for_each(settings->childKeys(), [&](auto&& key){ settings->remove(key); });
		settings->endGroup();

		SaveSettings();

		//for (auto&& v : files) // need a counter, might as well use normal for loop
		//const auto size{files.size()};
		for (qsizetype i{0}, size{files.size()}; i < size; ++i)
		{
			settings->setValue(tr("RecentFiles/recent%1").arg(i), files.at(i));
		}
	}

	ConnectRecent(files);
}

void QtApp::LoadSettings()
{
	QCoreApplication::setOrganizationName("WastedLessons");
	QCoreApplication::setApplicationName("WTF");

	settings = std::make_unique<QSettings>(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());

	if (settings->status() != QSettings::NoError)
	{
		QMessageBox::warning(this, tr("Error"), tr("[Error] Loading Settings; Status Code: {%1}").arg(settings->status()));
	}
	else if (!settings->isWritable())
	{
		QMessageBox::warning(this, tr("Warning"), tr("[Warning] Loading Settings; Location Non-writable: {%1}").arg(settings->fileName()));
	}
	else if (settings->allKeys().isEmpty())
	{
		GenerateDefaultSettings();
	}
	else
	{
		// backup the settings file in a new thread
		QFuture<void> back = QtConcurrent::run([&]()
		{
			auto fileName{settings->fileName()};
			if (fileName.isEmpty())
			{
				// can't backup: there isn't any settings file
				return;
			}

			const auto pos{fileName.lastIndexOf('.')};
			// trim any file ext, NOTE: will also trim part of the name if there is no ext and the name includes any .'s
			if (pos > 0)
			{
				// I don't know if truncate checks for bounds, and might as well skip a search if out of bounds
				if (pos <= fileName.size() - 1)
				{
					// ensure the directory name isn't altered
					if (fileName.lastIndexOf('/') < pos)
					{
						fileName.truncate(pos + 1);
					}
				}
			}
			fileName = tr("%1backup.ini").arg(fileName);

			auto backup{std::make_unique<QSettings>(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), tr("%1.backup").arg(QCoreApplication::applicationName()))};

			std::ranges::for_each(settings->allKeys(), [&](auto&& key){ backup->setValue(key, settings->value(key)); });

			// temporarily enable ntfs permission lookup
			extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;
			qt_ntfs_permission_lookup++;

			QFile file(fileName);
			if (file.exists())
			{
				// make sure existing backup file permissions allow write
				//if (!(file.permissions() & QFileDevice::WriteUser))
				if (!(std::bit_and<QFileDevice::Permissions>()(file.permissions(), QFileDevice::WriteUser)))
				{
					if (!file.remove())
					{
						// can't backup: existing backup won't cooperate
						return;
					}
				}
			}
			qt_ntfs_permission_lookup--;

			backup->sync();
		}); // End QFuture
	}

	//settings->sync();
}

void QtApp::SaveSettings()
{
	if (settings->status() != QSettings::NoError)
	{
		QMessageBox::warning(this, tr("Error"), tr("[Error] Saving Settings; Status Code: {%1}").arg(settings->status()));
	}
	else if (!settings->isWritable())
	{
		QMessageBox::warning(this, tr("Warning"), tr("[Warning] Saving Settings; Location Non-writable: {%1}").arg(settings->fileName()));
	}
	else
	{
		settings->sync();
	}
}

void QtApp::GenerateDefaultSettings()
{
	settings->clear();

	// Recent Files
	settings->setValue("System/MaxRecent", 5);

	// Style
	settings->setValue("Style/Name", "Fusion");
	settings->setValue("Style/Font", QApplication::font());
	settings->setValue("Style/PointSize", 10);
	settings->setValue("Style/Window", QColor(53, 53, 53));								//QColor(53, 53, 53)
	settings->setValue("Style/WindowText", QColor(Qt::white));							//QColor(Qt::white)
	settings->setValue("Style/DisabledWindowText", QColor(127, 127, 127));				//QColor(127, 127, 127)
	settings->setValue("Style/Base", QColor(42, 42, 42));								//QColor(42, 42, 42)
	settings->setValue("Style/AlternateBase", QColor(66, 66, 66));						//QColor(66, 66, 66)
	settings->setValue("Style/ToolTipBase", QColor(Qt::white));							//QColor(Qt::white)
	settings->setValue("Style/ToolTipText", QColor(Qt::white));							//QColor(Qt::white)
	settings->setValue("Style/Text", QColor(Qt::white));								//QColor(Qt::white)
	settings->setValue("Style/DisabledText", QColor(127, 127, 127));					//QColor(127, 127, 127)
	settings->setValue("Style/Dark", QColor(35, 35, 35));								//QColor(35, 35, 35)
	settings->setValue("Style/Shadow", QColor(20, 20, 20));								//QColor(20, 20, 20)
	settings->setValue("Style/Button", QColor(53, 53, 53));								//QColor(53, 53, 53)
	settings->setValue("Style/ButtonText", QColor(Qt::white));							//QColor(Qt::white)
	settings->setValue("Style/DisabledButtonText", QColor(127, 127, 127));				//QColor(127, 127, 127)
	settings->setValue("Style/BrightText", QColor(Qt::red));							//QColor(Qt::red)
	settings->setValue("Style/Link", QColor(42, 130, 218));								//QColor(42, 130, 218)
	settings->setValue("Style/Highlight", QColor(42, 130, 218));						//QColor(42, 130, 218)
	settings->setValue("Style/DisabledHighlight", QColor(80, 80, 80));					//QColor(80, 80, 80)
	settings->setValue("Style/HighlightedText", QColor(Qt::white));						//QColor(Qt::white)
	settings->setValue("Style/DisabledHighlightedText", QColor(127, 127, 127));			//QColor(127, 127, 127)
}

void QtApp::SetupStyle()
{
	// set style
	qApp->setStyle(QStyleFactory::create(settings->value("Style/Name", "Fusion").value<QString>()));

	// increase font size for better reading
	auto font{settings->value("Style/Font", QApplication::font()).value<QFont>()};
	font.setPointSize(settings->value("Style/PointSize", font.pointSize() + 2).value<int>());
	qApp->setFont(font);

	// modify palette to dark
	QPalette palette;
	palette.setColor(QPalette::Window, settings->value("Style/Window", QColor(53, 53, 53)).value<QColor>());													//QColor(53, 53, 53)
	palette.setColor(QPalette::WindowText, settings->value("Style/WindowText", QColor(Qt::white)).value<QColor>());												//QColor(Qt::white)
	palette.setColor(QPalette::Disabled, QPalette::WindowText, settings->value("Style/DisabledWindowText", QColor(127, 127, 127)).value<QColor>());				//QColor(127, 127, 127)
	palette.setColor(QPalette::Base, settings->value("Style/Base", QColor(42, 42, 42)).value<QColor>());														//QColor(42, 42, 42)
	palette.setColor(QPalette::AlternateBase, settings->value("Style/AlternateBase", QColor(66, 66, 66)).value<QColor>());										//QColor(66, 66, 66)
	palette.setColor(QPalette::ToolTipBase, settings->value("Style/ToolTipBase", QColor(Qt::white)).value<QColor>());											//QColor(Qt::white)
	palette.setColor(QPalette::ToolTipText, settings->value("Style/ToolTipText", QColor(Qt::white)).value<QColor>());											//QColor(Qt::white)
	palette.setColor(QPalette::Text, settings->value("Style/Text", QColor(Qt::white)).value<QColor>());															//QColor(Qt::white)
	palette.setColor(QPalette::Disabled, QPalette::Text, settings->value("Style/DisabledText", QColor(127, 127, 127)).value<QColor>());							//QColor(127, 127, 127)
	palette.setColor(QPalette::Dark, settings->value("Style/Dark", QColor(35, 35, 35)).value<QColor>());														//QColor(35, 35, 35)
	palette.setColor(QPalette::Shadow, settings->value("Style/Shadow", QColor(20, 20, 20)).value<QColor>());													//QColor(20, 20, 20)
	palette.setColor(QPalette::Button, settings->value("Style/Button", QColor(53, 53, 53)).value<QColor>());													//QColor(53, 53, 53)
	palette.setColor(QPalette::ButtonText, settings->value("Style/ButtonText", QColor(Qt::white)).value<QColor>());												//QColor(Qt::white)
	palette.setColor(QPalette::Disabled, QPalette::ButtonText, settings->value("Style/DisabledButtonText", QColor(127, 127, 127)).value<QColor>());				//QColor(127, 127, 127)
	palette.setColor(QPalette::BrightText, settings->value("Style/BrightText", QColor(Qt::red)).value<QColor>());												//QColor(Qt::red)
	palette.setColor(QPalette::Link, settings->value("Style/Link", QColor(42, 130, 218)).value<QColor>());														//QColor(42, 130, 218)
	palette.setColor(QPalette::Highlight, settings->value("Style/Highlight", QColor(42, 130, 218)).value<QColor>());											//QColor(42, 130, 218)
	palette.setColor(QPalette::Disabled, QPalette::Highlight, settings->value("Style/DisabledHighlight", QColor(80, 80, 80)).value<QColor>());					//QColor(80, 80, 80)
	palette.setColor(QPalette::HighlightedText, settings->value("Style/HighlightedText", QColor(Qt::white)).value<QColor>());									//QColor(Qt::white)
	palette.setColor(QPalette::Disabled, QPalette::HighlightedText, settings->value("Style/DisabledHighlightedText", QColor(127, 127, 127)).value<QColor>());	//QColor(127, 127, 127)

	qApp->setPalette(palette);
}

/* ******************************************************************************** *\

\* ******************************************************************************** */
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

/* ******************************************************************************** *\
	menu->file
\* ******************************************************************************** */
void QtApp::OpenRecent()
{
	const auto action{qobject_cast<QAction*>(sender())};
	if (!action)
	{
		// how did we get here?
		return;
	}

	QString fileName;

	if (!action->data().isNull())
	{
		fileName = action->data().toString();
	}

	if (fileName.isEmpty())
	{
		// missing filename in recent entry, try to recover with QFileDialog
		fileName = QFileDialog::getOpenFileName(this, tr("Locate File..."));
	}

	OpenFile(std::move(fileName));
}

void QtApp::on_actionOpen_triggered()
{
	OpenFile(std::move(QFileDialog::getOpenFileName(this, tr("Open File..."))));
}

// sadly this can't be done in a new thread, because QtApp::LoadFile() has to be done in the QtGui thread
void QtApp::OpenFile(QString fileName)
{
	if (fileName.isNull())
	{
		// user cancelled action during QFileDialog
		return;
	}

	QFile file(fileName);

	if (!file.exists())
	{
		// invalid filename, try to locate if the file was moved (or just open something else)
		fileName = QFileDialog::getOpenFileName(this, tr("Locate File..."));

		if (fileName.isNull())
		{
			// user cancelled action during QFileDialog
			return;
		}
		else
		{
			file.setFileName(fileName);
		}
	}

	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		// genuine error state
		QMessageBox::warning(this, tr("Warning"), tr("Cannot open file [%1]:\n{%2}").arg(QDir::toNativeSeparators(fileName), file.errorString()));
	}
	else
	{
		LoadFile(file);
	}

	file.close();
}

void QtApp::on_actionSave_triggered()
{
}

void QtApp::on_actionSave_As_triggered()
{
}

void QtApp::on_actionSave_All_triggered()
{
}

void QtApp::on_actionReload_triggered()
{
}

void QtApp::on_actionReload_All_triggered()
{
}

void QtApp::on_actionExit_triggered()
{
	// TODO check if save on close is enabled
	/*
	if (should save)
	{
		// save stuff
	}
	*/

	// cleanly quit
	qApp->quit();
}

/* ******************************************************************************** *\
	menu->edit
\* ******************************************************************************** */
void QtApp::on_actionUndo_triggered()
{
}

void QtApp::on_actionRedo_triggered()
{
}

void QtApp::on_actionCut_triggered()
{
}

void QtApp::on_actionCopy_triggered()
{
}

void QtApp::on_actionPaste_triggered()
{
}

void QtApp::on_actionDelete_triggered()
{
}

void QtApp::on_actionDuplicate_triggered()
{
}

void QtApp::on_actionSelect_All_triggered()
{
}

/* ******************************************************************************** *\
	menu->search
\* ******************************************************************************** */
void QtApp::on_actionFind_triggered()
{
}

void QtApp::on_actionFind_Next_triggered()
{
}

void QtApp::on_actionFind_Previous_triggered()
{
}

void QtApp::on_actionFind_All_triggered()
{
}

void QtApp::on_actionReplace_triggered()
{
}

void QtApp::on_actionReplace_Next_triggered()
{
}

void QtApp::on_actionReplace_Previous_triggered()
{
}

void QtApp::on_actionReplace_All_triggered()
{
}

/* ******************************************************************************** *\
	menu->tools
\* ******************************************************************************** */
void QtApp::on_actionSettings_triggered()
{
	settingsDialog->show();
}

void QtApp::on_actionRoll_triggered()
{
}
