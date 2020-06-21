
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
#include "afxdialogex.h"
#include <atlbase.h>
#include "CMySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SEND_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOUR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatClientDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)
	
	//ON_BN_CLICKED(IDC_AUTOSEND_RADIO1, &CMFCChatClientDlg::OnBnClickedAutosendRadio1)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatClientDlg::OnBnClickedClearBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFCChatClientDlg::OnBnClickedAutosendCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("6000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));
	//读取配置文件中的昵称。
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR wszPath[MAX_PATH] = { 0 };
	//1.获取当前路径
	GetCurrentDirectoryW(MAX_PATH, wszPath);
	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", wszPath);
	DWORD dwNum=GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL,
		wszName, MAX_PATH, strFilePath);
	if (dwNum > 0) {
		TRACE("#####wszName=%ls\n", wszName);
		//2.显示在控件中
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}
	else
	{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"),L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}
	
	//初始化控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);
	//初始化颜色选择变量的初始显示
	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));

	m_WordColorCombo.SetCurSel(0);//设置当前 选择
	SetDlgItemText(IDC_COLOUR_COMBO, _T("黑色"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		//定义设备上下文
		CPaintDC dc(this); // 用于绘制的设备上下文
		//确定区域
		CRect rect;
		GetClientRect(&rect);
		TRACE("width=%d,height=%d\n", rect.Width(), rect.Height());
		//定义并创建内存设备环境，创建兼容性设备DC

		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);
		//载入资源图片
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmap(IDB_WD_BITMAP);
		//将图片载入位图
		BITMAP bBitmap;
		bmpBackGround.GetBitmap(&bBitmap);
		//将位图选入临时的内存设备环境
		CBitmap* pbmpold = dcBmp.SelectObject(&bmpBackGround);
		//绘制,将原图像复制到目标矩形区域

		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0,
			          bBitmap.bmWidth, bBitmap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConnectBtn()
{
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);

	//取得IP跟端口
	TRACE("####OnBnClickedConnectBtn");
	CString strPort, strIP;
	//从控件中获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);
	//CString 转char *
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP =(LPCSTR)T2A(strIP);
	TRACE("szPort=%s,szIP=%s", szPort, szIP);


	int iPort = _ttoi(strPort);
	//创建对象
	m_client = new CMySocket;
	
	// 创建套接字
	if (!m_client->Create()) 
	{
		TRACE("m_client Create error %d",GetLastError());
		return;
	}
	else 
	{
		TRACE("m_client Create Success");
	}
	//连接
	if (m_client->Connect(strIP, iPort)!=SOCKET_ERROR)
	{
		TRACE("m_client->Connect error %d\n",GetLastError());
		return;
	}
	//ALT+G
	//alt+shift+F

}


void CMFCChatClientDlg::OnBnClickedDisconnectBtn()
{
	//控件恢复状态
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	//回收资源
	m_client->Close();
	if (m_client != NULL) {
		delete m_client;
		m_client = NULL;
	}

	//显示到列表框
	CString strShow = CatShowString(_T(""), _T("断开与服务器的连接！"));
	m_list.AddString(strShow);
	UpdateData(FALSE);

}

//消息的拼接
CString CMFCChatClientDlg::CatShowString(CString strInfo, CString strMsg)
{
	//时间+信息（昵称）+消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X ");
	CString strShow;
	strShow = strTime + strShow;
strShow += strInfo;
strShow += strMsg;
return strShow;
}

void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowTextW(strTmpMsg);
	CString strName;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);
	strTmpMsg = strName + _T(": ") + strTmpMsg;

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);
	//2.发送到服务端
	m_client->Send(szSendBuf, MAX_SEND_BUF, 0);

	//3.显示到列表框
	CString strShow;
	// 	CString strName;
	// 	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);
	// 	strName += _T(": ");
	CString strInfo = _T("");
	strShow = CatShowString(strInfo, strTmpMsg);

	// 	CString strTime;
	// 	m_tm = CTime::GetCurrentTime();
	// 	strTime = m_tm.Format("%X ");
	// 	strShow = strTime + strShow;
	// 	strShow += strTmpMsg;
	m_list.AddString(strShow);
	UpdateData(FALSE);
	//清空编辑框
	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}


void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0)
	{
		MessageBox(_T("昵称不能为空！"));
		return;
	}

	if (IDOK == AfxMessageBox(_T("确定修改昵称吗？"), MB_OKCANCEL))
	{
		TRACE("####:OnBnClickedSavenameBtn()");
		//保存昵称

		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);
		//两种方式获取编辑框内容
		//GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);
		GetDlgItemText(IDC_NAME_EDIT, strName);
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}

}




void CMFCChatClientDlg::OnBnClickedClearBtn()
{
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnBnClickedAutosendCheck()
{
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))
		->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))
			->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))
			->SetCheck(TRUE);
	}
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);

	if ((IDC_LIST1) == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 255));
		}
	}

	/*
	if (strColor == L"黑色")
	{
		if ((IDC_LIST1) == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
		 {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
	 }
	if (strColor == L"红色")
	{
		if ((IDC_LIST1) == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	if (strColor == L"蓝色")
	{
		if ((IDC_LIST1) == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
	}
	if (strColor == L"绿色")
	{
		if ((IDC_LIST1) == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(0, 255, 255));
		}
	}
	*/

	

	 return hbr;
 }


BOOL CMFCChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	//规避回车键
	//按下键盘，并且是某键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		TRACE("回车");
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		TRACE("空格键");
		return TRUE;
	}
	if ((pMsg->message) == WM_KEYDOWN)
	{
		TRACE("######Ctrl 是否按下");
		if (GetKeyState(VK_CONTROL) < 0)// Ctrl 是否按下
		{
			TRACE("######Ctrl +X 是否按下");
			if (pMsg->wParam == 'X')    //Ctrl +X   是否按下
			{
				CDialogEx::OnOK();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
