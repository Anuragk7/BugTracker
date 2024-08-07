
// BugTracksView.cpp : implementation of the CBugTracksView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BugTracks.h"
#endif

#include "BugTracksDoc.h"
#include "BugTracksView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBugTracksView

IMPLEMENT_DYNCREATE(CBugTracksView, CView)

BEGIN_MESSAGE_MAP(CBugTracksView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_VIEW_APPLOOK_OFF_2003, &CBugTracksView::OnTrackAnimate)
	ON_WM_TIMER()
	ON_COMMAND(ID_TRACK_ANIMATE, &CBugTracksView::OnTrackAnimate)
	ON_COMMAND(ID_TRACK2_ANIMATE2, &CBugTracksView::OnTrack2Animate2)
END_MESSAGE_MAP()

// CBugTracksView construction/destruction

CBugTracksView::CBugTracksView() noexcept
{
	// TODO: add construction code here

}

CBugTracksView::~CBugTracksView()
{
}

BOOL CBugTracksView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBugTracksView drawing

void CBugTracksView::OnDraw(CDC* pDC)
{
	CBugTracksDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	// make pens for solid lines of thickness 2 

	CPen RedPen(PS_SOLID, 2, RGB(255, 0, 0));

	CPen BluePen(PS_SOLID, 2, RGB(0, 0, 255));


	CPen* pOldPen = pDC->SelectObject(&RedPen);


	int i, N = pDoc->m_BugDataArray.GetSize();


	// draw any tracks which need animated 

	for (i = 0; i < pDoc->m_nBugPosition - 1; i++)

	{

		pDC->MoveTo(pDoc->m_BugDataArray[i].x, pDoc->m_BugDataArray[i].y);

		pDC->LineTo(pDoc->m_BugDataArray[i + 1].x, pDoc->m_BugDataArray[i + 1].y);

	}


	// change pens 

	pDC->SelectObject(&BluePen);


	// start drawing non animated tracks, but need to check for a 

	// valid starting postion 

	int start = pDoc->m_nBugPosition;

	if (start < 0) start = 0;
	for (i = start; i < N - 2; i++)
	{
		pDC->MoveTo(pDoc->m_BugDataArray[i].x,  pDoc->m_BugDataArray[i].y);

		pDC->LineTo(pDoc->m_BugDataArray[i + 1].x, pDoc->m_BugDataArray[i + 1].y);

	}


	// deselect pens and delete them 

	pDC->SelectObject(pOldPen);

	RedPen.DeleteObject();

	BluePen.DeleteObject();


	// move to next position or quit animating 

	if (pDoc->m_nBugPosition != -1) pDoc->m_nBugPosition++;

	if (pDoc->m_nBugPosition >= N)

	{

		pDoc->m_nBugPosition = -1;


		// stop timer 1 

		KillTimer(1);


		// redraw and erase so all lines are in initial state (blue) 

		InvalidateRect(NULL);

	}
	//raw code for native data here
}

void CBugTracksView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBugTracksView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBugTracksView diagnostics

#ifdef _DEBUG
void CBugTracksView::AssertValid() const
{
	CView::AssertValid();
}

void CBugTracksView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBugTracksDoc* CBugTracksView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBugTracksDoc)));
	return (CBugTracksDoc*)m_pDocument;
}
#endif //_DEBUG


// CBugTracksView message handlers





void CBugTracksView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)

	{

		// tell windows the view needs redrawn 

		// note: the last parameter is the erase flag. 

		// if it is TRUE, things will flicker like crazy. 

		InvalidateRect(NULL, FALSE);

	}
	
	CView::OnTimer(nIDEvent);
}


void CBugTracksView::OnTrackAnimate()
{
	// TODO: Add your command handler code here
	CBugTracksDoc* pDoc = GetDocument();
	// set the position to the first data point 

	pDoc->m_nBugPosition = 0;


	// create a timer with id=1 and delay of 200 milliseconds 

	SetTimer(1, 200, NULL);
}


void CBugTracksView::OnTrack2Animate2()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CBugTracksDoc* pDoc = GetDocument();
	// set the position to the first data point 

	pDoc->m_nBugPosition = 0;


	// create a timer with id=1 and delay of 200 milliseconds 

	SetTimer(1, 200, NULL);
}
