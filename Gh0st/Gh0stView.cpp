
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

	return CListView::PreCreateWindow(cs);
}

void CGh0stView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
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
