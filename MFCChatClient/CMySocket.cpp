#include "pch.h"
#include "CMySocket.h"

CMySocket::CMySocket()
{

}
CMySocket::~CMySocket()
{

}

//ALT+G
//alt+shift+F
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg *)AfxGetApp()->GetMainWnd();
	CString strShow;
	
// 	dlg->m_tm = CTime::GetCurrentTime();
// 	strShow = dlg->m_tm.Format("%X ");
	strShow += _T("与服务器连接成功");
	strShow = dlg->CatShowString(_T(""), strShow);
	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);

}
void CMySocket::OnReceive(int nErrorCode) 
{
	
	TRACE("####CMySocket::OnReceive(int nErrorCode) ");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//1.接收数据
	char szRecvBuf[MAX_SEND_BUF] = { 0 };
	Receive(szRecvBuf, MAX_SEND_BUF, 0);
	TRACE("#####client Receive szRecvBuf %s", szRecvBuf);
	//2.显示 到列表框
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow;
	CString strInfo = _T("服务端: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
// 	CString strTime;
// 	dlg->m_tm = CTime::GetCurrentTime();
// 	strTime = dlg->m_tm.Format("%X ");
// 	strShow = strTime + strShow;
// 	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))
		->GetCheck())
	{
		//自动回复,读取编辑框内容
		CString strAutoSendMsg;
		dlg->GetDlgItem(IDC_AUTOSENDMSG_EDIT)->GetWindowTextW(strAutoSendMsg);
		//封包，组格式，发送给服务端：时间+昵称+消息
		CString strName;
		dlg->GetDlgItemTextW(IDC_NAME_EDIT, strName);
		CString  strMsg = _T("[自动回复]") + strAutoSendMsg;
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, MAX_SEND_BUF, 0);

		//时间+昵称+消息
		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->UpdateData(FALSE);
	}
	//alt+shift +F
	//选中单选按钮
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}