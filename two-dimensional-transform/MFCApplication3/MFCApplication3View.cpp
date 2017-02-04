
// MFCApplication3View.cpp : implementation of the CMFCApplication3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FUNCTION_DDA, &CMFCApplication3View::OnFunctionDda)
	ON_COMMAND(ID_FUNCTION_CONVERSION, &CMFCApplication3View::OnFunctionConversion)
END_MESSAGE_MAP()

// CMFCApplication3View construction/destruction

CMFCApplication3View::CMFCApplication3View()
{
	// TODO: add construction code here

}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View drawing

void CMFCApplication3View::arymul(int a[2][3], int b[3][3])
{
	memset(c, 0, sizeof(c));
	int k = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void CMFCApplication3View::dda_line(int xa, int ya, int xb, int yb)
{
	int dx = xb - xa, dy = yb - ya, step;
	double xincrement, yincrement, x = xa, y = ya;
	if (abs(dx) > abs(dy))
	{
		step = abs(dx);
	}
	else
	{
		step = abs(dy);
	}
	xincrement = dx / (double)step;
	yincrement = dy / (double)step;

	CDC *pDC = GetDC();
	pDC->SetPixel(round(x), round(y), RGB(255, 0, 0));

	for (int i = 0; i < step; i++)
	{
		x += xincrement;
		y += yincrement;
		pDC->SetPixel(round(x), round(y), RGB(255, 0, 0));
	}
}

double CMFCApplication3View::round(double x)
{
	double y = x - floor(x);
	if (y >= 0.5)
		return ceill(x);
	else
		return floor(x);
}

void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCApplication3View printing

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCApplication3View diagnostics

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG

// CMFCApplication3View message handlers


void CMFCApplication3View::OnFunctionDda()
{
	// TODO: Add your command handler code here
	dda_line(x1, y1, x2, y2);
}


void CMFCApplication3View::OnFunctionConversion()
{
	// TODO: Add your command handler code here
	int a[2][3] = { { x1, y1, 1 },{ x2, y2, 1 } };
	int b[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 300, 100, 1 } };
	arymul(a, b);
	x1 = c[0][0];
	y1 = c[0][1];
	x2 = c[1][0];
	y2 = c[1][1];
	dda_line(x1, y1, x2, y2);
}
