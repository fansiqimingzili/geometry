#include"rect.h"

namespace geometry {
    Rect::Rect(float left, float top, float right, float bottom)
        :left_(left), top_(top), right_(right), bottom_(bottom) {

    }
    Rect::Rect() : left_(0.0f), top_(0.0f), right_(0.0f), bottom_(0.0f) {

    }

    static Rect CreateRectFromWH(float w, float h) {
        return  Rect{ 0, 0, w, h };
    }
    
    static Rect CreateRectFromLTRB(float l, float t, float r, float b) {
        return Rect{ l, t, r, b };
    }


    static Rect CreateRectFromXYWH(float x, float y, float w, float h) {
        return Rect{ x, y, x + w, y + h };
    }

    bool Rect::IsEmpty() const {
        return !(left_ < right_&& top_ < bottom_);
    }

    bool Rect::IsSorted() const {
        return left_ <= right_ && top_ <= bottom_;
    }

    bool Rect::IsFinite() const {
        float accum = 0;
        accum *= left_;
        accum *= top_;
        accum *= right_;
        accum *= bottom_;
        // value==value will be true iff value is not NaN
        // TODO: is it faster to say !accum or accum==accum?//???
        return !(accum != accum);
    }

    float Rect::GetMinX() const { 
        return left_; 
    }

    float Rect::GetMinY() const { 
        return top_; 
    }

    float Rect::GetLeft() const { 
        return left_; 
    }

    float Rect::GetTop() const { 
        return top_; 
    }

    float Rect::GetRight() const { 
        return right_; 
    }

    float Rect::GetBottom() const { 
        return bottom_; 
    }

    float Rect::GetWidth() const { 
        return right_ - left_; 
    }

    float Rect::GetHeight() const { 
        return bottom_ - top_; 
    }

    float Rect::GetCenterX() const {
        return left_ * 0.5 + right_ * 0.5;
    }

    float Rect::GetCenterY() const {
        // don't use SkScalarHalf(fTop + fBottom) as that might overflow before the 0.5
        return top_ * 0.5 + bottom_ * 0.5;
    }

    void Rect::SetLeft(float left) {
        left_ = left;
    }

    void Rect::SetRight(float right) {
        right_ = right;
    }

    void Rect::SetTop(float top) {
        top_ = top;
    }

    void Rect::SetBottom(float bottom) {
        bottom_ = bottom;
    }

    void Rect::SetLTRB(float left, float top, float right, float bottom) {
        left_ = left;
        top_ = top;
        right_ = right;
        bottom_ = bottom;
    }

    void Rect::Set(const Point& p0, const Point& p1) {
        left_ = fmin(p0.X(), p1.Y());
        right_ = fmax(p0.X(), p1.X());
        top_ = fmin(p0.Y(), p1.Y());
        bottom_ = fmax(p0.Y(), p1.Y());
    }

    void Rect::SetXYWH(float x, float y, float width, float height) {
        left_ = x;
        top_ = y;
        right_ = x + width;
        bottom_ = y + height;
    }

    void  Rect::ToQuad(Point quad[4]) const {
        quad[0].Set(left_,top_);
        quad[1].Set(right_,top_);
        quad[2].Set(right_, bottom_);
        quad[3].Set(left_, bottom_);
    }

    Rect Rect::MakeOffset(float dx, float dy) const {
        return CreateRectFromLTRB(left_ + dx, top_ + dy, right_ + dx, bottom_ + dy);
    }

    //位锟斤拷
    void  Rect::Offset(float dx,float dy) {
        left_ += dx;
        top_ += dy;
        right_ += dx;
        bottom_ += dy;
    }

    //锟斤拷位锟斤拷
    void  Rect::Offset(const Point& pt) {
        this->Offset(pt.X(), pt.Y());
    }

    //锟洁交
    bool  Rect::Intersects(float al, float at, float ar, float ab,
        float bl, float bt, float br, float bb) {
        float L = fmax(al, bl);
        float R = fmin(ar, br);
        float T = fmax(at, bt);
        float B = fmin(ab, bb);
        return L < R&& T < B;
    }

    bool  Rect::Intersects(const Rect& r) const {
        return Intersects(left_, top_, right_, bottom_, r.left_, r.top_, r.right_, r.bottom_);
    }

    bool  Rect::Intersects(const Rect& a, const Rect& b) {
        return Intersects(a.left_, a.top_, a.right_, a.bottom_,
            b.left_, b.top_, b.right_, b.bottom_);
    }

    bool  Rect::ContainsPoint(float x, float y) const {
        return x >= left_ && x < right_&& y >= top_ && y < bottom_;
    }

    bool  Rect::Contains(const Rect& r) const {
        // todo: can we eliminate the this->isEmpty check?
        return !r.IsEmpty() && !this->IsEmpty() &&
            left_ <= r.left_ && top_ <= r.top_ &&
            right_ >= r.right_ && bottom_ >= r.bottom_;
    }

    void  Rect::Sort() {
        using std::swap;
        if (left_ > right_) {
            swap(left_, right_);
        }

        if (top_ > bottom_) {
            swap(top_, bottom_);
        }
    }

    Rect Rect::MakeSorted() const {
        return CreateRectFromLTRB(fmin(left_, right_), fmin(top_, bottom_),
            fmax(left_, right_), fmax(top_, bottom_));
    }
    Rect Rect::ExpandBounds(const Point& p) {
        float L = fmin(left_, p.X());
        float T = fmin(top_, p.Y());
        float R = fmax(right_, p.X());
        float B = fmax(bottom_, p.Y());
        this->SetLTRB(L, T, R, B);
        return *this;
    }
}