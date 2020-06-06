#pragma once
#include <afxsock.h>
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();

	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

