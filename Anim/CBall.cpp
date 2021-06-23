#include "pch.h"
#include "CBall.h"


CBall::CBall(int left, int top, int right, int bottom, COLORREF color, int offX, int offY, CRect* bound)
	:CRect( left, top, right, bottom ), m_offX( offX ), m_offY( offY )
{
	InitObjects(color);
	InitBoundRect(bound);
}

CBall::CBall(CRect* baseRect, COLORREF color, int offX, int offY, CRect* bound)
	:CRect(baseRect), m_offX(offX), m_offY(offY)
{
	InitObjects(color);
	InitBoundRect(bound);
}

CBall::CBall(CPoint coord, SIZE size, COLORREF color, int offX, int offY, CRect* bound)
	:CRect(coord, size), m_offX(offX), m_offY(offY)
{
	InitObjects(color);
	InitBoundRect(bound);
}

CBall::~CBall()
{
	DeleteObjects();

	delete m_pBallPen;
	delete m_pBallBrush;
}

void CBall::InitObjects(COLORREF ballColor)
{
	m_pBallPen = new CPen(PS_SOLID, 1, ballColor);
	m_pBallBrush = new CBrush(ballColor);
}

void CBall::InitBoundRect(CRect* boundRect)
{
	if (boundRect)
		m_pBoundRect = boundRect;
	else
		m_pBoundRect = new CRect(0, 0, 0, 0);
}

void CBall::PaintBall(CDC* ballDC)
{
	CPen* pOldPen = ballDC->SelectObject(m_pBallPen);
	CBrush* pOldBrush = ballDC->SelectObject(m_pBallBrush);

	ballDC->Ellipse(this);
	ballDC->SelectObject(pOldPen);
	ballDC->SelectObject(pOldBrush);
}

void CBall::SetBall(CRect* baseRect, COLORREF color)
{
	SetBallSize(baseRect);
	SetBallColor(color);
}

void CBall::SetOffset(int offX, int offY)
{
	m_offX = offX;
	m_offY = offY;
}

void CBall::SetBoundRect(CRect* bound)
{
	m_pBoundRect = bound;
}

void CBall::MoveBall()
{
	if (left <= m_pBoundRect->left || right >= m_pBoundRect->right)
		m_offX = -m_offX;

	if (top <= m_pBoundRect->top || bottom >= m_pBoundRect->bottom)
		m_offY = -m_offY;

	OffsetRect(m_offX, m_offY);
}