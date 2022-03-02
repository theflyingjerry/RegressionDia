
// RegressionDiaDlg.h : header file
//

#pragma once


// CRegressionDiaDlg dialog
class CRegressionDiaDlg : public CDialogEx
{
// Construction
public:
	CRegressionDiaDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGRESSIONDIA_DIALOG };
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
private:
	//Doc Type Varaiable and Info
	enum DocumentType{None, Text};

	DocumentType m_documentType{ DocumentType::None };
	
	bool updated{ false };

	//Data Variables
	int n;
	double* X = NULL;
	double* Y = NULL;
	bool dataRead{ false };

	//Variables to scale to graph
	double m_x_scale = 0;
	double m_y_scale = 0;

	//Regression data
	bool regressed{ false };
	float coeff;
	float constantTerm;
	float errorSq;



public:
	afx_msg void OnBnClickedButtonOpenFile();
	
private:
	//Label Variables with text boxes
	CString m_GraphTitle;
	CString m_GraphX;
	CString m_GraphY;
private:
	int ScaleX(double);
	int ScaleY(double);
	void RegressionAnalysis();
public:
	afx_msg void OnBnClickedButtonRegression();
	
	
	afx_msg void OnBnClickedButtonSaveFile();
	
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedClear();
};
