
// Gh0stView.h : CGh0stView ��Ľӿ�
//

#pragma once
#include "Gh0stDoc.h"
#define CListView CCJListView

class CGh0stView : public CListView
{
protected: // �������л�����
	CGh0stView();
	DECLARE_DYNCREATE(CGh0stView)

// ����
public:
	CGh0stDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CGh0stView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CListCtrl* m_pListCtrl;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMyInitialUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddToList(WPARAM wParam, LPARAM lParam);
	int m_nCount=0;
};

#ifndef _DEBUG  // Gh0stView.cpp �еĵ��԰汾
inline CGh0stDoc* CGh0stView::GetDocument() const
   { return reinterpret_cast<CGh0stDoc*>(m_pDocument); }
#endif

