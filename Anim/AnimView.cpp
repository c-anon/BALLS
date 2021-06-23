
// AnimView.cpp : implementation of the CAnimView class
//

#include "pch.h"
#include "framework.h"
#include "CBall.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Anim.h"
#endif
#include "MainFrm.h"
#include "AnimDoc.h"
#include "AnimView.h"
#include<vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define BALLSIZE 60
#define BLUE RGB(0,0,255)
#define MAX_SIZE 10
// CAnimView

IMPLEMENT_DYNCREATE(CAnimView, CView)

BEGIN_MESSAGE_MAP(CAnimView, CView)
	ON_COMMAND(ID_START_STOP, &CAnimView::OnStart)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_PLUS, &CAnimView::OnPlus)
	ON_COMMAND(ID_MINUS, &CAnimView::OnMinus)
	ON_UPDATE_COMMAND_UI(ID_PLUS, &CAnimView::OnUpdatePlus)
	ON_UPDATE_COMMAND_UI(ID_MINUS, &CAnimView::OnUpdateMinus)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CAnimView construction/destruction
void CALLBACK ZfxTimerProc(
	HWND hWNd,
	UINT nMsg,
	UINT nIDEvent,
	DWORD dwTime
)
{
	::SendMessage(hWNd, WM_TIMER, 0, 0);
}




CAnimView::CAnimView() noexcept
{
	m_bPLus = TRUE;
	m_bMinus = FALSE;

	m_bStart = FALSE;//ok
	
	numberOfBalls = 0;
	m_pClientRect = new CRect(0, 0, 0, 0); //ok
	
}

CAnimView::~CAnimView()
{

	delete m_pClientRect;
}

BOOL CAnimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAnimView drawing

void CAnimView::OnDraw(CDC* pDC)
{

	CDC memDC; //pamieciowy kontekst urzadzenia	//ok
	BOOL b = memDC.CreateCompatibleDC(pDC);
	ASSERT(b);
	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pClientRect->Width(), m_pClientRect->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pClientRect, RGB(230, 230, 230));		//ok
	
	for (auto x : m_pBalls)
		x->PaintBall(&memDC);
	
	
	

	b = pDC->BitBlt(0, 0, m_pClientRect->Width(), m_pClientRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();

	


	
	
}


// CAnimView diagnostics

#ifdef _DEBUG
void CAnimView::AssertValid() const
{
	CView::AssertValid();
}

void CAnimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnimDoc* CAnimView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
	return (CAnimDoc*)m_pDocument;
}
#endif //_DEBUG


// CAnimView message handlers


void CAnimView::OnStart()
{
	// TODO: Add your command handler code here
	m_bStart = !m_bStart;
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(m_bStart);
}


void CAnimView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//m_nTimerID = SetTimer(WM_USER + 1, 20, NULL);
	m_nTimerID = SetTimer(WM_USER + 1, 20, ZfxTimerProc);
	// TODO: Add your specialized code here and/or call the base class
}


void CAnimView::OnDestroy()
{
	KillTimer(m_nTimerID);
	CView::OnDestroy();

	// TODO: Add your message handler code here
}


void CAnimView::OnTimer(UINT_PTR nIDEvent)
{
	
	if (m_bStart)
	{
		for (auto x : m_pBalls)
		{
			x->MoveBall();
		}
	}
	Invalidate();	// odrysowanie
	CView::OnTimer(nIDEvent);
}


void CAnimView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	GetClientRect(m_pClientRect);
	CView::OnPrepareDC(pDC, pInfo);
}


BOOL CAnimView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return 1;
	//return CView::OnEraseBkgnd(pDC);
}


void CAnimView::OnPlus()
{
	
	if (numberOfBalls <= 10)
	{	numberOfBalls++;

		srand((unsigned)time(NULL));
		int position = random(20, 200);
		int size = random(30, 130);
		int offsetX = random(1, 10);
		int offsetY = random(1, 8);
		int R = random(150, 250);
		int G = random(150, 250);
		int B = random(150, 250);

		m_pBalls.push_back(new CBall(
			position, position, position + size, position + size,
			RGB(R, G, B),
			offsetX, offsetY,
			m_pClientRect));
		
	}
}


void CAnimView::OnMinus()
{
	// TODO: Add your command handler code here
	m_bPLus = FALSE;
	m_bMinus = TRUE;
	if (numberOfBalls >= 1)
		numberOfBalls--;
	m_pBalls.pop_back();
}


void CAnimView::OnUpdatePlus(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable(m_bMinus);
	if(numberOfBalls>=10)
		pCmdUI->Enable(FALSE);
		
}


void CAnimView::OnUpdateMinus(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (numberOfBalls <= 1)
		pCmdUI->Enable(FALSE);
	
}

int CAnimView::random(int from, int to)
{
	int randNum = (std::rand() % to + from + 1);
	return randNum;
}


void CAnimView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	for (auto x : m_pBalls)
	{
		if ((cx <= x->right))
			
		{
			x->MoveToX(m_pClientRect->right - x->Width() - 1);
			
		}
		if ((cx <= x->left))

		{
			x->MoveToX(m_pClientRect->left + x->Width() + 1);

		}
		
		if (cy <= x->bottom)
			
		{
			x->MoveToY(m_pClientRect->bottom - x->Width() - 1);
			
		}

		if (cy <= x->top)

		{
			x->MoveToY(m_pClientRect->top + x->Width() + 1);

		}
			
	}
	// TODO: Add your message handler code here
}
