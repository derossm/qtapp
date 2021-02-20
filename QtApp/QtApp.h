/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:
		This is the main Qt module.

		Note: following Qt style for Qt interfacing code
\**********************************************************************************************************************************************/
#pragma once

#include "stdafx.h"
#include "QtHeaders.h"

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

	//_NODISCARD
	[[nodiscard]]
	auto GetRecentFiles() const noexcept
	{
		QStringList files;

		settings->beginGroup("RecentFiles");
		std::ranges::for_each(settings->childKeys(), [&](auto&& key){ files.push_back(settings->value(key).value<QString>()); });
		settings->endGroup();

		return files;
	}

	void ConnectRecent(QStringList& files) noexcept;
	void UpdateRecentFiles() noexcept;
	void OpenRecent() noexcept;

	void LoadFile(QFile& file) noexcept;
	void OpenFile(QString fileName) noexcept;

	constexpr void SaveDialog() noexcept {}

	void GenerateDefaultSettings() noexcept;

	void LoadSettings() noexcept;
	void SaveSettings() noexcept
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
			// WARNING: in Qt 6, there are exceptions from sometimes atomic failures in this call TODO
			// QFuture back creating a new thread for disk sync
			//auto back{ QtConcurrent::run([&]{ try { settings->sync(); } catch (...){ std::cout<<"Exception during settings->sync()"; } }) };
			settings->sync();
		}
	}

	void BackupSettings() noexcept;

	void SetupStyle() noexcept;

	// do not copy
	QtApp(const QtApp&) = delete;
	QtApp& operator=(const QtApp&) = delete;

	// do not move
	QtApp(QtApp&&) = delete;
	QtApp& operator=(QtApp&&) = delete;

public:
	QtApp(QWidget* parent = (QWidget*)nullptr) noexcept;

	~QtApp() noexcept;

public slots:
	// must be accessible by SettingsDialog to trigger updating the style TODO event handling
	void UpdateStyle() noexcept
	{
		SetupStyle();
	}

private slots:
	constexpr void on_actionNew_triggered() noexcept {}
	void on_actionOpen_triggered() noexcept
	{
		//OpenFile(std::move(QFileDialog::getOpenFileName(this, tr("Open File..."))));
		OpenFile(QFileDialog::getOpenFileName(this, tr("Open File...")));
	}

	constexpr void on_actionSave_triggered() noexcept {}
	constexpr void on_actionSave_As_triggered() noexcept {}
	constexpr void on_actionSave_All_triggered() noexcept {}

	constexpr void on_actionReload_triggered() noexcept {}
	constexpr void on_actionReload_All_triggered() noexcept {}

	constexpr void on_actionUndo_triggered() noexcept {}
	constexpr void on_actionRedo_triggered() noexcept {}

	constexpr void on_actionCut_triggered() noexcept {}
	constexpr void on_actionCopy_triggered() noexcept {}
	constexpr void on_actionPaste_triggered() noexcept {}
	constexpr void on_actionDelete_triggered() noexcept {}
	constexpr void on_actionDuplicate_triggered() noexcept {}

	constexpr void on_actionSelect_All_triggered() noexcept {}

	constexpr void on_actionFind_triggered() noexcept {}
	constexpr void on_actionFind_Next_triggered() noexcept {}
	constexpr void on_actionFind_Previous_triggered() noexcept {}
	constexpr void on_actionFind_All_triggered() noexcept {}

	constexpr void on_actionReplace_triggered() noexcept {}
	constexpr void on_actionReplace_Next_triggered() noexcept {}
	constexpr void on_actionReplace_Previous_triggered() noexcept {}
	constexpr void on_actionReplace_All_triggered() noexcept {}

	void on_actionSettings_triggered() noexcept;

	// NOTE Qt uses int for index of widget, so don't use unsigned literals here Qt 6.0
	void on_tabWidget_tabCloseRequested(int index) noexcept
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

	void on_actionExit_triggered() noexcept
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
