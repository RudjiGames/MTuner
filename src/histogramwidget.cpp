//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/histogramwidget.h>
#include <MTuner/src/binloaderview.h>
#include <MTuner/src/histogram.h>
#include <MTuner/src/capturecontext.h>

HistogramWidget::HistogramWidget(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);

	m_histogramView	= findChild<HistogramView*>("graphicsView");
	connect(m_histogramView, SIGNAL(binClicked()), this, SIGNAL(binClicked()));

	m_comboType = findChild<QComboBox*>("comboType");
	connect(m_comboType, SIGNAL(activated(int)), this, SLOT(displayTypeChanged(int)));

	m_comboHist = findChild<QComboBox*>("comboHistogram");
	connect(m_comboHist, SIGNAL(activated(int)), this, SLOT(displayModeChanged(int)));

	m_chkPeaks = findChild<QCheckBox*>("checkBoxPeaks");
	connect(m_chkPeaks, SIGNAL(stateChanged(int)), this, SLOT(showPeaksChanged(int)));

	setContext(NULL,NULL);
}

void HistogramWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void HistogramWidget::setContext(CaptureContext* _capture, BinLoaderView* _binView)
{
	m_binView = _binView;
	if (_capture)
	{
		m_histogramView->setContext(_capture);
		m_comboType->setEnabled(true);
		m_comboHist->setEnabled(true);
		m_chkPeaks->setEnabled(true);
		displayTypeChanged(m_binView->getHistogramType());
		displayModeChanged(m_binView->getHistogramMode());
		showPeaksChanged(m_binView->getHistogramPeaks()?1:0);
	}
	else
	{
		m_histogramView->setContext(NULL);
		m_comboType->setEnabled(false);
		m_comboHist->setEnabled(false);
		m_chkPeaks->setEnabled(false);
		displayTypeChanged(0);
		displayModeChanged(0);
		showPeaksChanged(0);
	}
}

void HistogramWidget::updateUI()
{
	if (m_histogramView)
		m_histogramView->updateUI();
}

void HistogramWidget::displayTypeChanged(int _index)
{
	Histogram* h = m_histogramView->getHistogram();
	switch(_index)
	{
		case 0: h->setHistogramType(HistogramType::Size); break;
		case 1: h->setHistogramType(HistogramType::Overhead); break;
		case 2: h->setHistogramType(HistogramType::Count); break;
	};
	if (m_binView)
		m_binView->setHistogramType(_index);
	m_comboType->setCurrentIndex(_index);
}

void HistogramWidget::displayModeChanged(int _index)
{
	Histogram* h = m_histogramView->getHistogram();
	switch(_index)
	{
		case 0: h->setDisplayMode(DisplayMode::Global); break;
		case 1: h->setDisplayMode(DisplayMode::Snapshot); break;
		case 2: h->setDisplayMode(DisplayMode::Both); break;
	};
	if (m_binView)
		m_binView->setHistogramMode(_index);
	m_comboHist->setCurrentIndex(_index);
}

void HistogramWidget::showPeaksChanged(int _state)
{
	Histogram* h = m_histogramView->getHistogram();
	h->setPeaks(_state!=0);
	if (m_binView)
		m_binView->setHistogramPeaks(_state!=0);
	m_chkPeaks->setChecked(_state!=0);
}
