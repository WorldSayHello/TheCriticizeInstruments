// MyPic.cpp : 实现文件
//

#include "stdafx.h"
#include "TheCriticizeInstruments.h"
#include "MyPic.h"
#include "TheCriticizeInstrumentsDlg.h"

extern HWND g_hWnd;
extern HWND g_hMe;
// CMyPic

IMPLEMENT_DYNAMIC(CMyPic, CStatic)

CMyPic::CMyPic()
{

}

CMyPic::~CMyPic()
{
}


BEGIN_MESSAGE_MAP(CMyPic, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyPic 消息处理程序




void CMyPic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//不管光标的位置，使所有后续鼠标输入发送到当前 CWnd 对象。
	//一般来说，鼠标只能在当前窗口相应，使用此函数后，鼠标在所有窗口都可以相应
	SetCapture();
	//设置鼠标样式
	HCURSOR hCursor = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR_SELECT));
	::SetCursor(hCursor);
	//设置图标
	HICON hIconAfter = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_AFTER));
	this->SetIcon(hIconAfter);
	FromHandle(g_hMe)->SetTimer(1, 600, NULL);

	CStatic::OnLButtonDown(nFlags, point);
}


void CMyPic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	ReleaseCapture();
	HICON hIconBefor = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_BEFOR));
	this->SetIcon(hIconBefor);

	POINT Point;
	::GetCursorPos(&Point);
	g_hWnd = ::WindowFromPoint(Point);

	//因为::WindowFromPoint(Point)对不可用的窗口无效，所以，为了能选中
	//灰色按钮等不可用的窗口(以进行激活等操作)，添加下面这段代码
	//读者也可以做一下试验，将下面*******间的代码注释掉，将不能选中不可用窗口

	//*******************

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

	//**********************//
	FromHandle(g_hMe)->KillTimer(1);

	//LONG  Style   = GetWindowLongPtr(g_hWnd, GWL_STYLE);
	//LONG  StyleEx = GetWindowLongPtr(g_hWnd, GWL_EXSTYLE);

	CStatic::OnLButtonUp(nFlags, point);
}
