/* ******************************************************************************** *\

\* ******************************************************************************** */

#include "stdafx.h"

#include "SettingsDialog.h"

void SettingsDialog::setupUi()
{
	if (this->objectName().isEmpty())
	{
		this->setObjectName(QString::fromUtf8("settingsUI"));
	}

	this->resize(1134, 610);
	buttonBox = new QDialogButtonBox(this);
	buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
	buttonBox->setGeometry(QRect(30, 240, 341, 32));
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

	retranslateUi();

	connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
	connect(buttonBox, &QDialogButtonBox::accepted, _parent, &QtApp::UpdateStyle);

	QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	QMetaObject::connectSlotsByName(this);
}

void SettingsDialog::retranslateUi()
{
	this->setWindowTitle(QCoreApplication::translate("Settings", "Dialog", nullptr));
}

void SettingsDialog::setColor()
{
	QCoreApplication::setOrganizationName("WastedLessons");
	QCoreApplication::setApplicationName("WTF");

	//auto settings = std::make_unique<QSettings>(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
	QSettings settings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());

	if (settings.status() != QSettings::NoError)
	{
		QMessageBox::warning(this, tr("Error"), tr("[Error] Loading Settings; Status Code: {%1}").arg(settings.status()));
	}
	else if (!settings.isWritable())
	{
		QMessageBox::warning(this, tr("Warning"), tr("[Warning] Loading Settings; Location Non-writable: {%1}").arg(settings.fileName()));
	}

	const auto color = QColorDialog::getColor(settings.value("Style/Window", QColor(Qt::green)).value<QColor>(), this, "Select Color", QColorDialog::ShowAlphaChannel);

	if (color.isValid())
	{
		settings.setValue("Style/Window", color);
		settings.sync();
	}
}

void SettingsDialog::setupColor()
{
	colorButton = new QPushButton(tr("Setup Color"));

	auto layout = new QGridLayout(this);

	layout->setColumnStretch(1, 1);
	layout->addWidget(colorButton, 0, 0);

	connect(colorButton, &QAbstractButton::clicked, this, &SettingsDialog::setColor);

	QMetaObject::connectSlotsByName(this);
}

void SettingsDialog::accept()
{
	this->done(QDialog::Accepted);
}
