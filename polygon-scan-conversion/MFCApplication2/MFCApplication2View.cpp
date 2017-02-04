
// MFCApplication2View.cpp : implementation of the CMFCApplication2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_FUNCTION_FILL, &CMFCApplication2View::OnFunctionFill)
END_MESSAGE_MAP()

// CMFCApplication2View construction/destruction

CMFCApplication2View::CMFCApplication2View()
{
	// TODO: add construction code here
	m_EdgeTable = NULL;
	LenOfEdge = 0;
	m_min = -1;
	num = 0;
}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View drawing

void CMFCApplication2View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCApplication2View printing

BOOL CMFCApplication2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCApplication2View diagnostics

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View message handlers


void CMFCApplication2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	RedrawWindow();

	CDC* pDC = GetDC();
	CPen newpen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *old = pDC->SelectObject(&newpen);
	spt[num] = point;
	num++;
	pDC->Polyline(spt, num);
	pDC->SelectObject(old);
	ReleaseDC(pDC);

	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDown(nFlags, point);
}

void CMFCApplication2View::InitET()
{
	int i, max;
	// 求出最大的y值和最小的y值，即占用的最大扫描线数
	for (max = spt[0].y, m_min = spt[0].y, i = 1; i< 8; i++)
	{
		if (spt[i].y > max) max = spt[i].y;
		else if (spt[i].y < m_min) m_min = spt[i].y;
	}
	LenOfEdge = max - m_min + 1;			// 最大扫描线数
	m_EdgeTable = new ET[LenOfEdge];	//长度为LenOfEdge的创建边表

										// 初始化边表数组为空
	for (i = 0; i<LenOfEdge; i++)
	{
		m_EdgeTable[i].next = NULL;
	}

	// 根据所给边求出边表
	for (i = 0; i<7; i++)
	{
		int m = i + 1;
		if (spt[i].y < spt[m].y)	//第i个点的y坐标小于下一个点的y坐标
		{
			ET *q = new ET();
			q->xymin = spt[i].x;
			q->ymax = spt[m].y;
			q->k = (double)(spt[m].x - spt[i].x) / (double)(spt[m].y - spt[i].y);	// 1/k的值
			q->next = NULL;
			ET* p = &m_EdgeTable[spt[i].y - m_min];
			while (p->next != NULL) p = p->next;
			p->next = q;
		}
		else if (spt[i].y > spt[m].y)	//第i个点的坐标大于下一个点的坐标
		{
			ET *q = new ET();
			q->xymin = spt[m].x;
			q->ymax = spt[i].y;
			q->k = (double)(spt[i].x - spt[m].x) / (double)(spt[i].y - spt[m].y);	// 1/k的值
			q->next = NULL;
			ET* p = &m_EdgeTable[spt[m].y - m_min];
			while (p->next != NULL) p = p->next;
			p->next = q;
		}
	}
	for (i = 0; i<LenOfEdge; i++)
	{
		if (m_EdgeTable[i].next != NULL)
		{
			ET *p = m_EdgeTable[i].next;
			while (p != NULL)
			{
				TRACE("%d,%f, %d, %f\n", i, p->xymin, p->ymax, p->k);
				p = p->next;
			}
			TRACE("\n\n");
		}
	}
	CDC *dc = GetDC();
	ET *p = nullptr;
	BOOL Draw = TRUE;

	// 将第一个不为空的边表中的边与AET表合并
	for (i = 0; i< LenOfEdge; i++)
	{
		if (m_EdgeTable[i].next != NULL)
		{
			p = m_EdgeTable[i].next;
			m_EdgeTable[i].next = NULL;
			break;
		}
	}
	int y = m_min;			//扫描线
	double x = p->xymin;	//横向扫描一行的下标
	while (p != NULL)
	{
		ET* q = p;
		double x_max = q->xymin;	// 一行中最右边的x值
		x = q->xymin;				// 起始值，一行中最左边的x值
		while (q != NULL)				// 求一行中的最后一个边界点的x坐标,和起始点的x坐标
		{
			if (q->xymin > x_max) x_max = q->xymin;
			if (q->xymin < x) x = q->xymin;
			q = q->next;
		}

		Draw = TRUE;
		while (x < x_max) //扫描一行
		{
			q = p;
			while (q != NULL)	// 扫描整行，判断当前点是不是节点
			{
				if (int(q->xymin) == int(x))	//访问到一个节点，取反
				{
					Draw = !Draw;
					break;
				}
				q = q->next;
			}
			if (!Draw) dc->SetPixel(int(x + 0.5), y, 0);
			x++;
		}

		for (q = p; q != NULL; q = q->next)	// 填充后删除 ymax = y的边
		{
			if (q->ymax == y)
			{
				if (q == p)
				{
					p = p->next;
				}
				else
				{
					ET* temp = p;
					while (temp != NULL && temp->next != NULL)	//删除 q
					{
						if (temp->next == q) { temp->next = q->next; break; }
						temp = temp->next;
					}
				}

			}
		}
		y += 1;	//向下移动一行
		for (q = p; q != NULL; q = q->next)
		{
			q->xymin = q->xymin + q->k;
		}
		if (m_EdgeTable[y - m_min].next != NULL)
		{
			for (q = p; q != NULL && q->next != NULL; q = q->next)
				;
			if (q != NULL)
			{
				q->next = m_EdgeTable[y - m_min].next;
				m_EdgeTable[y - m_min].next = NULL;
			}
		}
	}
	ReleaseDC(dc);
}


void CMFCApplication2View::OnFunctionFill()
{
	// TODO: Add your command handler code here
	InitET();
}
