#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <math.h>

namespace geometry {
    class Point {
    public:
        Point(float x, float y) :x_(x), y_(y) {

        }
        Point() {
            x_ = 0;
            y_ = 0;
        }

        Point Make(float x, float y) {
            return {x, y};
        };

        bool operator==(const Point& point) {
            return x_== point.x_ && y_ == point.y_;
        }

        bool operator!=(const Point& point) {
            return x_ != point.x_ ||y_ != point.y_;
        }

        bool Equals(float x, float y) const {return x_ == x && y_ == y;}

        friend Point operator+(const Point& a, const Point& b) {
            return { a.x_ + b.x_, a.y_ + b.y_ };
        }

        friend Point operator-(const Point& a, const Point& b) {
            return { a.x_ - b.x_, a.y_ - b.y_ };
        }

        friend float operator*(const Point& a, const Point& b) {
            return a.x_ * b.x_ + a.y_ * b.y_;
        }

        Point& operator+=(const Point& other) {
            x_ += other.x_;
            y_ += other.y_;
            return *this;
        }

        Point& operator-=(const Point& other) {
            x_ -= other.x_;
            y_ -= other.y_;
            return *this;
        }

        Point operator*(float scale) const {return { x_ * scale, y_ * scale }; }

        Point& Scale(float value) {
            x_ *= value;
            y_ *= value;
            return *this;
        }

        void Set(float x, float y) {
            x_ = x;
            y_ = y;
        }

        void SetX(float x) {
            x_ = x;
        }

        void SetY(float y) {
            y_ = y;
        }

        float X() const { return x_; };

        float Y() const { return y_; };

        void OffSet(float x, float y) {
            x_+= x;
            y_ += y;
        }
        
        float Length(){
             float lensq = x_ * x_ + y_ * y_;
             return sqrt(lensq);
        }

        Point Normal() {
            return Point(y_,-x_);
        }

        //gui yi
        Point& Normalize() {
            float len=Length();
            if (len > 0.0f) {
                float one_over_len = 1.0f / len;
                x_ *= one_over_len;
                y_ *= one_over_len;
            }
            return *this;
        }
        //absin
        static float Cross(Point& a, Point& b) { return  a.x_ * b.y_ - a.y_ * b.x_;};
        static float Cross(float x1, float y1, float x2, float y2) { return  x1 * y2 - y1*x2; };
        //abcos
        static float Dot(Point& a, Point& b) { return  a.x_ * b.x_ + a.y_ * b.y_; };
        static float Dot(float x1, float y1, float x2, float y2) { return  x1 * x2 + y1* y2; };
    private:
        float x_=0.0f;
        float y_=0.0f;

    };
}
#endif
