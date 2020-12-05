/* ************************************************************************************************************************************************ *\
	This is the main Qt module.

	Note: following Qt style for Qt interfacing code
\* ************************************************************************************************************************************************ */

#pragma once

#include "stdafx.h"

#pragma warning(push, 0)
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtWidgets>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun.h>

// unnecessary?
#include <QObject>

// duplicates in ui_QtApp.h
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QVariant>

// duplicates in ui_QtApp.h
#include <QtGui/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#pragma warning(pop)

#include "uic/ui_QtApp.h"

class SettingsDialog;

class QtApp : public QMainWindow
{
	Q_OBJECT

private:
	std::unique_ptr<Ui::QtGuiApplicationClass> ui;
	std::unique_ptr<SettingsDialog> settingsDialog;
	std::unique_ptr<QSettings> settings;

	std::vector<std::unique_ptr<QAction>> recentFileActions;
	QString currentFile;

	[[nodiscard]]
	auto GetRecentFiles() const
	{
		QStringList files;

		settings->beginGroup("RecentFiles");
		std::ranges::for_each(settings->childKeys(), [&](auto&& key){ files.push_back(settings->value(key).value<QString>()); });
		settings->endGroup();

		// TODO confirm RVO is happening
		return files;
	}

	void ConnectRecent(QStringList& files);
	void UpdateRecentFiles();
	void OpenRecent();

	void LoadFile(QFile& file);
	void OpenFile(QString fileName);

	void SaveDialog() {}

	void GenerateDefaultSettings();

	void LoadSettings();
	void SaveSettings()
	{
		if (settings->status() != QSettings::NoError) [[unlikely]]
		{
			QMessageBox::warning(this, tr("Error"), tr("[Error] Saving Settings; Status Code: {%1}").arg(settings->status()));
		}
		else if (!settings->isWritable()) [[unlikely]]
		{
			QMessageBox::warning(this, tr("Warning"), tr("[Warning] Saving Settings; Location Non-writable: {%1}").arg(settings->fileName()));
		}
		else [[likely]]
		{
			auto back{ QtConcurrent::run([&]{ settings->sync(); }) };
		}
	}

	void BackupSettings();

	void SetupStyle();

	// do not copy
	QtApp(const QtApp&) = delete;
	QtApp& operator=(const QtApp&) = delete;

	// do not move
	QtApp(QtApp&&) = delete;
	QtApp& operator=(QtApp&&) = delete;

public:
	QtApp(QWidget* parent = (QWidget*)nullptr);

	~QtApp();

public slots:
	// must be accessible by SettingsDialog to trigger updating the style
	void UpdateStyle()
	{
		SetupStyle();
	}

private slots:
	void on_actionNew_triggered() {}
	void on_actionOpen_triggered()
	{
		OpenFile(std::move(QFileDialog::getOpenFileName(this, tr("Open File..."))));
	}

	void on_actionSave_triggered() {}
	void on_actionSave_As_triggered() {}
	void on_actionSave_All_triggered() {}

	void on_actionReload_triggered() {}
	void on_actionReload_All_triggered() {}

	void on_actionUndo_triggered() {}
	void on_actionRedo_triggered() {}

	void on_actionCut_triggered() {}
	void on_actionCopy_triggered() {}
	void on_actionPaste_triggered() {}
	void on_actionDelete_triggered() {}
	void on_actionDuplicate_triggered() {}

	void on_actionSelect_All_triggered() {}

	void on_actionFind_triggered() {}
	void on_actionFind_Next_triggered() {}
	void on_actionFind_Previous_triggered() {}
	void on_actionFind_All_triggered() {}

	void on_actionReplace_triggered() {}
	void on_actionReplace_Next_triggered() {}
	void on_actionReplace_Previous_triggered() {}
	void on_actionReplace_All_triggered() {}

	void on_actionSettings_triggered();

	// NOTE Qt uses int for index of widget, so don't use unsigned literals here Qt 6.0
	void on_tabWidget_tabCloseRequested(int index)
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

	void on_actionExit_triggered()
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
};
