#pragma once



// BuildView ������ͼ

class BuildView : public CFormView
{
	DECLARE_DYNCREATE(BuildView)

public:
	BuildView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~BuildView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUILD };
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


