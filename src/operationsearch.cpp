//--------------------------------------------------------------------------//
/// Copyright (c) 2018 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/operationsearch.h>

OperationSearch::OperationSearch(QWidget* _parent, Qt::WindowFlags _flags)	: 
	QWidget(_parent, _flags)
{
	ui.setupUi(this);

	m_buttonPrev	= findChild<QPushButton*>("buttonPrev");
	m_buttonNext	= findChild<QPushButton*>("buttonNext");
	m_buttonSearch	= findChild<QToolButton*>("buttonSearch");
	m_address		= findChild<QLineEdit*>("lineEditAddress");
	m_searchAddress	= findChild<QLineEdit*>("lineEditSearch");
	m_searchType	= findChild<QComboBox*>("comboBox");

	m_searchAddress->setValidator(new QRegExpValidator(QRegExp("0x?[0-9A-Fa-f]{1,16}")));

	connect(m_buttonPrev, SIGNAL(clicked()), this, SIGNAL(findPrev()));
	connect(m_buttonNext, SIGNAL(clicked()), this, SIGNAL(findNext()));
	connect(m_searchAddress, SIGNAL(textChanged(const QString&)), this, SLOT(searchStringChanged(const QString&)));
	connect(m_buttonSearch, SIGNAL(clicked()), this, SLOT(search()));
	connect(m_searchType, SIGNAL(activated(int)), this, SLOT(searchTypeChanged(int)));
}

void OperationSearch::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void OperationSearch::setPrevEnabled(bool _enabled)
{
	m_buttonPrev->setEnabled(_enabled);
}

void OperationSearch::setNextEnabled(bool _enabled)
{
	m_buttonNext->setEnabled(_enabled);
}

void OperationSearch::setAddress(uint64_t _address)
{
	QString hex = QString::number(_address,16);
	int hexLen = hex.length();
	int zeroes = 0;
	if (hexLen <= 8)
		zeroes = 8-hexLen;
	else
		zeroes = 16-hexLen;

	while (zeroes--)
		hex = "0" + hex;

	hex = "0x" + hex;
	m_address->setText(hex);
	m_address->setEnabled(true);
}

void OperationSearch::search()
{
	if (m_searchType->currentIndex()==0)
	{
		uint64_t address = m_searchAddress->text().toULongLong(0,16);
		emit searchByAddress(address);
	}
	else
	{
		uint64_t size = m_searchAddress->text().toULongLong(0,10);
		emit searchBySize(size);
	}
}

void OperationSearch::searchTypeChanged(int _type)
{
	if (_type==0)
		m_searchAddress->setValidator(new QRegExpValidator(QRegExp("0x?[0-9A-Fa-f]{1,16}")));
	else
		m_searchAddress->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,16}")));
	m_searchAddress->setText("");
}

void OperationSearch::searchStringChanged(const QString& _text)
{
	m_buttonSearch->setEnabled(_text.length()!=0);
}
