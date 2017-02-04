
// MFCApplication3View.h : interface of the CMFCApplication3View class
//

#pragma once


class CMFCApplication3View : public CView
{
protected: // create from serialization only
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

// Attributes
public:
	CMFCApplication3Doc* GetDocument() const;

// Operations
public:
	void arymul(int a[2][3], int b[3][3]);
	int x1 = 50, y1 = 50, x2 = 200, y2 = 200;
	int c[2][3];
	void dda_line(int xa, int ya, int xb, int yb);
	double round(double x);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFunctionDda();
	afx_msg void OnFunctionConversion();
};

#ifndef _DEBUG  // debug version in MFCApplication3View.cpp
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

