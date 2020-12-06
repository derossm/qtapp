/* ************************************************************************************************************************************************ *\
	
\* ************************************************************************************************************************************************ */
#pragma once

#include "stdafx.h"
#include "QtHeaders.h"

class QtTablet : public QWidget
{
	Q_OBJECT

public:
	enum class Valuator
	{
		PressureValuator, TangentialPressureValuator, TiltValuator, VTiltValuator, HTiltValuator, NoValuator
	};
	Q_ENUM(Valuator)

	QtTablet(QWidget* parent = (QWidget*)nullptr) noexcept;

	~QtTablet() = default;

	bool saveImage(const QString& file) noexcept;
	bool loadImage(const QString& file) noexcept;
	void clear() noexcept;

	void setAlphaChannelValuator(Valuator type) noexcept
	{
		m_alphaChannelValuator = type;
	}

	void setColorSaturationValuator(Valuator type) noexcept
	{
		m_colorSaturationValuator = type;
	}

	void setLineWidthType(Valuator type) noexcept
	{
		m_lineWidthValuator = type;
	}

	void setColor(const QColor& c) noexcept
	{
		if (c.isValid()) m_color = c;
	}

	QColor color() const noexcept
	{
		return m_color;
	}

	void setTabletDevice(QTabletEvent* event) noexcept
	{
		updateCursor(event);
	}

protected:
	void tabletEvent(QTabletEvent* event) noexcept override;
	void paintEvent(QPaintEvent* event) noexcept override;
	void resizeEvent(QResizeEvent* event) noexcept override;

private:
	void initPixmap() noexcept;
	void paintPixmap(QPainter& painter, QTabletEvent* event) noexcept;
	Qt::BrushStyle brushPattern(qreal value) noexcept;
	static qreal pressureToWidth(qreal pressure) noexcept;
	void updateBrush(const QTabletEvent* event) noexcept;
	void updateCursor(const QTabletEvent* event) noexcept;

	// do not copy
	QtTablet(const QtTablet&) = delete;
	QtTablet& operator=(const QtTablet&) = delete;

	// do not move
	QtTablet(QtTablet&&) = delete;
	QtTablet& operator=(QtTablet&&) = delete;

	Valuator m_alphaChannelValuator{Valuator::TangentialPressureValuator};
	Valuator m_colorSaturationValuator{Valuator::NoValuator};
	Valuator m_lineWidthValuator{Valuator::PressureValuator};

	QColor m_color{Qt::red};

	QPixmap m_pixmap;
	QBrush m_brush;
	QPen m_pen;

	bool m_deviceDown{false};

	struct Point
	{
		QPointF pos;
		qreal pressure{0.0};
		qreal rotation{0.0};
	} lastPoint;
};
