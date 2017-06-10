
// Gh0stView.h : CGh0stView 类的接口
//

#pragma once
#include "Gh0stDoc.h"
#define CListView CCJListView

class CGh0stView : public CListView
{
protected: // 仅从序列化创建
	CGh0stView();
	DECLARE_DYNCREATE(CGh0stView)

// 特性
public:
	CGh0stDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CGh0stView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CListCtrl* m_pListCtrl;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMyInitialUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddToList(WPARAM wParam, LPARAM lParam);
	int m_nCount=0;
};

#ifndef _DEBUG  // Gh0stView.cpp 中的调试版本
inline CGh0stDoc* CGh0stView::GetDocument() const
   { return reinterpret_cast<CGh0stDoc*>(m_pDocument); }
#endif

