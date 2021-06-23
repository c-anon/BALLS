#pragma once
#include<vector>
#include <atltypes.h>


class CBall : public CRect
{
public:
    CBall(int left = 0, int top = 0, int right = 0, int bottom = 0, COLORREF color = RGB(0,0,0), int offX = 0, int offY = 0, CRect* bound = nullptr);
    CBall(CRect* baseRect, COLORREF color = RGB(0, 0, 0), int offX = 0, int offY = 0, CRect* bound = nullptr );
    CBall(CPoint coord, SIZE size, COLORREF color = RGB(0, 0, 0), int offX = 0, int offY = 0, CRect* bound = nullptr);

    ~CBall();

    inline void SetBallColor(COLORREF color);
    inline void SetBallSize(CRect* baseRect);

    void PaintBall(CDC* ballDC);
    void SetBall(CRect* baseRect, COLORREF color);
    void SetOffset(int offX, int offY);
    void SetBoundRect(CRect* bound);

    void MoveBall();

private:
    inline void CreateObjects(COLORREF ballColor);
    inline void DeleteObjects();
    void InitObjects(COLORREF ballColor);
    void InitBoundRect(CRect* boundRect);

    CPen* m_pBallPen;
    CBrush* m_pBallBrush;
    CRect* m_pBoundRect;

    int m_offX;
    int m_offY;

};

inline void CBall::CreateObjects(COLORREF ballColor)
{
    m_pBallPen->CreatePen(PS_SOLID, 3, ballColor);
    m_pBallBrush->CreateSolidBrush(ballColor);
}

inline void CBall::DeleteObjects()
{
    m_pBallPen->DeleteObject();
    m_pBallBrush->DeleteObject();
}

inline void CBall::SetBallColor(COLORREF color)
{
    DeleteObjects();
    CreateObjects(color);
}

inline void CBall::SetBallSize(CRect* baseRect)
{
    SetRect(baseRect->left, baseRect->top, baseRect->right, baseRect->bottom);
}

