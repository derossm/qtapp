/* ************************************************************************************************************************************************ *\
	This is the main Qt module.

	Note: following Qt style for Qt interfacing code
\* ************************************************************************************************************************************************ */

#pragma once

#include "stdafx.h"

#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

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

	auto GetRecentFiles() const;
	void UpdateRecentFiles();
	void ConnectRecent(QStringList& files);
	void OpenRecent();
	void OpenFile(QString fileName);

	void LoadSettings();
	void SaveSettings();

	void LoadFile(QFile& file);
	void SaveDialog();

	void SetupStyle();
	void GenerateDefaultSettings();

	// do not copy
	QtApp(const QtApp&) = delete;
	QtApp& operator=(const QtApp&) = delete;

	// do not move
	QtApp(QtApp&&) = delete;
	QtApp& operator=(QtApp&&) = delete;

public:
	QtApp(QWidget* parent = (QWidget*)nullptr); // parent default casted this way in Qt
	~QtApp();

public slots:
	// must be accessible by SettingsDialog to trigger updating the style
	void UpdateStyle()
	{
		SetupStyle();
	}

private slots:
	void on_actionNew_triggered();
	void on_actionOpen_triggered();

	void on_actionSave_triggered();
	void on_actionSave_As_triggered();
	void on_actionSave_All_triggered();

	void on_actionReload_triggered();
	void on_actionReload_All_triggered();

	void on_actionExit_triggered();

	void on_actionUndo_triggered();
	void on_actionRedo_triggered();

	void on_actionCut_triggered();
	void on_actionCopy_triggered();
	void on_actionPaste_triggered();
	void on_actionDelete_triggered();
	void on_actionDuplicate_triggered();

	void on_actionSelect_All_triggered();

	void on_actionFind_triggered();
	void on_actionFind_Next_triggered();
	void on_actionFind_Previous_triggered();
	void on_actionFind_All_triggered();

	void on_actionReplace_triggered();
	void on_actionReplace_Next_triggered();
	void on_actionReplace_Previous_triggered();
	void on_actionReplace_All_triggered();

	void on_actionSettings_triggered();
	void on_actionRoll_triggered();

	void on_tabWidget_tabCloseRequested(int index);
};
