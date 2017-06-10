// SetingView.cpp : 实现文件
//

#include "stdafx.h"
#include "Gh0st.h"
#include "SetingView.h"


// SetingView

IMPLEMENT_DYNCREATE(SetingView, CFormView)

SetingView::SetingView()
	: CFormView(IDD_SETTING)
{

}

SetingView::~SetingView()
{
}

void SetingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(SetingView, CFormView)
END_MESSAGE_MAP()


// SetingView 诊断

#ifdef _DEBUG
void SetingView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SetingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SetingView 消息处理程序
