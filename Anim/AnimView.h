
// AnimView.h : interface of the CAnimView class
//

#pragma once
#include<vector>
#include"CBall.h"
#define MAX_SIZE 10
class CAnimView : public CView
{
protected: // create from serialization only
	CAnimView() noexcept;
	DECLARE_DYNCREATE(CAnimView)

// Attributes
public:
	CAnimDoc* GetDocument() const;
	
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CAnimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();

public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
private:
	//CRect*		m_pBall;
	//CPen*		m_pBallPen;
	//CBrush*		m_pBallBrush;
	UINT_PTR	m_nTimerID;
	/*int			m_nBallOffX;
	int			m_nBallOffY;*/
	BOOL		m_bStart;
	CRect*		m_pClientRect;

	std::vector<CBall*> m_pBalls;
	//
	BOOL m_bPLus;
	BOOL m_bMinus;
	int numberOfBalls;
	int CAnimView::random(int from, int to);
	
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPlus();
	afx_msg void OnMinus();
	afx_msg void OnUpdatePlus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMinus(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in AnimView.cpp
inline CAnimDoc* CAnimView::GetDocument() const
   { return reinterpret_cast<CAnimDoc*>(m_pDocument); }
#endif

