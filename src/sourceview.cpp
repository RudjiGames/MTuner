//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/mtuner.h>
#include <MTuner/src/sourceview.h>
#include <MTuner/src/highlighter.h>
#include <MTuner/src/external_editor.h>
#include <MTuner/src/capturecontext.h>

SourceView::SourceView(QWidget* _parent) : 
	QPlainTextEdit(_parent)
{
	lineNumberArea			= new LineNumberArea(this);
	m_contextMenu			= NULL;
	m_tabWidthAction4		= NULL;
	m_tabWidthAction8		= NULL;
	m_openInEditorAction	= NULL;
	m_editorDialog			= NULL;
	m_context				= NULL;

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	updateLineNumberAreaWidth(0);

	QFont font;
	font.setFamily("Consolas");
	font.setFixedPitch(true);
	font.setPointSize(10);

	setFont(font);
	lineNumberArea->setFont(font);
	setReadOnly(true);
	setWordWrapMode(QTextOption::NoWrap);
	setCenterOnScroll(true);
	setTabWidth(4);

	new Highlighter(document());

	createCustomContextMenu();
}

void SourceView::changeEvent(QEvent* _event)
{
	QPlainTextEdit::changeEvent(_event);
	switch (_event->type())
	{
		case QEvent::LanguageChange:
			if (m_tabWidthAction4) m_tabWidthAction4->setText(QObject::tr("Set tab width to 4"));
			if (m_tabWidthAction8) m_tabWidthAction8->setText(QObject::tr("Set tab width to 8"));
			if (m_openInEditorAction) m_openInEditorAction->setText(QObject::tr("Open in editor"));
			break;
		default:
			break;
	};
}

int SourceView::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10)
	{
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
	return space;
}

void SourceView::setTabWidth(int _width)
{
	setTabStopWidth(fontMetrics().width(QLatin1Char(' ')) * _width);
}

void SourceView::createCustomContextMenu()
{
	m_tabWidthAction4 = new QAction(QObject::tr("Set tab width to 4"),this);
	m_tabWidthAction4->setCheckable(true);
	m_tabWidthAction4->setChecked(true);

	m_tabWidthAction8 = new QAction(QObject::tr("Set tab width to 8"),this);
	m_tabWidthAction8->setCheckable(true);
	m_tabWidthAction8->setChecked(false);

	m_openInEditorAction = new QAction(QObject::tr("Open in editor"),this);
	m_openInEditorAction->setEnabled(false);

	connect(m_tabWidthAction4, SIGNAL(triggered()), this, SLOT(setTabWidthTo4()));
	connect(m_tabWidthAction8, SIGNAL(triggered()), this, SLOT(setTabWidthTo8()));
	connect(m_openInEditorAction, SIGNAL(triggered()), this, SLOT(openInEditor()));
}

void SourceView::updateLineNumberAreaWidth(int _newBlockCount)
{
	RTM_UNUSED(_newBlockCount);
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void SourceView::updateLineNumberArea(const QRect& _rect, int _dy)
{
	if (_dy)
		lineNumberArea->scroll(0, _dy);
	else
		lineNumberArea->update(0, _rect.y(), lineNumberArea->width(), _rect.height());

	if (_rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}

void SourceView::openFile(const QString& _file, int _row, int _col)
{
	RTM_UNUSED(_col);
	QFile file(_file);
	if (file.open(QFile::ReadOnly | QFile::Text))
	{
		m_currentFile = _file;
		m_currentLine = _row;
		setPlainText(file.readAll());
		m_openInEditorAction->setEnabled(true);
		file.close();
	}
	else
	{
		bool set = false;
		if (m_context)
		{
			QString symDir(QString::fromUtf8(m_context->getSymbolStoreDir().c_str()));
			QDir symD = symDir;

			QFileInfo info(symD, _file);
			if (info.exists())
			{
				QFile fileRel(info.absoluteFilePath());
				if (fileRel.open(QFile::ReadOnly | QFile::Text))
				{
					m_currentFile = info.absoluteFilePath();
					m_currentLine = _row;
					setPlainText(fileRel.readAll());
					m_openInEditorAction->setEnabled(true);
					fileRel.close();
					set = true;
				}
			}
		}

		if (!set)
		{
			m_currentFile = "";
			m_currentLine = -1;
			setPlainText("");
			m_openInEditorAction->setEnabled(false);
		}
	}

	if (m_currentLine != -1)
	{
		QTextCursor cursor = textCursor();
		cursor.setPosition(0, QTextCursor::KeepAnchor);
		cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor, _row-1);
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		setTextCursor(cursor);
		highlightCurrentLine();
	}
	else
	{
		QTextCursor cursor = textCursor();
		cursor.setPosition(0, QTextCursor::MoveAnchor);
		setTextCursor(cursor);
		setExtraSelections(QList<QTextEdit::ExtraSelection>());
	}
}

void SourceView::contextMenuEvent(QContextMenuEvent* _event)
{
	QMenu *menu = createStandardContextMenu();
	menu->addAction(m_tabWidthAction4);
	menu->addAction(m_tabWidthAction8);
	menu->addAction(m_openInEditorAction);
	menu->exec(mapToGlobal(_event->pos()));
}

void SourceView::resizeEvent(QResizeEvent* _event)
{
	QPlainTextEdit::resizeEvent(_event);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void SourceView::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	QColor lineColor = QColor(121,121,124);

	QTextEdit::ExtraSelection selection;
	selection.format.setBackground(lineColor);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
	selection.cursor = textCursor();
	selection.cursor.clearSelection();
	extraSelections.append(selection);
	setExtraSelections(extraSelections);
}

void SourceView::lineNumberAreaPaintEvent(QPaintEvent* _event)
{
	QPainter painter(lineNumberArea);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= _event->rect().bottom() && m_currentFile != "")
	{
		if (block.isVisible() && bottom >= _event->rect().top())
		{
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::gray);
			painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}

void SourceView::setTabWidthTo4()
{
	m_tabWidthAction4->setChecked(true);
	m_tabWidthAction8->setChecked(false);
	setTabWidth(4);
}

void SourceView::setTabWidthTo8()
{
	m_tabWidthAction8->setChecked(true);
	m_tabWidthAction4->setChecked(false);
	setTabWidth(8);
}

void SourceView::openInEditor()
{
	QString args = m_editorDialog->getEditorArgs();
	args.replace("%F", m_currentFile);

	QTextCursor cursor = textCursor();
	int y = cursor.blockNumber() + 1;
	args.replace("%L", QString::number(y));
	
	QProcess* launchEditor = new QProcess(this);
	launchEditor->start("\"" + m_editorDialog->getEditorPath() + "\" " + args);
	if (!launchEditor->waitForStarted())
	{
		int r = QMessageBox::question(this, tr("Failed to start editor!"), tr("Setup external editor now?"), QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
		if (r == QMessageBox::Yes)
		{
			m_editorDialog->run();
			openInEditor();
		}
	}
	launchEditor->close();
}
