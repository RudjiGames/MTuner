//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/histogram.h>
#include <MTuner/src/histogramview.h>
#include <MTuner/src/capturecontext.h>

static bool shouldHighlight(QRect& _rect, QPoint& _highlight, int _highlightBin)
{
	if (_highlightBin == -1)
		return false;
	return _rect.contains(_highlight);
}

Histogram::Histogram(HistogramView* _histogramWidget)
{
	m_histogramWidget	= _histogramWidget;
	m_displayMode		= DisplayMode::Global;
	m_type				= HistogramType::Size;
	m_showPeaks			= false;
	m_highlight			= QPoint(0, 0); // outside
	m_highlightBin		= -1;
}

QRectF Histogram::boundingRect() const
{
	QSize sz = m_histogramWidget->size();
	return QRectF(-sz.width()/2, -sz.height()/2, sz.width(), sz.height());
}

QPainterPath Histogram::shape() const
{
    QPainterPath path;
	path.addRect( QRectF(0, 0, 0, 0) );
    return path;
}

QString Histogram::fromVal(int _val)
{
	QString s;
	if (_val < 1024)
		s = QString::number(_val) + " b";
	else
		if (_val < 1024*1024)
			s = QString::number(_val/1024) + " Kb";
		else
			s = QString::number(_val/(1024*1024)) + " Mb";

	while (s.length() < 6)
		s = " " + s;
	return s;
}

uint64_t Histogram::getMaxValue(rtm::MemoryStats& _stats, HistogramType::Enum _type, bool _usePeak)
{
	uint64_t maxVal = 0;
	int numBins = rtm::MemoryStats::NUM_HISTOGRAM_BINS;
	switch (_type)
	{
	case HistogramType::Size:
		for (int i=0; i<numBins; ++i)
		{
			maxVal = qMax(maxVal, _stats.m_histogram[i].m_size);
			if (_usePeak)
				maxVal = qMax(maxVal, _stats.m_histogram[i].m_sizePeak);
		}
		break;

	case HistogramType::Overhead:
		for (int i=0; i<numBins; ++i)
		{
			maxVal = qMax(maxVal, (uint64_t)_stats.m_histogram[i].m_overhead);
			if (_usePeak)
				maxVal = qMax(maxVal, (uint64_t)_stats.m_histogram[i].m_overheadPeak);
		}
		break;

	case HistogramType::Count:
		for (int i=0; i<numBins; ++i)
		{
			maxVal = qMax(maxVal, (uint64_t)_stats.m_histogram[i].m_count);
			if (_usePeak)
				maxVal = qMax(maxVal, (uint64_t)_stats.m_histogram[i].m_countPeak);
		}
		break;
	}
	return maxVal;
}

uint64_t Histogram::getValue(rtm::MemoryStats& _stats, HistogramType::Enum _type, int _bin, bool _peak)
{
	switch (_type)
	{
	case HistogramType::Size:
		if (_peak)
			return _stats.m_histogram[_bin].m_sizePeak;
		else
			return _stats.m_histogram[_bin].m_size;
		break;

	case HistogramType::Overhead:
		if (_peak)
			return (uint64_t)_stats.m_histogram[_bin].m_overheadPeak;
		else
			return (uint64_t)_stats.m_histogram[_bin].m_overhead;
		break;

	case HistogramType::Count:
		if (_peak)
			return (uint64_t)_stats.m_histogram[_bin].m_countPeak;
		else
			return (uint64_t)_stats.m_histogram[_bin].m_count;
		break;
	}
	return 0;
}

QString Histogram::getTypeString(HistogramType::Enum _type, uint64_t _val, bool _peak)
{
	QString ret;
	switch (_type)
	{
	case HistogramType::Size:
		if (_val == 1)
			ret = "1 " + QObject::tr("byte used");
		else
			ret = m_locale.toString(qulonglong(_val)) + " " + QObject::tr("bytes used");
		break;

	case HistogramType::Overhead:
		ret = m_locale.toString(qulonglong(_val)) + " " + QObject::tr("bytes of overhead");
		break;

	case HistogramType::Count:
		if (_val == 1)
			ret = "1 " + QObject::tr("allocation");
		else
			ret = m_locale.toString(qulonglong(_val)) + " " + QObject::tr("allocations");
		break;
	}

	if (_peak)
		ret += " " + QObject::tr("at peak");

	return ret;
}

static QColor boostColor(const QColor& _color, bool _boost)
{
	static int boost = 60;
	if (_boost)
		return QColor(qMin(_color.red()   + boost, 255),
		              qMin(_color.green() + boost, 255),
		              qMin(_color.blue()  + boost, 255),
		              _color.alpha());
	return _color;
}

void Histogram::paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget)
{
	RTM_UNUSED(_option);
	RTM_UNUSED(_widget);
	CaptureContext* ctx = m_histogramWidget->getContext();
	if (!ctx)
		return;

	QRect rect = m_histogramWidget->getDrawRect();
	int left = rect.x();
	int top = rect.y();
	int right = rect.width() + rect.x();
	int bottom = rect.height() + rect.y();

	_painter->setPen(QPen(Qt::black, 1.0, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
	_painter->drawLine(left,top,right,top);
	_painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_painter->drawLine(left,bottom,right,bottom);

	QFont font("Consolas",8,QFont::Normal);
	_painter->setFont(font);

	int numBins = rtm::MemoryStats::NUM_HISTOGRAM_BINS;
	int delta = (right-left) / (numBins+1);

	QRectF boundRect = boundingRect();
	int deltaW = (boundRect.width() - (right-left))/2;
	int deltaH = (boundRect.height() - (bottom-top))/2;

	int currSize = rtm::MemoryStats::MIN_HISTOGRAM_SIZE;
	int currPos = deltaW + delta;

	uint32_t selectedBin = ctx->m_capture->getSelectHistogramBin();

	for (int i=0; i<numBins; ++i)
	{
		_painter->save();
		if (i == static_cast<int>(selectedBin))
			_painter->setPen(QPen(QColor(50+80, 150+80, 170+80), 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		else
			_painter->setPen(QPen(Qt::lightGray, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

		QTransform tr;
		tr.translate(currPos - 15, boundRect.height() - deltaH + 21);
		tr.rotate(-45.0f);
		_painter->setTransform(tr);
		_painter->drawText(0,0,fromVal(currSize));
		_painter->restore();
		_painter->drawLine(QPoint(left+currPos-deltaW, bottom), QPoint(left+currPos-deltaW, bottom+3));
		currPos += delta;
		currSize <<= 1;
	}

	// number of histogram bars per bin, used to figure out thickness of a single bar
	int barsPerBin = 1;
	if (m_showPeaks)
		barsPerBin = 2;
	if (m_displayMode == DisplayMode::Both)
		barsPerBin *= 2;

	int thickness = (delta & ~1) - 6;

	while (thickness % barsPerBin)
		thickness -= 2;

	rtm::MemoryStats statsGlobal	= ctx->m_capture->getGlobalStats();
	rtm::MemoryStats statsSnapshot	= ctx->m_capture->getSnapshotStats();

	QColor globalCol(50, 150, 170, 138);
	QColor globalColPeak(50+60, 150+60, 170+60, 111);
	QColor snapshotCol(90, 120, 90, 138);
	QColor snapshotColPeak(90+60, 120+60, 90+60, 111);

	m_toolTips.clear();

	switch (m_displayMode)
	{
	case DisplayMode::Global:
	case DisplayMode::Snapshot:
		{
			QColor* col  = &globalCol;
			QColor* colPeak  = &globalColPeak;

			rtm::MemoryStats* stats = &statsGlobal;
			QString statsType = "Global:\n";
			if (m_displayMode == DisplayMode::Snapshot)
			{
				statsType = "Snapshot:\n";
				stats = &statsSnapshot;
				col  = &snapshotCol;
				colPeak  = &snapshotColPeak;
			}

			uint64_t maxVal = getMaxValue(*stats,m_type,false);
			uint64_t maxValPeak = getMaxValue(*stats,m_type,true);

			int position = left + delta;
			for (int i=0; i<numBins; ++i)
			{
				if (m_showPeaks)
				{
					uint64_t binVal = getValue(*stats, m_type,i,false);
					uint64_t binHeight = maxVal ? ((bottom - top) * binVal) / maxVal : 0;
					if (binHeight != 0)
					{
						QRect rect1(position-thickness/2,bottom-binHeight,thickness/2,binHeight);
						_painter->setBrush(boostColor(*col, shouldHighlight(rect1, m_highlight, m_highlightBin)));
						_painter->drawRect(rect1);
						m_toolTips.push_back(HistogramToolTip(rect1, getTypeString(m_type,binVal,false),i));
					}

					binVal = getValue(*stats, m_type,i,true);
					binHeight = maxValPeak ? ((bottom - top) * binVal) / maxValPeak : 0;
					if (binHeight != 0)
					{
						QRect rect2(position,bottom-binHeight,thickness/2,binHeight);
						_painter->setBrush(boostColor(*colPeak, shouldHighlight(rect2, m_highlight, m_highlightBin)));
						_painter->drawRect(QRect(position,bottom-binHeight,thickness/2,binHeight));
						m_toolTips.push_back(HistogramToolTip(rect2, getTypeString(m_type,binVal,true),i));
					}

					position += delta;
				}
				else
				{
					uint64_t binVal = getValue(*stats, m_type,i,false);
					uint64_t binHeight = maxVal ? ((bottom - top) * binVal) / maxVal : 0;
					if (binHeight != 0)
					{
						QRect rect1(position-thickness/2,bottom-binHeight,thickness,binHeight);
						_painter->setBrush(boostColor(*col, shouldHighlight(rect1, m_highlight, m_highlightBin)));
						_painter->drawRect(rect1);
						m_toolTips.push_back(HistogramToolTip(rect1, getTypeString(m_type,binVal,false),i));
					}

					position += delta;
				}
			}
		}
		break;

	case DisplayMode::Both:
		{
			uint64_t maxValGlobal		= getMaxValue(statsGlobal,m_type,false);
			uint64_t maxValPeakGlobal	= getMaxValue(statsGlobal,m_type,true);
			uint64_t maxValSnapshot		= getMaxValue(statsSnapshot,m_type,false);
			uint64_t maxValPeakSnapshot	= getMaxValue(statsSnapshot,m_type,true);

			int position = left + delta;
			for (int i=0; i<numBins; ++i)
			{
				if (m_showPeaks)
				{
					uint64_t binVal = getValue(statsGlobal, m_type,i,false);
					uint64_t binHeight = maxValGlobal ? ((bottom - top) * binVal) / maxValGlobal : 0;
					if (binHeight != 0)
					{
						QRect rect1(position-thickness/2,bottom-binHeight,thickness/4,binHeight);
						_painter->setBrush(boostColor(globalCol, shouldHighlight(rect1, m_highlight, m_highlightBin)));
						_painter->drawRect(rect1);
						m_toolTips.push_back(HistogramToolTip(rect1,"Global:\n" + getTypeString(m_type,binVal,false),i));
					}

					binVal = getValue(statsGlobal, m_type,i,true);
					binHeight = maxValPeakGlobal ? ((bottom - top) * binVal) / maxValPeakGlobal : 0;
					if (binHeight != 0)
					{
						QRect rect2(position-thickness/2+thickness/4,bottom-binHeight,thickness/4,binHeight);
						_painter->setBrush(boostColor(globalColPeak, shouldHighlight(rect2, m_highlight, m_highlightBin)));
						_painter->drawRect(rect2);
						m_toolTips.push_back(HistogramToolTip(rect2,"Global:\n" + getTypeString(m_type,binVal,true),i));
					}
					
					binVal = getValue(statsSnapshot, m_type,i,false);
					binHeight = maxValSnapshot ? ((bottom - top) * binVal) / maxValSnapshot : 0;
					if (binHeight != 0)
					{
						QRect rect3(position,bottom-binHeight,thickness/4,binHeight);
						_painter->setBrush(boostColor(snapshotCol, shouldHighlight(rect3, m_highlight, m_highlightBin)));
						_painter->drawRect(rect3);
						m_toolTips.push_back(HistogramToolTip(rect3,"Snapshot:\n" + getTypeString(m_type,binVal,false),i));
					}

					binVal = getValue(statsSnapshot, m_type,i,true);
					binHeight = maxValPeakSnapshot ? ((bottom - top) * binVal) / maxValPeakSnapshot : 0;
					if (binHeight != 0)
					{
						QRect rect4(position+thickness/4,bottom-binHeight,thickness/4,binHeight);
						_painter->setBrush(boostColor(snapshotColPeak, shouldHighlight(rect4, m_highlight, m_highlightBin)));
						_painter->drawRect(rect4);
						m_toolTips.push_back(HistogramToolTip(rect4,"Snapshot:\n" + getTypeString(m_type,binVal,true),i));
					}

					position += delta;
				}
				else
				{
					uint64_t binVal = getValue(statsGlobal, m_type,i,false);
					uint64_t binHeight = maxValGlobal ? ((bottom - top) * binVal) / maxValGlobal : 0;
					if (binHeight != 0)
					{
						QRect rect1(position-thickness/2,bottom-binHeight,thickness/2,binHeight);
						_painter->setBrush(boostColor(globalCol, shouldHighlight(rect1, m_highlight, m_highlightBin)));
						_painter->drawRect(rect1);
						m_toolTips.push_back(HistogramToolTip(rect1,"Global:\n" + getTypeString(m_type,binVal,false),i));
					}
					binVal = getValue(statsSnapshot, m_type,i,false);
					binHeight = maxValSnapshot ? ((bottom - top) * binVal) / maxValSnapshot : 0;
					if (binHeight != 0)
					{
						QRect rect2(position,bottom-binHeight,thickness/2,binHeight);
						_painter->setBrush(boostColor(snapshotCol, shouldHighlight(rect2, m_highlight, m_highlightBin)));
						_painter->drawRect(rect2);
						m_toolTips.push_back(HistogramToolTip(rect2,"Snapshot:\n" + getTypeString(m_type,binVal,false),i));
					}

					position += delta;
				}
			}
		}
		break;
	}
}
