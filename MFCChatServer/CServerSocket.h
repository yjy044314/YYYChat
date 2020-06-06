#pragma once
#include <afxsock.h>
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"

class CServerSocket :
	public CAsyncSocket
{
public:

	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnConnect(int nErrorCode);
};

