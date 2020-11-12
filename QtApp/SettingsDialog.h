/* ******************************************************************************** *\

\* ******************************************************************************** */
#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

#include "QtApp.h"

class SettingsDialog : public QDialog
{
	const QtApp* _parent;
	QDialogButtonBox* buttonBox;
	QPushButton* colorButton;

	void setupUi();
	void retranslateUi();
	void setColor();
	void setupColor();

public:

	SettingsDialog(const QtApp* p = nullptr) : _parent{p}
	{
		setupUi();
		setupColor();
	}

public slots:
	void accept();
};
