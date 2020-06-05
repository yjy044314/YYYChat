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
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += _T("与服务器连接成功");
	dlg->m_list.AddString(str);

	CAsyncSocket::OnConnect(nErrorCode);

}
void CMySocket::OnReceive(int nErrorCode) 
{
	TRACE("####OnReceive");
}