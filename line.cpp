#include"line.h"
namespace geometry {

    Line::Line(float x1, float y1, float x2, float y2):x1_(x1), y1_(y1), x2_(x2), y2_(y2){

    }
    Line::Line(Point p1, Point p2){
        x1_ = p1.X();
        y1_ = p1.Y();
        x2_ = p2.Y();
        y2_ = p2.Y();
    }

    void  Line::OffSet(float x, float y) {
        x1_ += x;
        y1_ += y;
        x2_ += x;
        y2_ += y;
    }

    void  Line::Scale(float value) {
        x1_ *= value;
        y1_ *= value;
        x2_ *= value;
        y2_ *= value;
    }

    //¹éÒ»»¯
    void Line::Normalize() {
        float dx = x2_ - x1_;
        float dy = y2_ - y1_;
        float lensq = dx * dx + dy * dy;
        if (lensq > 0.0f) {
            float one_over_len = 1.0f / sqrt(lensq);
            x1_ *= one_over_len;
            y1_ *= one_over_len;
            x2_ *= one_over_len;
            y2_ *= one_over_len;
        }
    }

    Rect Line::ComputeBounds() const {
        float L = fmax(x1_, x2_);
        float R = fmin(x1_, x2_);
        float T = fmax(y1_, y2_);
        float B = fmin(y1_, y2_);
        return Rect(L, R, T, B);
    }

    bool Line::ContainsPoint(float x, float y) const {
        if (Point::Cross(x1_ - x, y1_ - x, x2_ - x, y2_ - y) == 0 && Point::Dot(x1_ - x, y1_ - x, x2_ - x, y2_ - y) <= 0)
            return true;
        return false;
    }
    bool Line::ContainsPoint(Point& pt) const {
        if (Point::Cross(x1_ - pt.X(), y1_ - pt.Y(), x2_ - pt.X(), y2_ - pt.Y()) == 0 
            && Point::Dot(x1_ - pt.X(), y1_ - pt.Y(), x2_ - pt.X(), y2_ - pt.Y()) <= 0)
            return true;
        return false;
    }
}