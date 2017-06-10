// BuildView.cpp : 实现文件
//

#include "stdafx.h"
#include "Gh0st.h"
#include "BuildView.h"


// BuildView

IMPLEMENT_DYNCREATE(BuildView, CFormView)

BuildView::BuildView()
	: CFormView(IDD_BUILD)
{

}

BuildView::~BuildView()
{
}

void BuildView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(BuildView, CFormView)
END_MESSAGE_MAP()


// BuildView 诊断

#ifdef _DEBUG
void BuildView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void BuildView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// BuildView 消息处理程序
