
// TheCriticizeInstrumentsDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTheCriticizeInstrumentsDlg �Ի���



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


// CTheCriticizeInstrumentsDlg ��Ϣ�������

BOOL CTheCriticizeInstrumentsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//Ĭ�Ͻ������������Ϸ� ��֪��Ϊʲô��Ҫ��������SetWindowsPos
	((CButton*)GetDlgItem(IDC_CHECK_ALWAYS_TOP))->SetCheck(1);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	if (!::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE))
		OutputDebugString(L"�����������Ϸ�ʧ��");

	m_pic.SubclassDlgItem(IDC_PIC, this);

	g_hMe = m_hWnd;


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTheCriticizeInstrumentsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTheCriticizeInstrumentsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTheCriticizeInstrumentsDlg::OnBnClickedCheckAlwaysTop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nTop = ((CButton*)GetDlgItem(IDC_CHECK_ALWAYS_TOP))->GetCheck();
	if (nTop == 1)
		//���ô��ڴ������Ϸ�
		::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

}


void CTheCriticizeInstrumentsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
	{
		POINT Point;

		RECT Rect;
		HWND DeskHwnd = ::GetDesktopWindow();        //ȡ��������
		HDC  DeskDC = ::GetWindowDC(DeskHwnd);     //ȡ�������豸����

		int OldRop2 = SetROP2(DeskDC, R2_NOTXORPEN);
		::GetCursorPos(&Point);                    //ȡ���������
		HWND UnHwnd = ::WindowFromPoint(Point);    //ȡ�����ָ�봦���ھ��

												   //������õ��Ӵ���
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
		::GetWindowRect(g_hWnd, &Rect);      //��ô��ھ���

		if (Rect.left < 0) Rect.left = 0;
		if (Rect.top < 0) Rect.top = 0;

		HPEN NewPen = ::CreatePen(0, 3, RGB(125, 0, 125));    //�����»���,����DeskDC
		::SelectObject(DeskDC, NewPen);
		//HGDIOBJ OldPen = ::SelectObject(DeskDC, NewPen);
		::Rectangle(DeskDC, Rect.left, Rect.top, Rect.right, Rect.bottom);  //��ָʾ������Χ��ʾ����

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

		//WM_CHAR �������뷨
		::PostMessage(g_hWnd, WM_CHAR, szWord[i], 0);
	}

	::PostMessage(g_hWnd, WM_KEYDOWN, VK_RETURN, 0);
	::PostMessage(g_hWnd, WM_KEYUP, VK_RETURN, 0);
}

void CTheCriticizeInstrumentsDlg::OnBnClickedButtonBegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		//WM_CHAR �������뷨
		::PostMessage(g_hWnd, WM_CHAR, szWord[i], 0);
	}

	::PostMessage(g_hWnd, WM_KEYDOWN, VK_RETURN, 0);
	//::PostMessage(g_hWnd, WM_KEYUP, VK_RETURN, 0);
}

//��ֹ���س��Զ��˳�
void CTheCriticizeInstrumentsDlg::OnOK()
{

}

void CTheCriticizeInstrumentsDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(2);
}
