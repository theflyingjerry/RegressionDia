
// RegressionDiaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RegressionDia.h"
#include "RegressionDiaDlg.h"
#include "afxdialogex.h"
#include "CClearDlg.h"
#include < stdlib.h >

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
public:
	
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


// CRegressionDiaDlg dialog



CRegressionDiaDlg::CRegressionDiaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGRESSIONDIA_DIALOG, pParent)
	
	, m_GraphTitle(_T(""))
	, m_GraphX(_T(""))
	, m_GraphY(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegressionDiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_GraphTitle);
	DDX_Text(pDX, IDC_EDIT2, m_GraphX);
	DDX_Text(pDX, IDC_EDIT3, m_GraphY);
}

BEGIN_MESSAGE_MAP(CRegressionDiaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CRegressionDiaDlg::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_REGRESSION, &CRegressionDiaDlg::OnBnClickedButtonRegression)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FILE, &CRegressionDiaDlg::OnBnClickedButtonSaveFile)
	ON_BN_CLICKED(IDC_CLEAR, &CRegressionDiaDlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CRegressionDiaDlg message handlers

BOOL CRegressionDiaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRegressionDiaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRegressionDiaDlg::OnPaint()
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
		CPaintDC dc(this);
		//Add Graph Axes
		CPoint Origin(100, 550);
		CPoint EndY(100, 50);
		CPoint EndX(600, 550);

		dc.MoveTo(Origin);
		dc.LineTo(EndY);

		dc.MoveTo(Origin);
		dc.LineTo(EndX);

		//Add Hash Marks for X and Y Axes
		for (int i = 150; i < 650; i += 50) {
			CPoint hashs(i, 545);
			CPoint hashe(i, 555);
			dc.MoveTo(hashs);
			dc.LineTo(hashe);
		}
		for (int i = 50; i < 550; i += 50) {
			CPoint hashs(95, i);
			CPoint hashe(105, i);
			dc.MoveTo(hashs);
			dc.LineTo(hashe);
		}

		if (m_documentType == DocumentType::Text) {

			//Add Title and Axes Labels
			dc.TextOutW(290, 7, m_GraphTitle);
			dc.TextOutW(290, 600, m_GraphX);

			//Add Y Axis Label with rotated fpnt
			CFont Font;
			Font.CreateFont(18, 0, 900, 900,
				0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
			CFont* pFont = dc.SelectObject(&Font);
			CRect rectClient;
			GetClientRect(rectClient);
			dc.TextOutW(10,390,m_GraphY);
			dc.SelectObject(pFont);
			Font.DeleteObject();
			

			//Add values to hashmarks
			CString a,b,c,d;
			a.Format(_T("%d"), int(m_x_scale));
			b.Format(_T("%d"), int(m_x_scale/2));
			c.Format(_T("%d"), int(m_y_scale/2));
			d.Format(_T("%d"), int(m_y_scale));

			dc.TextOutW(580, 565, a);
			dc.TextOutW(340, 565, b);
			dc.TextOutW(60, 300, c);
			dc.TextOutW(60, 50, d);
				

			//Scale and Plot Data Points
			for (int i = 0; i < n; i++) {
				int xp = ScaleX(X[i]);
				int yp = ScaleY(Y[i]);
				
				dc.Ellipse((xp - 5), (yp - 5), (xp + 5), (yp + 5));
			}

			//Plot Regression Line
			if (regressed) {
				int yint = ScaleY(constantTerm);
				int yend = ScaleY((coeff * m_x_scale + constantTerm));
					
				dc.MoveTo(100, yint);
				dc.LineTo(600, yend);
			}
				
		}
	}
		
	CDialogEx::OnPaint();
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRegressionDiaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRegressionDiaDlg::OnBnClickedButtonOpenFile()
{
	//Add Filter for data
	LPCTSTR pszFilter =
		_T("Text (*.txt)|*.txt|");

	//Create file type variable for selected file 
	if(!dataRead){
	CFileDialog dlgFile(TRUE, _T("text"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, pszFilter, AfxGetMainWnd());

	//If file selected:
	if (IDOK == dlgFile.DoModal()) {
		//Try and read
		try {
			//Read as text
			CStdioFile file(dlgFile.GetPathName(), CFile::modeRead | CFile::typeText);
			//Ensure data is read
			bool succesful{ false };
			//Read data line by line and assign to class variables
			if (dlgFile.GetFileExt() == _T("txt")) {
				CString coordinate;
				if (file.ReadString(coordinate)) {
					m_GraphTitle = coordinate;
					SetDlgItemText(IDC_EDIT1, m_GraphTitle);
					if (file.ReadString(coordinate)) {
						m_GraphX = coordinate;
						SetDlgItemText(IDC_EDIT2, m_GraphX);
						if (file.ReadString(coordinate)) {
							m_GraphY = coordinate;
							SetDlgItemText(IDC_EDIT3, m_GraphY);
							if (file.ReadString(coordinate)) {
								n = _ttoi(coordinate);
								//Reset X & Y if not empty
								if (X == NULL || Y == NULL) {
									X = new double[n];
									Y = new double[n];
								}
								else {
									delete[] X;
									delete[] Y;
									X = new double[n];
									Y = new double[n];
								}
								//Read by line until done 
								for (int i = 0; i < n; i++) {
									if (file.ReadString(coordinate)) {
										int j = 0;
										CString tok = _T("");
										//Make sub strings of each line and assign first to x and second to y
										while (AfxExtractSubString(tok, coordinate, j, ',')) {
											if (j == 0) {
												X[i] = _ttoi(tok);
											}
											else if (j == 1) {
												Y[i] = _ttoi(tok);
											}
											j++;
										}
										//Find largest data to use as scale
										if (X[i] >= m_x_scale) {
											m_x_scale = X[i];
										}
										if (Y[i] >= m_y_scale) {
											m_y_scale = Y[i];
										}
									}
								}
								//Set doc type for later and succesful read
								m_documentType = DocumentType::Text;
								succesful = true;
								regressed = false;
							}
						}
					}
				}
			}
			//Alert user read failed
			if (!succesful) {
				AfxMessageBox(_T("Error reading text type file"));
			}
			//Update
			if (succesful) {
				dataRead = true;
				Invalidate();
				UpdateWindow();
			}
		}
		catch (CFileException* pe)
		{
			TRACE(_T("File could not be opened, cause = %d\n"),
				pe->m_cause);
			pe->Delete();
		}
	}
	}
}

void CRegressionDiaDlg::OnBnClickedButtonRegression(){
	RegressionAnalysis();
	//update windows
	regressed = true;
	m_documentType = DocumentType::Text;
	Invalidate();
	UpdateWindow();
}

void CRegressionDiaDlg::RegressionAnalysis() {
	//Check if Data has been read
	if (dataRead && !regressed) {
		//Initialze some variables
		coeff = 0;
		constantTerm = 0;
		double sum_x = 0;
		double sum_y = 0;
		double sum_x_sqrtd = 0;
		double sum_y_sqrtd = 0;
		double sum_xy = 0;
		double numerator = 0;
		double denominator = 0;

		//Set variables based on data
		for (int i = 0; i < n; i++) {
			sum_x += X[i];
			sum_y += Y[i];
			sum_x_sqrtd += X[i] * X[i];
			sum_y_sqrtd += Y[i] * Y[i];
			sum_xy += X[i] * Y[i];
		}

		//Calculate Coeffecient
		numerator = (n * sum_xy - sum_x * sum_y);
		denominator = (n * sum_x_sqrtd - sum_x * sum_x);
		coeff = numerator / denominator;

		//Calculate Constant Term
		numerator = (sum_y * sum_x_sqrtd - sum_x * sum_xy);
		denominator = (n * sum_x_sqrtd - sum_x * sum_x);
		constantTerm = numerator / denominator;

		//Calculate Error
		
		//Can Produce round off error?
		double xAn;
		for (int j = 0; j < n; j++) {
			xAn = coeff * X[j] + constantTerm;
			errorSq += ((xAn - Y[j]) * (xAn - Y[j]));
		}
		

	} else {
		AfxMessageBox(_T("Regession analysis unvailable - no Data is imported"));
	}

}

int CRegressionDiaDlg::ScaleX(double in) {
	int result = ((500 / m_x_scale) * in) + 100;
	return result;
}

int CRegressionDiaDlg::ScaleY(double in) {
	int result = ((500 / m_y_scale) * in);
	if (result < 250) {
		result = 250 + (250 - result) + 50;
	}
	else {
		result = 250 - (result - 250) + 50;
	}
	return result;
}

void CRegressionDiaDlg::OnBnClickedButtonSaveFile()
{
	// TODO: Add your control notification handler code here
	//Add Filter for data
	LPCTSTR pszFilter =
		_T("Text (*.txt)|*.txt|");

	//Create file type variable for selected file 
	
	CFileDialog dlgFile(FALSE, _T("text"), (m_GraphTitle+_T(".txt")), OFN_OVERWRITEPROMPT, pszFilter, AfxGetMainWnd());

	//If file selected:
	if (IDOK == dlgFile.DoModal()) {
		//Try and read
		try {
			//Read as text
			CStdioFile file(dlgFile.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
			//Ensure data is read
			bool succesful{ false };
			//Read data line by line and assign to class variables
			if (dlgFile.GetFileExt() == _T("txt")) {
				UpdateData();
				CString coordinate;
				file.WriteString(m_GraphTitle + "\n");
				file.WriteString(m_GraphX + "\n");
				file.WriteString(m_GraphY + "\n");
				coordinate.Format(_T("%d\n"), n);
				file.WriteString(coordinate);

				for (int i = 0; i < n; i++) {
					coordinate.Format(_T("% f, % f\n"), X[i], Y[i]);
					file.WriteString(coordinate);					
				}
				file.WriteString(_T("\n"));
				file.WriteString(_T("Regression Data\n"));
				file.WriteString(_T("Line of best fit\n"));
				coordinate.Format(_T("%f * X + %f\n"), coeff, constantTerm);
				file.WriteString(coordinate);
				file.WriteString(_T("\n"));
				file.WriteString(_T("Error:\n"));
				coordinate.Format(_T("%f\n"), errorSq);
				file.WriteString(coordinate);
				succesful = true;
				
			}

			//Alert user read failed
			if (!succesful) {
				AfxMessageBox(_T("Error saving file"));
			}
			//Update
			if (succesful) {
				dataRead = false;
				
			}
		}
		catch (CFileException* pe)
		{
			CString Error;
			Error.Format(_T("File could not be saved, cause = %d\n"),
				pe->m_cause);
			AfxMessageBox(Error);
			pe->Delete();
		}
	}
	
	
}


void CRegressionDiaDlg::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	CClearDlg cleardlg;
	if (cleardlg.DoModal() == IDOK) {
		dataRead = false;
		regressed = false;
		m_documentType = DocumentType::None;
		delete[] X;
		delete[] Y;
		X = NULL;
		Y = NULL;
		m_GraphTitle = m_GraphX = m_GraphY = _T("");
		SetDlgItemText(IDC_EDIT1, m_GraphTitle);
		SetDlgItemText(IDC_EDIT2, m_GraphX);
		SetDlgItemText(IDC_EDIT3, m_GraphY);
		Invalidate();
		UpdateWindow();
	}
}
