
// BugTracksDoc.cpp : implementation of the CBugTracksDoc class
//

#include "pch.h"
#include "framework.h"

#include "MainFrm.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BugTracks.h"
#endif

#include "BugTracksDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBugTracksDoc

IMPLEMENT_DYNCREATE(CBugTracksDoc, CDocument)

BEGIN_MESSAGE_MAP(CBugTracksDoc, CDocument)
END_MESSAGE_MAP()


// CBugTracksDoc construction/destruction

CBugTracksDoc::CBugTracksDoc() noexcept
{
	// TODO: add one-time construction code here

}

CBugTracksDoc::~CBugTracksDoc()
{
}

BOOL CBugTracksDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_BugDataArray.RemoveAll();
	m_nBugPosition = -1;
	return TRUE;
}




// CBugTracksDoc serialization

void CBugTracksDoc::Serialize(CArchive& ar)
{
	if (!ar.IsStoring()) // Loading (reading) data
	{
		SBugData Data;
		CString strOneLine;
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		// Read data in, one line at a time
		while (ar.ReadString(strOneLine))
		{
			// Display the raw line read for debugging
			//AfxMessageBox(strOneLine); // Display the line as wide string

			// Tokenize the line by spaces
			int tokenPos = 0;
			CString token1 = strOneLine.Tokenize(_T(" "), tokenPos);
			CString token2 = strOneLine.Tokenize(_T(" "), tokenPos);

			// Check if both tokens were successfully extracted
			if (!token1.IsEmpty() && !token2.IsEmpty())
			{
				// Convert the tokens to floats using _ttof (wide version of atof)
				Data.x = _ttof(token1);
				Data.y = _ttof(token2);

				// Add the data to the array
				m_BugDataArray.Add(Data);

				// Notify about successful parsing
				CString successMessage;
				successMessage.Format(_T("Successfully parsed line: \"%s\"\nParsed values: %f, %f"), strOneLine, Data.x, Data.y);
				pMain->ChangeStatusText(successMessage);
			}
			else
			{
				// Handle parsing failure
				CString errorMessage;
				errorMessage.Format(_T("Failed to parse line: \"%s\""), strOneLine);
				//AfxMessageBox(errorMessage);
				break; // Stop processing on failure
			}
		}

		// Notify about the number of successfully parsed data points
		CString message;
		message.Format(_T("Loaded % d points."), m_BugDataArray.GetSize());
		pMain->ChangeStatusText(message);
		//AfxMessageBox(message);
	}
}



#ifdef SHARED_HANDLERS

// Support for thumbnails
void CBugTracksDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CBugTracksDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBugTracksDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBugTracksDoc diagnostics

#ifdef _DEBUG
void CBugTracksDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBugTracksDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBugTracksDoc commands
