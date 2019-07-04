//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_HISTOGRAMWIDGET_H
#define RTM_MTUNER_HISTOGRAMWIDGET_H

#include <MTuner/.qt/qt_ui/histogram_ui.h>

class HistogramView;
class BinLoaderView;

class HistogramWidget : public QWidget
{
	Q_OBJECT

private:
	QComboBox*		m_comboType;
	QComboBox*		m_comboHist;
	QCheckBox*		m_chkPeaks;
	HistogramView*	m_histogramView;
	BinLoaderView*	m_binView;

public:
	HistogramWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void changeEvent(QEvent* _event);
	void setContext(CaptureContext* _context, BinLoaderView* _binView);

public Q_SLOTS:
	void updateUI();
	void displayTypeChanged(int _index);
	void displayModeChanged(int _index);
	void showPeaksChanged(int _state);

Q_SIGNALS:
	void binClicked();

private:
	Ui::HistogramWidgetClass ui;
};

#endif // RTM_MTUNER_HISTOGRAMWIDGET_H
