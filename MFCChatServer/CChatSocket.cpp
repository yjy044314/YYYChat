#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
//#include <atlbase.h>


CChatSocket::CChatSocket() 
{

}
CChatSocket::~CChatSocket() 
{

}
void CChatSocket::OnReceive(int nErrorCode) 
{
	TRACE("####CChatSocket::OnReceive(int nErrorCode) ");
	CMFCChatServerDlg* dlg =(CMFCChatServerDlg *) AfxGetApp()->GetMainWnd();
	//1.��������
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);
	TRACE("#####server Receive szRecvBuf %s", szRecvBuf);
	//2.��ʾ ���б��
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow = _T("�ͻ���: ");
	strShow = dlg->CatShowString(strShow, strRecvMsg);
// 	CString strTime;
// 	dlg->m_tm = CTime::GetCurrentTime();
// 	strTime = dlg->m_tm.Format("%X ");
// 	strShow = strTime + strShow;
// 	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}
