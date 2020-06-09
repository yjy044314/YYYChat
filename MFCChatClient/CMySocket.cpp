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
	strShow += _T("����������ӳɹ�");
	strShow = dlg->CatShowString(_T(""), strShow);
	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);

}
void CMySocket::OnReceive(int nErrorCode) 
{
	
	TRACE("####CMySocket::OnReceive(int nErrorCode) ");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//1.��������
	char szRecvBuf[MAX_SEND_BUF] = { 0 };
	Receive(szRecvBuf, MAX_SEND_BUF, 0);
	TRACE("#####client Receive szRecvBuf %s", szRecvBuf);
	//2.��ʾ ���б��
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow;
	CString strInfo = _T("�����: ");
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
		//�Զ��ظ�,��ȡ�༭������
		CString strAutoSendMsg;
		dlg->GetDlgItem(IDC_AUTOSENDMSG_EDIT)->GetWindowTextW(strAutoSendMsg);
		//��������ʽ�����͸�����ˣ�ʱ��+�ǳ�+��Ϣ
		CString strName;
		dlg->GetDlgItemTextW(IDC_NAME_EDIT, strName);
		CString  strMsg = _T("[�Զ��ظ�]") + strAutoSendMsg;
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, MAX_SEND_BUF, 0);

		//ʱ��+�ǳ�+��Ϣ
		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->UpdateData(FALSE);
	}
	//alt+shift +F
	//ѡ�е�ѡ��ť
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}