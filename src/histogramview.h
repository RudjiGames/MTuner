//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_HISTOGRAMVIEW_H
#define RTM_MTUNER_HISTOGRAMVIEW_H

class Histogram;
struct CaptureContext;

class HistogramView : public QGraphicsView
{
	Q_OBJECT

private:
    QGraphicsScene*	m_scene;
	CaptureContext*	m_context;
	Histogram*		m_histogram;
	QLabel*			m_toolTipLabel;
	int				m_mode;
	bool			m_showPeaks;
	int				m_histogramType;

public:
	static const int	s_marginLeft	= 45;
	static const int	s_marginRight	= 30;
	static const int	s_marginTop		= 23;
	static const int	s_marginBottom	= 46;

	HistogramView(QWidget* _parent = 0);

	QRect			getDrawRect() const;
	void			setContext(CaptureContext* _context);
	CaptureContext* getContext() { return m_context; }
	Histogram*		getHistogram() { return m_histogram; }
	void			updateUI();

	void drawBackground(QPainter* _painter, const QRectF& _rect);
	
	void resizeEvent(QResizeEvent* _event);
	void mousePressEvent(QMouseEvent* _event);
	void mouseMoveEvent(QMouseEvent* _event);
	void mouseReleaseEvent(QMouseEvent* _event);
	void leaveEvent(QEvent* _event);

Q_SIGNALS:
	void binClicked();
};

#endif // RTM_MTUNER_HISTOGRAMVIEW_H
