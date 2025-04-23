// SCParagraphStatic.cpp: 구현 파일
//

#include "SCParagraphStatic.h"
#include "../../Common/Functions.h"
#include "../../Common/MemoryDC.h"

// CSCParagraphStatic

IMPLEMENT_DYNAMIC(CSCParagraphStatic, CSCStatic)

CSCParagraphStatic::CSCParagraphStatic()
{
	int sz = sizeof(LOGFONT);
}

CSCParagraphStatic::~CSCParagraphStatic()
{
}


BEGIN_MESSAGE_MAP(CSCParagraphStatic, CSCStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CSCParagraphStatic 메시지 처리기
CRect CSCParagraphStatic::set_text(CString text, Gdiplus::Color cr_text_color /*-1*/)
{
	m_paragraph.clear();

	int i;
	CString str;
	std::deque<CString> tags;

	//"<b><cr = Red>This</b></cr > is a <cr =Blue><i>sample</i> <b>paragraph</b>."
	get_tag_str(text, tags);

	CSCParagraph basic_para, para;
	basic_para.font_name = m_lf.lfFaceName;
	basic_para.bold = (m_lf.lfWeight == FW_BOLD);
	basic_para.size = get_font_size_from_pixel_size(m_hWnd, m_lf.lfHeight);
	basic_para.italic = m_lf.lfItalic;
	basic_para.strike = m_lf.lfStrikeOut;
	basic_para.underline = m_lf.lfUnderline;
	basic_para.cr_text = m_cr_text;
	basic_para.cr_back = m_cr_back;

	para = basic_para;

	//시작 태그를 만나면 속성을 세팅하고
	//단순 텍스트를 만나면 해당 속성과 함께 paragraph로 push하고
	//끝 태그를 만나면 끝 태그가 끝날때까지 진행하고 끝 태그를 만나면 그 속성을 해제한다. 
	for (i = 0; i < tags.size(); i++)
	{
		if (tags[i] == _T("<b>"))
		{
			para.bold = true;
		}
		else if (tags[i] == _T("</b>"))
		{
			para.bold = basic_para.bold;
		}
		else if (tags[i] == _T("<i>"))
		{
			para.italic = true;
		}
		else if (tags[i] == _T("</i>"))
		{
			para.italic = basic_para.italic;
		}
		else if (tags[i] == _T("<u>"))
		{
			para.underline = true;
		}
		else if (tags[i] == _T("</u>"))
		{
			para.underline = basic_para.underline;
		}
		else if (tags[i] == _T("<s>"))
		{
			para.strike = true;
		}
		else if (tags[i] == _T("</s>"))
		{
			para.strike = basic_para.strike;
		}
		else if (tags[i].Find(_T("<cr=")) >= 0)
		{
			CString str_color = tags[i].Mid(4, tags[i].GetLength() - 5);
			para.cr_text = get_color(CString2string(str_color));
		}
		else if (tags[i].Find(_T("</cr>")) >= 0)
		{
			para.cr_text = basic_para.cr_text;
		}
		else if (tags[i].Find(_T("<crb=")) >= 0)
		{
			CString str_color = tags[i].Mid(4, tags[i].GetLength() - 5);
			para.cr_back = get_color(CString2string(str_color));
		}
		else if (tags[i].Find(_T("</crb>")) >= 0)
		{
			para.cr_back = basic_para.cr_back;
		}
		else
		{
			para.text = tags[i];
			m_paragraph.push_back(para);
		}
	}

	//"<b><cr = Red>This</b></cr > is a <cr =Blue><i>sample</i> <b>paragraph</b>."
	//recalc_text_size();

	return m_rect_text;
}


void CSCParagraphStatic::OnPaint()
{
	CPaintDC dc1(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CSCStatic::OnPaint()을(를) 호출하지 마십시오.
	CRect rc;

	GetClientRect(&rc);

	CMemoryDC dc(&dc1, &rc);

	CFont font, * pOldFont;
	LOGFONT lf;

	memcpy(&lf, &m_lf, sizeof(LOGFONT));

	for (int i = 0; i < m_paragraph.size(); i++)
	{
		//font.CreateFontIndirect(&m_lf);
		font.CreateFont((m_paragraph[i].size, 0, 0, 0, m_paragraph[i].bold ? FW_BOLD : FW_NORMAL,
			m_paragraph[i].italic, m_paragraph[i].underline, m_paragraph[i].strike,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_QUALITY, m_paragraph[i].font_name);
		pOldFont = (CFont*)dc.SelectObject(&font);
		dc.SetTextColor(m_paragraph[i].cr_text.ToCOLORREF());
		dc.SetBkColor(m_paragraph[i].cr_back.ToCOLORREF());
		dc.DrawText(m_paragraph[i].text, m_rect_text, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
		dc.SelectObject(pOldFont);
	}
}
