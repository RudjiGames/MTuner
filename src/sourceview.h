//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_SOURCEVIEW_H
#define RTM_MTUNER_SOURCEVIEW_H

#include <MTuner/src/loader/capture.h>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;
class ExternalEditor;
struct CaptureContext;

class SourceView : public QPlainTextEdit
{
	Q_OBJECT

	QString			m_currentFile;
	int				m_currentLine;
	QMenu*			m_contextMenu;
	QAction*		m_tabWidthAction4;
	QAction*		m_tabWidthAction8;
	QAction*		m_openInEditorAction;
	ExternalEditor*	m_editorDialog;
	CaptureContext*	m_context;

public:
	SourceView(QWidget* _parent = 0);

	void changeEvent(QEvent* _event);
	void lineNumberAreaPaintEvent(QPaintEvent* _event);
	int  lineNumberAreaWidth();
	void setTabWidth(int _width);
	void setEditorDialog(ExternalEditor* _editor) { m_editorDialog = _editor; }
	void setContext(CaptureContext* _context) { m_context = _context; }

protected:
	void contextMenuEvent(QContextMenuEvent* _event);
	void resizeEvent(QResizeEvent* _event);
	void createCustomContextMenu();

private Q_SLOTS:
	void updateLineNumberAreaWidth(int _newBlockCount);
	void highlightCurrentLine();
	void updateLineNumberArea(const QRect&, int);
	void openFile(const QString& _file, int _row, int _column);
	void setTabWidthTo4();
	void setTabWidthTo8();
	void openInEditor();

private:
	QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
{
private:
	SourceView* m_sourceView;

public:
	LineNumberArea(SourceView* _editor) :
		QWidget(_editor)
	{
		m_sourceView = _editor;
	}

	QSize sizeHint() const
	{
		return QSize(m_sourceView->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent* _event)
	{
		m_sourceView->lineNumberAreaPaintEvent(_event);
	}
};

#endif // RTM_MTUNER_SOURCEVIEW_H
