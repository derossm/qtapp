/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#pragma once

#include "stdafx.h"
#include "QtHeaders.h"

#include "QtApp.h"

class SettingsDialog : public QDialog
{
	QtApp* _parent;
	std::unique_ptr<QSettings> settings;
	QColor color;

	void setupUi() noexcept;
	void retranslateUi() noexcept;
	void setColor() noexcept;
	void setupColor() noexcept;

public:
	SettingsDialog(QtApp* p = nullptr) noexcept : _parent{p}
	{
		setupUi();
		setupColor();
	}

private slots:
	void accept() noexcept override;
};
