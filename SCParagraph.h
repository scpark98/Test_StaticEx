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

class CParagraphData
{
public:
	CParagraphData();
	~CParagraphData();

	//�ѹ� paragraph���� ������ �� ��ȿ�� ������� �ƴ� ���·� ���ο� paragraph�� ���͵�
	//�� ��Ÿ�Ͽ��� ��ȭ���� �����ȴ�.
	//ex. add("<font size=12><font bold = 1>first line") �Էµ� ��
	//add("second line")�̸� �� �� ��Ÿ���� �� ��Ÿ�ϰ��� �״�� �����Ѵ�.

	//<font name = "���� ���"><font size=12><font bold = 1>
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
