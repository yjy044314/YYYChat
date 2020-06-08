#include "pch.h"
#include "CMySocket.h"

CMySocket::CMySocket()
{

}
CMySocket::~CMySocket()
{

}

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
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);
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
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}