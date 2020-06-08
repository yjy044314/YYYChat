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

	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str=dlg->m_tm.Format("%X ");
	str += _T("�ͻ������ӳɹ�");
	dlg->m_list.AddString(str);
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);
}