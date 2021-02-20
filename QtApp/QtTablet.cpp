/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#include "stdafx.h"

#include "QtTablet.h"

QtTablet::QtTablet(QWidget* parent) noexcept
{

}

bool QtTablet::saveImage(std::string_view file) noexcept
{
	return false;
}

bool QtTablet::loadImage(std::string_view file) noexcept
{
	return false;
}

void QtTablet::clear() noexcept
{

}

void QtTablet::tabletEvent(QTabletEvent* event) noexcept
{

}

void QtTablet::paintEvent(QPaintEvent* event) noexcept
{

}

void QtTablet::resizeEvent(QResizeEvent* event) noexcept
{

}

void QtTablet::initPixmap() noexcept
{

}

void QtTablet::paintPixmap(const QPainter& painter, const QTabletEvent* event) noexcept
{

}

Qt::BrushStyle QtTablet::brushPattern(qreal value) noexcept
{
	return Qt::BrushStyle{};
}

qreal QtTablet::pressureToWidth(qreal pressure) noexcept
{
	return qreal{};
}

void QtTablet::updateBrush(const QTabletEvent* event) noexcept
{

}

void QtTablet::updateCursor(const QTabletEvent* event) noexcept
{

}
