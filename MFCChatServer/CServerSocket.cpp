#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "CChatSocket.h"


CServerSocket::CServerSocket() 
{

}
CServerSocket:: ~CServerSocket() 
{

}
void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("####OnAccept(int nErrorCode)");
	CMFCChatServerDlg* dlg =(CMFCChatServerDlg*) AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	//��ʼ��������
	Accept(*(dlg->m_chat));

	CString strShow;
// 	dlg->m_tm = CTime::GetCurrentTime();
// 	strShow =dlg->m_tm.Format("%X ");
	strShow += _T("�ͻ������ӳɹ�");
	strShow = dlg->CatShowString(_T("") , strShow);
	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);
}