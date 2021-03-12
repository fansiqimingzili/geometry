#ifndef Ray2_hpp
#define Ray2_hpp

#include <stdio.h>
#include "point.h"
#include "rect.h"

namespace geometry {
    class Line {

    public:
        Line(float x1,float y1, float x2, float y2);
        Line(Point p1, Point p2);
        Line() = default;
        ~Line() = default;

        Line Make(float x1, float y1, float x2, float y2) {
            return {x1_,y1_, x2_,y2_ };
        };

        bool operator==(const Line& line) {
            return x1_ == line.x1_ && y1_ == line.y1_ && x2_ == line.x2_ && y2_ == line.y2_;
        }

        bool operator!=(const Line& line) {
            return x1_!= line.x1_ ||y1_ != line.y1_ || x2_ != line.x2_ || y2_ != line.y2_;
        }

        friend bool operator==(const Line& a, const Line& b) {
            return a.x1_ == b.x1_ && a.y1_ == b.y1_&& a.x2_ == b.x2_ && a.y2_ == b.y2_;
        };
        friend bool operator!=(const Line& a, const Line& b) {
            return a.x1_ != b.x1_ || a.y1_ != b.y1_|| a.x2_ != b.x2_ || a.y2_ != b.y2_;
        }

        Line operator*(float scale) const { return { x1_ * scale, y1_ * scale, x2_ * scale, y2_ * scale }; }

        void Set(float x1, float y1,float x2, float y2) {
            x1_ = x1;
            y1_ = y1;
            x2_ = x2;
            y2_ = y2;
        }

        void SetStartPoint(float x,float y) {
            x1_ = x;
            y1_ = y;
        }

        void SetStartPoint(Point& pt) {
            x1_ = pt.X();
            y1_ = pt.Y();
        }

        void SetEndPoint(float x, float y) {
            x2_ = x;
            y2_ = y;
        }

        void SetEndPoint(Point& pt) {
            x2_ = pt.X();
            y2_ = pt.Y();
        }

        Point GetStartPoint() const { return Point(x1_,y1_); };
        Point GetEndPoint() const { return Point(x2_, y2_); };

        float GetStartPointX() const { return x1_; };
        float GetStartPointY() const { return y1_; };

        float GetEndPointX() const { return x2_; };
        float GetEndPointY() const { return y2_; };

        void OffSet(float x, float y);

        void Scale(float value);

        //归一化
        void Normalize();

        float Length() {
            float dx = x2_ - x1_;
            float dy = y2_ - y1_;
            return sqrt(dx * dx + dy * dy);
        }

        static bool Intersects(float ax1, float ay1, float ax2, float ay2,
            float bx1, float by1, float bx2, float by2);

        //相交
        bool Intersects(const Line& r) const;

        static bool Intersects(const Line& a, const Line& b);

        Rect ComputeBounds() const;

        bool ContainsPoint(float x, float y) const;
        bool ContainsPoint(Point& pt) const;

    private:
        float x1_=0.0f;
        float y1_ = 0.0f;
        float x2_ = 0.0f;
        float y2_ = 0.0f;
    };
}
#endif /* Ray2_hpp */