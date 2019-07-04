//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/graphgrid.h>
#include <MTuner/src/graphcurve.h>
#include <MTuner/src/graphwidget.h>
#include <MTuner/src/capturecontext.h>

GraphGrid::GraphGrid(GraphWidget* _graphWidget, GraphCurve* _curve)
{
	m_graphWidget	= _graphWidget;
	m_curve			= _curve;
}

QRectF GraphGrid::boundingRect() const
{
	QSize sz = m_graphWidget->size();
	return QRectF(-sz.width()/2, -sz.height()/2, sz.width(), sz.height());
}

QPainterPath GraphGrid::shape() const
{
    QPainterPath path;
	path.addRect( QRectF(0, 0, 0, 0) );
    return path;
}

static const char* getTextFromSize(uint64_t _size)
{
	static char buffer[64];
	static const char* suffix[] = { "b ", "Kb", "Mb", "Gb", "Tb" };

	uint64_t size = _size;
	int suffIdx = 0;
	while (size >= 1024)
	{
		size /= 1024;
		suffIdx++;
	}

	strcpy(&buffer[61],suffix[suffIdx]);
	int idx = 60;
	while (size)
	{
		buffer[idx--] = '0' + size%10;
		size/=10;
	}

	return &buffer[idx+1];
}

QString getTimeString(float _time, uint64_t* _msec = NULL)
{
	uint64_t time = _time * 1000;

	if (_msec)
		*_msec = time;

	uint64_t msec = time % 1000;
	time /= 1000;
	uint64_t sec = time % 60;
	time /= 60;
	uint64_t min = time % 60;
	time /= 60;
	uint64_t hour = time;

	if (hour)
		return QString("%1h %2m %3s %4ms").arg(hour).arg(min).arg(sec).arg(msec);

	if (min)
		return QString("%1m %2s %3ms").arg(min).arg(sec).arg(msec);

	if (sec)
		return QString("%1s %2ms").arg(sec).arg(msec);

	return QString("0s %1ms").arg(msec);
}

void GraphGrid::paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget)
{
	RTM_UNUSED(_option);
	RTM_UNUSED(_widget);

	if (!m_graphWidget->getContext())
		return;

	// ruler vertical

	_painter->setRenderHint(QPainter::Antialiasing, true);
	CaptureContext* ctx = m_graphWidget->getContext();
	QRect rect = m_graphWidget->getDrawRect();
	int64_t left = rect.x();
	int64_t top = rect.y();
	int64_t right = rect.width() + rect.x();
	int64_t bottom = rect.height() + rect.y();

	_painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
	_painter->drawLine(QLineF(left,bottom,right,bottom));
	_painter->drawLine(QLineF(right,bottom,right-5,bottom-5));
	_painter->drawLine(QLineF(right,bottom,right-5,bottom+5));

	// the grid
	_painter->drawLine(QLineF(left,bottom,left,top));
	_painter->drawLine(QLineF(left,top,left-5,top+5));
	_painter->drawLine(QLineF(left,top,left+5,top+5));

	// horizontal lines
	
	_painter->setPen(QPen(Qt::darkGray, 1.0, Qt::DashLine));
	
	uint64_t max = m_curve->getMaxUsage();
	uint64_t min = m_curve->getMinUsage();

	uint64_t maxSize = 8;
	while (maxSize <= max) maxSize <<= 1;
	maxSize >>= 1;

	uint64_t minSize = maxSize;
	if (min != 0)
	{
		while (minSize >= min) minSize >>= 1;
	}
	else minSize = 8;
	minSize <<= 1;

	int prevY = -100000; // make sure we don't break at first line

	for (;;)
	{
		if (maxSize < minSize)
			break;

		int ycoord = bottom - ((bottom - top) * (maxSize-min) / max);
		if (ycoord - prevY < 10)
			break;
	
		prevY = ycoord;

		_painter->drawLine(left, ycoord, right, ycoord);
		QRectF txtR(left-39, ycoord-7, 36, 10);
		_painter->drawText(txtR, Qt::AlignCenter, getTextFromSize(maxSize));
		maxSize >>= 1;
	}

	// times

	uint64_t minTime = m_graphWidget->minTime();
	uint64_t maxTime = m_graphWidget->maxTime();

	uint64_t minMSec;
	uint64_t maxMSec;

	QRectF lcorner(left-50,bottom+6,100,20);
	QRectF rcorner(right-60,bottom+6,100,20);

	QString timeMin = getTimeString(ctx->m_capture->getFloatTime(minTime), &minMSec);
	QString timeMax = getTimeString(ctx->m_capture->getFloatTime(maxTime), &maxMSec);

	_painter->drawText(lcorner, Qt::AlignCenter, timeMin);
	_painter->drawText(rcorner, Qt::AlignCenter, timeMax);

	{
		uint64_t msecs = maxMSec - minMSec;
		uint64_t single = msecs / 11;

		uint64_t round = 1;
		while (round < single) round *= 10;

		uint64_t curr = minMSec + round;
		curr -= curr % round;

		uint64_t intensity = 255*single/round;
		_painter->setPen(QPen(QColor(0,0,0,intensity/2), 1.0, Qt::DashLine));

		while (curr < maxMSec)
		{
			uint64_t clocks = ctx->m_capture->getClocksFromTime(float(curr) / 1000.0f);
			int highlightX = m_graphWidget->mapTimeToPos(clocks);
			_painter->drawLine(highlightX, top, highlightX, bottom);
			curr += round;
		}

		if (round >= 10)
		{
			round /= 10;
			curr = minMSec + round;
			curr -= curr % round;

			_painter->setPen(QPen(QColor(0,0,0,(255-intensity)/2), 1.0, Qt::DashLine));

			while (curr < maxMSec)
			{
				uint64_t clocks = ctx->m_capture->getClocksFromTime(float(curr) / 1000.0f);
				int highlightX = m_graphWidget->mapTimeToPos(clocks);
				_painter->drawLine(highlightX, top, highlightX, bottom);
				curr += round;
			}
		}
	}

	uint64_t position = m_graphWidget->currentPos();
	if (position != 0)
	{
		int highlightX = m_graphWidget->mapTimeToPos(position);
		_painter->setPen(QPen(QColor(50, 150, 170), 1.0, Qt::SolidLine));
		_painter->drawLine(highlightX, top, highlightX, bottom);
	}

	uint64_t highlightTimeStart = m_graphWidget->getHighlightTime();
	uint64_t highlightTimeEnd	= m_graphWidget->getHighlightTimeEnd();

	if (highlightTimeStart < minTime)
		return;
	if (highlightTimeEnd > maxTime)
		return;

	float intensity = m_graphWidget->highlightIntensity();
	int highlightXstart	= m_graphWidget->mapTimeToPos(highlightTimeStart);
	int highlightXend	= m_graphWidget->mapTimeToPos(highlightTimeEnd);

	_painter->setPen(QPen(QColor(255,255,255,255*intensity), 1.0, Qt::DashLine));

	if (highlightTimeStart != highlightTimeEnd)
	{
		_painter->drawRect(highlightXstart, top, highlightXend - highlightXstart, bottom - top);
		_painter->setBrush(QColor(57,111,122,255*intensity/2));
		_painter->drawRect(highlightXstart, top, highlightXend - highlightXstart, bottom - top);
	}
	else
		_painter->drawLine(highlightXstart, top, highlightXstart, bottom);
}
