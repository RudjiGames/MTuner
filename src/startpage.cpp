//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <mtuner_pch.h>
#include <mtuner/src/startpage.h>
#include <mtuner/src/version.h>

static QString getMessage(const QString& _string)
{
	return QString("<html><head/><body><p><span style=\" font-size:16pt; font-weight:600; color:#787896;\">") + 
			_string + QString("</span></p></body></html>");
}

StartPageWidget::StartPageWidget(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);
	ui.label_version->setText(getMessage(QString("v") + QString(MTunerVersion)));
}

void StartPageWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}
