
// Test_StaticExDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "../../Common/CStatic/StaticEx.h"

// CTest_StaticExDlg dialog
class CTest_StaticExDlg : public CDialogEx
{
// Construction
public:
	CTest_StaticExDlg(CWnd* pParent = NULL);	// standard constructor

	double	m_hue;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_STATICEX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStaticEx m_static[10];
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMarquee();
	afx_msg void OnBnClickedButtonGrayUp();
	afx_msg void OnBnClickedButtonWhiteUp();
	CStatic m_static_gray;
	CStatic m_static_white;
};
