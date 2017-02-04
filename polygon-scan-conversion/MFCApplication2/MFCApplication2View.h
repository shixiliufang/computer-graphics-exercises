
// MFCApplication2View.h : interface of the CMFCApplication2View class
//

#pragma once
typedef struct tagET
{
	double xymin;
	long ymax;
	double k;
	struct tagET *next;
}ET;


class CMFCApplication2View : public CView
{
protected: // create from serialization only
	CMFCApplication2View();
	DECLARE_DYNCREATE(CMFCApplication2View)

// Attributes
public:
	CMFCApplication2Doc* GetDocument() const;

// Operations
public:
	CPoint seed_point, spt[100];
	ET *m_EdgeTable;
	int LenOfEdge;
	long m_min;
	int num = 0;

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
	virtual ~CMFCApplication2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void InitET();
	afx_msg void OnFunctionFill();
};

#ifndef _DEBUG  // debug version in MFCApplication2View.cpp
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

