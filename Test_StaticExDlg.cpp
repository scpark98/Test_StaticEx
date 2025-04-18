
// Test_StaticExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test_StaticEx.h"
#include "Test_StaticExDlg.h"
#include "afxdialogex.h"

#include "../../Common/Functions.h"
#include "../../Common/image_processing/hsl/hsl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTest_StaticExDlg dialog



CTest_StaticExDlg::CTest_StaticExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_STATICEX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_StaticExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_static[0]);
	DDX_Control(pDX, IDC_STATIC2, m_static[1]);
	DDX_Control(pDX, IDC_STATIC3, m_static[2]);
	DDX_Control(pDX, IDC_STATIC4, m_static[3]);
	DDX_Control(pDX, IDC_STATIC5, m_static[4]);
	DDX_Control(pDX, IDC_STATIC6, m_static[5]);
	DDX_Control(pDX, IDC_STATIC7, m_static[6]);
	DDX_Control(pDX, IDC_STATIC8, m_static[7]);
	DDX_Control(pDX, IDC_STATIC9, m_static[8]);
	DDX_Control(pDX, IDC_STATIC10, m_static[9]);
	DDX_Control(pDX, IDC_STATIC_GRAY, m_static_gray);
	DDX_Control(pDX, IDC_STATIC_WHITE, m_static_white);
	DDX_Control(pDX, IDC_STATIC_AUTO_FONT_SIZE, m_static_auto_font_size);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_static_image);
	DDX_Control(pDX, IDC_CHECK_MIRROR, m_check_mirror);
	DDX_Control(pDX, IDC_STATIC_LINK, m_static_link);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_static_title);
}

BEGIN_MESSAGE_MAP(CTest_StaticExDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTest_StaticExDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTest_StaticExDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MARQUEE, &CTest_StaticExDlg::OnBnClickedButtonMarquee)
	ON_BN_CLICKED(IDC_BUTTON_GRAY_UP, &CTest_StaticExDlg::OnBnClickedButtonGrayUp)
	ON_BN_CLICKED(IDC_BUTTON_WHITE_UP, &CTest_StaticExDlg::OnBnClickedButtonWhiteUp)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_CHECK_MIRROR, &CTest_StaticExDlg::OnBnClickedCheckMirror)
END_MESSAGE_MAP()


// CTest_StaticExDlg message handlers

BOOL CTest_StaticExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_resize.Create(this);
	m_resize.Add(IDC_STATIC_AUTO_FONT_SIZE, 0, 0, 50, 100);
	m_resize.Add(IDC_STATIC_IMAGE, 50, 0, 50, 100);
	m_resize.Add(IDC_CHECK_MIRROR, 50, 100, 0, 0);
	m_resize.Add(IDC_STATIC_LINK, 0, 100, 0, 0);

	CWinApp* pApp = &theApp;

	OnBnClickedOk();
	m_hue = 0.0;
	SetTimer(0, 10, NULL);

	RestoreWindowPosition(&theApp, this);

	m_static_title.set_back_color(Gdiplus::Color::Beige);
	m_static_title.set_round(22, Gdiplus::Color::Gray, get_sys_color(COLOR_3DFACE));

	m_static_auto_font_size.set_font_name(_T("D2Coding"));
	m_static_auto_font_size.set_font_italic();
	m_static_auto_font_size.set_font_size(36);
	m_static_auto_font_size.set_auto_font_size();
	m_static_auto_font_size.set_back_color(Gdiplus::Color::Pink);

	//m_static_image.set_back_color(Gdiplus::Color::Red);
	m_static_image.set_back_image(_T("GIF"), IDR_GIF_NOTEBOOK, Gdiplus::Color::White);
	m_static_image.fit_to_back_image(false);

	//각 라인별로 글자색, 크기, 간격을 다양하게 출력. html의 <color>와 같은 태그 방식? struct?
	
	m_static_link.set_link(_T("https://google.com"));

	for (int i = 100; i <= 600; i++)
	{
		TRACE(_T("get_error_str %d = %s\n"), i, get_error_str(i));
		TRACE(_T("GetSystemErrorMesssage %d = %s\n"), i, CString(GetSystemErrorMesssage(i).c_str()));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTest_StaticExDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTest_StaticExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTest_StaticExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTest_StaticExDlg::OnBnClickedOk()
{
	m_static_image.pause_gif(-1);

	int i;

	for (i = 0; i < 6; i++)
	{
		COLORREF cr = get_random_color();
		m_static[i].set_text_color(cr);
		//m_static[i].SetBackColor(color_complementary(cr));
		m_static[i].set_font_size(10);
	}

	m_static[0].add_header_image(IDB_CONFIG_CYAN);
	m_static[1].add_header_image(IDB_CONFIG_CYAN, true);

	for (i = 6; i < 9; i++)
	{
		m_static[i].set_font_size(10);
		m_static[i].set_prefix_space();
		if (i % 2 == 0)
		{
			m_static[i].set_icon(IDR_MAINFRAME, 32);
			//if (i == 6)
			//	m_static[i].set_gradient_color(get_random_color());
			//else
			//	m_static[i].set_gradient_color(GetSysColor(COLOR_3DFACE), get_random_color());
		}
		else
		{
			//m_static[i].set_vertical_gradient();
			m_static[i].set_icon(IDR_MAINFRAME, 16, true);
			//m_static[i].set_gradient_color(get_random_color(), get_random_color());
		}
	}

	//m_static[9].SetVerticalGradient();
	m_static[9].set_gradient_color(blue, darkblue, GRAY(128), GRAY(212), GRAY(128), blue);
}


void CTest_StaticExDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CTest_StaticExDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0)
	{
		if (m_hue < 360.0)
			m_hue += 1.0;
		else
			m_hue = 0.0;

		COLORREF cr = m_static[0].get_back_color().ToCOLORREF();
		HSL hsl(cr);
		hsl.SetHue(m_hue);
		cr = hsl.GetRGB();
		m_static[0].set_back_color(RGB2gpColor(cr));
		m_static[0].set_text_color(RGB2gpColor(color_complementary(cr)));
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CTest_StaticExDlg::OnBnClickedButtonMarquee()
{
}


void CTest_StaticExDlg::OnBnClickedButtonGrayUp()
{
	m_static_gray.ShowWindow(SW_HIDE);
	m_static_gray.SetWindowPos(&m_static_white, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_static_gray.ShowWindow(SW_SHOW);
}


void CTest_StaticExDlg::OnBnClickedButtonWhiteUp()
{
	m_static_white.ShowWindow(SW_HIDE);
	m_static_white.SetWindowPos(&m_static_gray, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_static_white.ShowWindow(SW_SHOW);
}


void CTest_StaticExDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveWindowPosition(&theApp, this);
}


void CTest_StaticExDlg::OnBnClickedCheckMirror()
{
	m_static_image.set_back_image_mirror(m_check_mirror.GetCheck());
}
