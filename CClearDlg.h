#pragma once
#include "afxdialogex.h"


// CClearDlg dialog

class CClearDlg : public CDialog
{
	DECLARE_DYNAMIC(CClearDlg)

public:
	CClearDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CClearDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
