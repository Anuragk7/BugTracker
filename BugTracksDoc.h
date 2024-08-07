
// BugTracksDoc.h : interface of the CBugTracksDoc class
//

#include <afxtempl.h>
#include "MainFrm.h"
#pragma once

struct SBugData
{
	float x;
	float y;
};


class CBugTracksDoc : public CDocument
{
protected: // create from serialization only
	CBugTracksDoc() noexcept;
	DECLARE_DYNCREATE(CBugTracksDoc)

// Attributes
public:
	CArray <SBugData, SBugData> m_BugDataArray;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CBugTracksDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int m_nBugPosition;
};
