//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_INJECT_H
#define RTM_MTUNER_INJECT_H

#include <MTuner/.qt/qt_ui/inject_ui.h>

class Inject : public QDialog
{
	Q_OBJECT

public:
	Inject(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);
	int	 getAllocator() { return ui.allocatorCombo->currentIndex(); }
	bool shouldCapture() { return ui.capture->isChecked(); }
	bool loadAfterCapture();

public Q_SLOTS:
	void capture(bool);
	void allocatorChanged(int);

private:
	Ui::Inject ui;
};

#endif // RTM_MTUNER_INJECT_H
