
// TheCriticizeInstrumentsDlg.h : ͷ�ļ�
//

#pragma once
#include "MyPic.h"
#include "afxwin.h"

// CTheCriticizeInstrumentsDlg �Ի���
class CTheCriticizeInstrumentsDlg : public CDialogEx
{
// ����
public:
	CTheCriticizeInstrumentsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THECRITICIZEINSTRUMENTS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CMyPic m_pic;
	afx_msg void OnBnClickedCheckAlwaysTop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void MyPostMessage();
	afx_msg void OnBnClickedButtonBegin();
	void OnOK();
	CEdit m_eInput;
	afx_msg void OnBnClickedButtonStop();
};
