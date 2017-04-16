// MyPic.cpp : ʵ���ļ�
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



// CMyPic ��Ϣ�������




void CMyPic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//���ܹ���λ�ã�ʹ���к���������뷢�͵���ǰ CWnd ����
	//һ����˵�����ֻ���ڵ�ǰ������Ӧ��ʹ�ô˺�������������д��ڶ�������Ӧ
	SetCapture();
	//���������ʽ
	HCURSOR hCursor = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR_SELECT));
	::SetCursor(hCursor);
	//����ͼ��
	HICON hIconAfter = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_AFTER));
	this->SetIcon(hIconAfter);
	FromHandle(g_hMe)->SetTimer(1, 600, NULL);

	CStatic::OnLButtonDown(nFlags, point);
}


void CMyPic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	ReleaseCapture();
	HICON hIconBefor = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_BEFOR));
	this->SetIcon(hIconBefor);

	POINT Point;
	::GetCursorPos(&Point);
	g_hWnd = ::WindowFromPoint(Point);

	//��Ϊ::WindowFromPoint(Point)�Բ����õĴ�����Ч�����ԣ�Ϊ����ѡ��
	//��ɫ��ť�Ȳ����õĴ���(�Խ��м���Ȳ���)�����������δ���
	//����Ҳ������һ�����飬������*******��Ĵ���ע�͵���������ѡ�в����ô���

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
