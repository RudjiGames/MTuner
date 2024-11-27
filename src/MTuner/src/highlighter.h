//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_HIGHLIGHTER_H
#define RTM_MTUNER_HIGHLIGHTER_H

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument* _parent = 0);

protected:
    void highlightBlock(const QString& _text);

private:
    struct HighlightingRule
    {
		QRegularExpression		m_pattern;
        QTextCharFormat			m_format;
    };

    QVector<HighlightingRule>	m_highlightingRules;
    QTextCharFormat				m_keywordFormat;
    QTextCharFormat				m_keywordFormat2;
    QTextCharFormat				m_classFormat;
    QTextCharFormat				m_singleLineCommentFormat;
    QTextCharFormat				m_multiLineCommentFormat;
    QTextCharFormat				m_quotationFormat;
	QTextCharFormat				m_includeFormat;
    QTextCharFormat				m_functionFormat;
	QTextCharFormat				m_functionFormat2;
	QTextCharFormat				m_functionFormat3;
	QTextCharFormat				m_preprocessorFormat;
	QTextCharFormat				m_preprocessorFormat2;
	QTextCharFormat				m_preprocessorFormat3;
};

#endif // RTM_MTUNER_HIGHLIGHTER_H
