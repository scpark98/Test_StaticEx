#pragma once

#include <afxwin.h>
#include <gdiplus.h>
#include <deque>

/*
[text coloring 지원 예정]
* paragraph data 구조체
	LOGFONT : 글꼴, 크기, 스타일
	Gdiplus::Color : 글자색, 배경색
	CString : 텍스트
	int : align
* 설정방식(html tag style ? own style ? )
m_static.set_text(_T("<font <b><12><i><
	* 저장방식
	*
*/

class CSCParagraph
{
public:
	CSCParagraph();
	~CSCParagraph();

	Gdiplus::Color	cr_text;		//<cr>
	Gdiplus::Color	cr_back;		//<crb>

	CString			text;
	CString 		font_name;		//<font_name>
	int				size;			//<size=12>
	bool			bold;			//<b>
	bool			italic;			//<i>
	bool			underline;		//<u>
	bool			strike;			//<s>

protected:
};
