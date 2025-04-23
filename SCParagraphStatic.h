#pragma once

#include <deque>
#include "../../Common/CStatic/SCStatic/SCStatic.h"
#include "SCParagraph.h"


// CSCParagraphStatic
class CSCParagraphStatic : public CSCStatic
{
	DECLARE_DYNAMIC(CSCParagraphStatic)

public:
	CSCParagraphStatic();
	virtual ~CSCParagraphStatic();

	//태그는 소문자로, 컬러값은 Gdiplus::Color에 정의된 이름을 사용함을 원칙으로 한다.
	//"<b><cr = red>This</b></cr > is a <cr =Blue><i>sample</i> <b>paragraph</b>."
	CRect			set_text(CString sText, Gdiplus::Color cr_text = Gdiplus::Color::Transparent);


protected:
	std::deque<CSCParagraph> m_paragraph;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

