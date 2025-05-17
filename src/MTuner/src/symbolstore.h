//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_SYMBOLSTORE_H
#define RTM_MTUNER_SYMBOLSTORE_H

#include <MTuner/.qt/qt_ui/symbolstore_ui.h>

class SymbolStore : public QDialog
{
	Q_OBJECT

private:
	QCheckBox*		m_srcRegistry;
	QLineEdit*		m_localStore;
	QLineEdit*		m_publicStore;
	QToolButton*	m_buttonDefault;
	QToolButton*	m_buttonBrowse;
	bool			m_hasRegistryEntry;
	bool			m_restoreRegistryChecked;
	QString			m_restorePublicStore;
	QString			m_restoreLocalStore;

public:
	SymbolStore(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void	changeEvent(QEvent* _event);
	QString	getSymbolStoreString() const;
	QString	getLocalStore() const;
	void	setLocalStore(const QString& _localStore);
	QString	getPublicStore() const;
	void	setPublicStore(const QString& _publicStore);
	bool	isRegistryChecked() const;
	void	setChecked(bool _registry);
	void	save();

public Q_SLOTS:
	void	selectLocalStore();
	void	defaultSymbolServer();
	void	visitMSDN();

	virtual int exec();
	virtual void accept();
	virtual void reject();

private:
	Ui::SymbolStoreDialog ui;
};

#endif // RTM_MTUNER_SYMBOLSTORE_H
