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

class CParagraphData
{
public:
	CParagraphData();
	~CParagraphData();

	//한번 paragraph값이 정해진 후 유효한 멤버값이 아닌 상태로 새로운 paragraph가 들어와도
	//그 스타일에는 변화없이 유지된다.
	//ex. add("<font size=12><font bold = 1>first line") 입력된 후
	//add("second line")이면 이 때 스타일은 전 스타일값을 그대로 유지한다.

	//<font name = "맑은 고딕"><font size=12><font bold = 1>
	LOGFONT*		lf = NULL;

	//<font color = RGB(255, 0, 0)> <font color = gRGB(255, 0, 0)> <font color = Gdiplus::Color(255, 0, 0)>
	Gdiplus::Color	cr_text = -1;

	//<back color = RGB(0, 0, 255)>
	Gdiplus::Color	cr_back = -1;

	CString			text;
	int				align = -1;
	int				height = -1;
};

class CParagraph
{
public:
	CParagraph();
	~CParagraph();

	void			add(CString data);

protected:
	std::deque<CParagraphData*> m_data;
	DWORD			get_value(CString data, CString tag_name, int start = 0);
};
