/* ************************************************************************************************************************************************ *\

\* ************************************************************************************************************************************************ */
#include "stdafx.h"
#include "QtTablet.h"

QtTablet::QtTablet(QWidget* parent) noexcept
{

}

bool QtTablet::saveImage(const QString& file) noexcept
{
	return false;
}

bool QtTablet::loadImage(const QString& file) noexcept
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

void QtTablet::paintPixmap(QPainter& painter, QTabletEvent* event) noexcept
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
