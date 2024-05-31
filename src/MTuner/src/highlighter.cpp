//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/highlighter.h>

Highlighter::Highlighter(QTextDocument* _parent)
    : QSyntaxHighlighter(_parent)
{
	HighlightingRule rule;

	m_keywordFormat.setForeground(QColor(86, 156, 214));
	QStringList keywordPatterns;
	keywordPatterns << "\\bclass\\b" << "\\bconst\\b" << "\\benum\\b" << "\\bexplicit\\b"
					<< "\\bfriend\\b" << "\\binline\\b" << "\\bnew\\b" << "\\bdelete\\b"
					<< "\\bnamespace\\b" << "\\boperator\\b" << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
					<< "\\bsignals\\b" << "\\bbreak\\b" << "\\bcase\\b" << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b" << "\\bcase\\b"
					<< "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b" << "\\bunion\\b" << "\\bvirtual\\b" << "\\breturn\\b" << "\\bvolatile\\b";
	foreach (const QString &pattern, keywordPatterns) {
		rule.m_pattern = QRegularExpression(pattern);
		rule.m_format = m_keywordFormat;
		m_highlightingRules.append(rule);
	}
	
	m_keywordFormat2.setForeground(QColor(51, 172, 174));
	QStringList keywordPatterns2;
	keywordPatterns2 << "\\bchar\\b" << "\\bdouble\\b" << "\\bint\\b" << "\\blong\\b" << "\\bnamespace\\b"
					<< "\\bshort\\b" << "\\bsigned\\b" << "\\bunsigned\\b" << "\\buint8_t\\b" << "\\buint16_t\\b" << "\\buint32_t\\b" << "\\buint64_t\\b"
					<< "\\bint8_t\\b" << "\\bint16_t\\b" << "\\bint32_t\\b" << "\\bint64_t\\b"
					<< "\\bvoid\\b" << "\\bvolatile\\b" << "\\bsize_t\\b";
	foreach (const QString &pattern, keywordPatterns2) {
		rule.m_pattern = QRegularExpression(pattern);
		rule.m_format = m_keywordFormat2;
		m_highlightingRules.append(rule);
	}

	m_preprocessorFormat.setForeground(QColor(189, 99, 197));
	rule.m_pattern = QRegularExpression("#.*");
	rule.m_format = m_preprocessorFormat;
	m_highlightingRules.append(rule);

	m_preprocessorFormat2.setForeground(QColor(155, 155, 155));
	QStringList keywordPatterns3;
	keywordPatterns3 << "\\binclude\\b" << "\\bif\\b" << "\\bifdef\\b" << "\\bifndef\\b" << "\\belif\\b"
					<< "\\bdefine\\b" << "\\bundef\\b" << "\\bifdef\\b" << "\\bifndef\\b" << "\\belse\\b" << "\\bendif\\b";
	foreach (const QString &pattern, keywordPatterns3) {
		rule.m_pattern = QRegularExpression(QString("#") + pattern);
		rule.m_format = m_preprocessorFormat2;
		m_highlightingRules.append(rule);
	}

	m_preprocessorFormat3.setForeground(QColor(255, 67, 54));
	QStringList keywordPatterns4;
	keywordPatterns4 << "\\bwarning\\b" << "\\berror\\b";
	foreach (const QString &pattern, keywordPatterns4) {
		rule.m_pattern = QRegularExpression(QString("#") + pattern);
		rule.m_format = m_preprocessorFormat3;
		m_highlightingRules.append(rule);
	}

	m_quotationFormat.setForeground(QColor(214, 157, 133));
	rule.m_pattern = QRegularExpression("\".*\"");
	rule.m_format = m_quotationFormat;
	m_highlightingRules.append(rule);

	m_includeFormat.setForeground(QColor(214, 157, 133));
	rule.m_pattern = QRegularExpression("<.*>");
	rule.m_format = m_includeFormat;
	m_highlightingRules.append(rule);

	m_functionFormat.setForeground(QColor(78, 201, 176));
	rule.m_pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
	rule.m_format = m_functionFormat;
	m_highlightingRules.append(rule);

	m_functionFormat2.setForeground(QColor(78, 201, 176));
	rule.m_pattern = QRegularExpression("\\b[A-Za-z0-9_]+::[A-Za-z0-9_]+(?=\\()");
	rule.m_format = m_functionFormat2; 
	m_highlightingRules.append(rule);

	m_functionFormat3.setForeground(QColor(78, 201, 176));
	rule.m_pattern = QRegularExpression("\\b[A-Za-z0-9_]+::~[A-Za-z0-9_]+(?=\\()");
	rule.m_format = m_functionFormat2;
	m_highlightingRules.append(rule);

	m_singleLineCommentFormat.setForeground(QColor(86, 164, 51));
	rule.m_pattern = QRegularExpression("//[^\n]*");
	rule.m_format = m_singleLineCommentFormat;
	m_highlightingRules.append(rule);

	m_multiLineCommentFormat.setForeground(QColor(86, 164, 51));
}

void Highlighter::highlightBlock(const QString& _text)
{
    foreach (const HighlightingRule &rule, m_highlightingRules) {
		QRegularExpression expression(rule.m_pattern);
        QRegularExpressionMatch match = expression.match(_text);

		int last = match.lastCapturedIndex();
        while (last >= 0) {
            int length = match.capturedLength(last);
			int index = match.capturedStart(last);
			setFormat(index, length, rule.m_format);
            --last;
        }
	}

	QRegularExpression comment("/\\*(.*?)\\*/", QRegularExpression::DotMatchesEverythingOption);

	QRegularExpressionMatch matches = comment.match(_text);
	for (int i=0; i<matches.lastCapturedIndex(); i++) {
		int length = matches.capturedLength(i);
		int index = matches.capturedStart(i);
		setFormat(index, length, m_multiLineCommentFormat);
	}
	setCurrentBlockState(0);
}
