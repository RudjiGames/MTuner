//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_OPERATIONSEARCH_H
#define RTM_MTUNER_OPERATIONSEARCH_H

#include <MTuner/.qt/qt_ui/operationsearch_ui.h>

class OperationSearch : public QWidget
{
	Q_OBJECT

	QPushButton*	m_buttonPrev;
	QPushButton*	m_buttonNext;
	QToolButton*	m_buttonSearch;
	QLineEdit*		m_address;
	QLineEdit*		m_searchAddress;
	QComboBox*		m_searchType;

public:
	OperationSearch(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void changeEvent(QEvent* _event);
	void setPrevEnabled(bool);
	void setNextEnabled(bool);
	void setAddress(uint64_t _address);

Q_SIGNALS:
	void searchByAddress(uint64_t);
	void searchBySize(uint64_t);
	void findPrev();
	void findNext();

public Q_SLOTS:
	void search();
	void searchTypeChanged(int);
	void searchStringChanged(const QString&);

private:
	Ui::OperationSearchWidget ui;
};

#endif // RTM_MTUNER_OPERATIONSEARCH_H
