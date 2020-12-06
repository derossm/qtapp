/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */
#pragma once

#include "stdafx.h"
#include "QtHeaders.h"
#include "QtApp.h"

class SettingsDialog : public QDialog
{
	QtApp* _parent;
	std::unique_ptr<QSettings> settings;
	QColor color;

	void setupUi();
	void retranslateUi();
	void setColor();
	void setupColor();

public:

	SettingsDialog(QtApp* p = nullptr) : _parent{p}
	{
		setupUi();
		setupColor();
	}

private slots:
	void accept();
};
