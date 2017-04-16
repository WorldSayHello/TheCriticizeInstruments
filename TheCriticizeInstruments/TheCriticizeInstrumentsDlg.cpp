
// TheCriticizeInstrumentsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TheCriticizeInstruments.h"
#include "TheCriticizeInstrumentsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
HWND g_hMe;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTheCriticizeInstrumentsDlg 对话框



CTheCriticizeInstrumentsDlg::CTheCriticizeInstrumentsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THECRITICIZEINSTRUMENTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTheCriticizeInstrumentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_eInput);
}

BEGIN_MESSAGE_MAP(CTheCriticizeInstrumentsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_ALWAYS_TOP, &CTheCriticizeInstrumentsDlg::OnBnClickedCheckAlwaysTop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_BEGIN, &CTheCriticizeInstrumentsDlg::OnBnClickedButtonBegin)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CTheCriticizeInstrumentsDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CTheCriticizeInstrumentsDlg 消息处理程序

BOOL CTheCriticizeInstrumentsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//默认将窗口置于最上方 不知道为什么需要调用两次SetWindowsPos
	((CButton*)GetDlgItem(IDC_CHECK_ALWAYS_TOP))->SetCheck(1);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	if (!::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE))
		OutputDebugString(L"窗口置于最上方失败");

	m_pic.SubclassDlgItem(IDC_PIC, this);

	g_hMe = m_hWnd;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTheCriticizeInstrumentsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTheCriticizeInstrumentsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTheCriticizeInstrumentsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTheCriticizeInstrumentsDlg::OnBnClickedCheckAlwaysTop()
{
	// TODO: 在此添加控件通知处理程序代码

	int nTop = ((CButton*)GetDlgItem(IDC_CHECK_ALWAYS_TOP))->GetCheck();
	if (nTop == 1)
		//设置窗口处于最上方
		::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

}


void CTheCriticizeInstrumentsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
	{
		POINT Point;

		RECT Rect;
		HWND DeskHwnd = ::GetDesktopWindow();        //取得桌面句柄
		HDC  DeskDC = ::GetWindowDC(DeskHwnd);     //取得桌面设备场景

		int OldRop2 = SetROP2(DeskDC, R2_NOTXORPEN);
		::GetCursorPos(&Point);                    //取得鼠标坐标
		HWND UnHwnd = ::WindowFromPoint(Point);    //取得鼠标指针处窗口句柄

												   //这里层层得到子窗口
		g_hWnd = UnHwnd;
		HWND GrayHwnd = ::GetWindow(g_hWnd, GW_CHILD);
		RECT TempRect;
		BOOL bFind = FALSE;
		while (GrayHwnd)
		{
			::GetWindowRect(GrayHwnd, &TempRect);
			if (::PtInRect(&TempRect, Point))
			{
				bFind = TRUE;
				break;
			}
			else
				GrayHwnd = ::GetWindow(GrayHwnd, GW_HWNDNEXT);

		}//while
		if (bFind == TRUE)
		{
			bFind = FALSE;
			g_hWnd = GrayHwnd;
		}
		CString HwndText;
		HwndText.Format(L"%X", g_hWnd);
		SetDlgItemText(IDC_EDIT_HWND, HwndText);
		::GetWindowRect(g_hWnd, &Rect);      //获得窗口矩形

		if (Rect.left < 0) Rect.left = 0;
		if (Rect.top < 0) Rect.top = 0;

		HPEN NewPen = ::CreatePen(0, 3, RGB(125, 0, 125));    //建立新画笔,载入DeskDC
		::SelectObject(DeskDC, NewPen);
		//HGDIOBJ OldPen = ::SelectObject(DeskDC, NewPen);
		::Rectangle(DeskDC, Rect.left, Rect.top, Rect.right, Rect.bottom);  //在指示窗口周围显示矩形

		::SetROP2(DeskDC, OldRop2);
		//::SelectObject(DeskDC, OldPen);
		::DeleteObject(NewPen);
		::ReleaseDC(DeskHwnd, DeskDC);
		DeskDC = NULL;
		break;
	}
	case 2:
	{
		MyPostMessage();
		break;
	}
	default:
		break;
	}
	

	CDialogEx::OnTimer(nIDEvent);
}

void CTheCriticizeInstrumentsDlg::MyPostMessage()
{
	CString Word;
	GetDlgItem(IDC_EDIT_INPUT)->GetWindowText(Word);

	WCHAR szWord[0x100] = { 0 };
	wcscpy_s(szWord, CT2CW(Word));

	for (int i = 0; i < lstrlen(szWord); i++)
	{

		//WM_CHAR 不打开输入法
		::PostMessage(g_hWnd, WM_CHAR, szWord[i], 0);
	}

	::PostMessage(g_hWnd, WM_KEYDOWN, VK_RETURN, 0);
	::PostMessage(g_hWnd, WM_KEYUP, VK_RETURN, 0);
}

void CTheCriticizeInstrumentsDlg::OnBnClickedButtonBegin()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(2);
	int v5 = ((CButton*)GetDlgItem(IDC_RADIO_5))->GetCheck();
    int v10 = ((CButton*)GetDlgItem(IDC_RADIO_10))->GetCheck();
	if (v5)
	{
		SetTimer(2, 200, NULL);
	}
	if (v10)
	{
		SetTimer(2, 100, NULL);
	}
	CString Word;
	GetDlgItem(IDC_EDIT_INPUT)->GetWindowText(Word);

	WCHAR szWord[0x100] = {0};
	wcscpy_s(szWord, CT2CW(Word));

	for (int i = 0; i < lstrlen(szWord); i++)
	{

		//WM_CHAR 不打开输入法
		::PostMessage(g_hWnd, WM_CHAR, szWord[i], 0);
	}

	::PostMessage(g_hWnd, WM_KEYDOWN, VK_RETURN, 0);
	//::PostMessage(g_hWnd, WM_KEYUP, VK_RETURN, 0);
}

//防止按回车自动退出
void CTheCriticizeInstrumentsDlg::OnOK()
{

}

void CTheCriticizeInstrumentsDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(2);
}
