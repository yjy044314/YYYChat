﻿
// MFCChatServerDlg.h: 头文件
//

#pragma once
class CServerSocket;
class CChatSocket;


// CMFCChatServerDlg 对话框
class CMFCChatServerDlg : public CDialogEx
{
// 构造
public:
	CMFCChatServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnEnChangeSendEdit();
	afx_msg void OnBnClickedStartBtn();
	CListBox m_list;
	CChatSocket* m_chat;
	CServerSocket* m_server;
	CTime m_tm;

	afx_msg void OnBnClickedSendBtn();
};
