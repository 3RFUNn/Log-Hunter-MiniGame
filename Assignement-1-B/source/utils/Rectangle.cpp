#include "../../include/utils/Rectangle.h"
#include <vector>
#include <iostream>

bool Rectangle::inside(float x, float y) const
{
    if (x >= this->getTopLeft().x and x <= this->getBottomRight().x
        and y >= this->getTopLeft().y and y <= this->getBottomRight().y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    // IX.B Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.
    // coords for this rectangle

    // coords for the rectangle rect
    Vector2f l1 = rect.getTopLeft();
    Vector2f r1 = rect.getBottomRight();

    if (inside(l1.x, l1.y) || inside(r1.x, l1.y) || inside(l1.x, r1.y) || inside(r1.x, r1.y))
    {
        return true;
    }
    return false;

}

