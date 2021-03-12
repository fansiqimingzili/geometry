//
//  Rect.hpp
//  svganalyze
//
//  Created by Bilibili on 2020/12/18.
//
#ifndef RECT_HPP
#define RECT_HPP

#include <stdio.h>
#include "point.h"
#include <math.h>
#include <utility>

namespace geometry {
    class Rect {
    public:
        Rect(float left, float top, float right, float bottom);
        Rect();
        ~Rect() = default;
        //float make(0, 0, w, h)
        static Rect CreateRectFromWH(float w, float h) {
            return  Rect{ 0, 0, w, h };
        }

        static Rect CreateRectFromLTRB(float l, float t, float r, float b) {
            return Rect{ l, t, r, b };
        }


        static Rect CreateRectFromXYWH(float x, float y, float w, float h) {
            return Rect{ x, y, x + w, y + h };
        }

        bool operator==(const Rect& other) const {
            return left_ == other.left_ && right_ == other.right_ && top_ == other.top_
                && bottom_ == other.bottom_;
        }

        bool operator!=(const Rect& other) const {
            return left_ == other.left_ || right_ == other.right_ || top_ == other.top_
                || bottom_ == other.bottom_;
        }

        bool IsEmpty() const;

        bool IsSorted() const;

        bool IsFinite() const;

        float GetMinX() const;

        float GetMinY() const;

        float GetLeft() const;

        float GetTop() const;

        float GetRight() const;

        float GetBottom() const;

        float GetWidth() const;

        float GetHeight() const;

        float GetCenterX() const;

        float GetCenterY() const;

        void SetLeft(float left);

        void SetRight(float right);

        void SetTop(float top);

        void SetBottom(float bottom);

        void SetLTRB(float left, float top, float right, float bottom);

        void Set(const Point& p0, const Point& p1);

        void SetXYWH(float x, float y, float width, float height);

        void ToQuad(Point quad[4]) const;

        Rect MakeOffset(float dx, float dy) const;

        //位锟斤拷
        void Offset(float dx, float dy);

        //锟斤拷位锟斤拷
        void Offset(const Point& pt);

        static bool Intersects(float al, float at, float ar, float ab,
            float bl, float bt, float br, float bb);

        //锟洁交
        bool Intersects(const Rect& r) const;

        static bool Intersects(const Rect& a, const Rect& b);

        bool ContainsPoint(float x, float y) const;

        bool Contains(const Rect& r) const;

        void Sort();

        Rect MakeSorted() const;

        Rect ExpandBounds(const Point& p);
    private:
        float left_;   //!< smaller x-axis bounds
        float top_;    //!< smaller y-axis bounds
        float right_;  //!< larger x-axis bounds
        float bottom_; //!< larger y-axis bounds
    };
}
#endif /* Rect_hpp */