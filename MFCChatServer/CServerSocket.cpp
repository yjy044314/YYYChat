#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"


CServerSocket::CServerSocket() 
{

}
CServerSocket:: ~CServerSocket() 
{

}
void CServerSocket::OnConnect(int nErrorCode)
{
	CMFCChatServerDlg* dlg =(CMFCChatServerDlg*) AfxGetApp()->GetMainWnd();

	TRACE("#### OnConnect(int nErrorCode)");
}