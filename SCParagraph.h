#pragma once

#include <afxwin.h>
#include <gdiplus.h>
#include <deque>

/*
[text coloring ���� ����]
* paragraph data ����ü
	LOGFONT : �۲�, ũ��, ��Ÿ��
	Gdiplus::Color : ���ڻ�, ����
	CString : �ؽ�Ʈ
	int : align
* �������(html tag style ? own style ? )
m_static.set_text(_T("<font <b><12><i><
	* ������
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
