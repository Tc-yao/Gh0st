#pragma once



// SetingView ������ͼ

class SetingView : public CFormView
{
	DECLARE_DYNCREATE(SetingView)

public:
	SetingView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~SetingView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


