
// BugTracksView.h : interface of the CBugTracksView class
//

#pragma once


class CBugTracksView : public CView
{
protected: // create from serialization only
	CBugTracksView() noexcept;
	DECLARE_DYNCREATE(CBugTracksView)

// Attributes
public:
	CBugTracksDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CBugTracksView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTrackAnimate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTrackAnimate();
	afx_msg void OnTrack2Animate2();
};

#ifndef _DEBUG  // debug version in BugTracksView.cpp
inline CBugTracksDoc* CBugTracksView::GetDocument() const
   { return reinterpret_cast<CBugTracksDoc*>(m_pDocument); }
#endif

