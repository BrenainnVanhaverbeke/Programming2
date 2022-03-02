#pragma once
#include "Vector2f.h"
class DaeShape
{
public:
    DaeShape(const Point2f& center, const Color4f& colour, float width, float height);
    virtual void Draw() const;
    void Translate(const Vector2f& translateVector);

protected:
    float m_Width;
    float m_Height;

    Point2f m_Center;
    Color4f m_Colour;
};