#ifndef POINT3D_H
#define POINT3D_H

#include <stdio.h>
#include <math.h>
#include "matrix3d.h"

namespace geometry {
 class Point3D {
    public:
        Point3D()
        {

        }
        Point3D(float x, float y, float z, float w=1.0) : x_(x), y_(y), z_(z), w_(w)
        {

        }
        Point3D Make(float x, float y,float z) {
            return {x,y,z};
        };

        bool operator==(const Point3D& point) {
            return x_== point.x_ && y_ == point.y_&& z_ == point.z_;
        }

        bool operator!=(const Point3D& point) {
            return x_ != point.x_ ||y_ != point.y_||z_ != point.z_;
        }

        //add
        Point3D& operator+=(const Point3D& vec){
            w_ = 1;
            x_ = x_ + vec.x_;
            y_ = y_ + vec.y_;
            z_ = z_ + vec.z_;
            return *this;
        }

        //sub
        Point3D& operator-=(const Point3D& vec){
            w_ = 1;
            x_ = x_ - vec.x_;
            y_ = y_ - vec.y_;
            z_ = z_ - vec.z_;
            return *this;
        }

        // //向量乘矩阵
        // Point3D& operator*=(const Matrix3D& mat)
        // {
        //     x_ = x_ * mat.m_[0][0] + y_* mat.m_[1][0] + z_ * mat.m[2][0] + w_* mat.m[3][0];
        //     y_ = x_ * mat.m_[0][1] + y_ * mat.m_[1][1] + z_ * mat.m[2][1] + w_ * mat.m[3][1];
        //     z_  = x_  * mat.m_[0][2] + y_ * mat.m_[1][2] + z_ * mat.m[2][2] + w_ * mat.m[3][2];
        //     w_  = x_  * mat.m_[0][3] + y_ * mat.m_[1][3] + z_ * mat.m[2][3] + w_ * mat.m[3][3];
        //     return *this;
        // }

        friend Point3D operator+(const Point3D& a, const Point3D& b) {
            return { a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_ };
        }

        friend Point3D operator-(const Point3D& a, const Point3D& b) {
            return { a.x_ - b.x_, a.y_ - b.y_ , a.z_ - b.z_ };
        }

        friend float operator*(const Point3D& a, const Point3D& b) {
            return a.x_ * b.x_ + a.y_ * b.y_+a.z_ * b.z_;
        }

          Point3D operator*(float scale) const {return {x_ * scale, y_ * scale,z_*scale }; }

        void Set(float x, float y,float z) {
            x_ = x;
            y_ = y;
            z_ = z;
        }

        void SetX(float x) {
            x_ = x;
        }

        void SetY(float y) {
            y_ = y;
        }

        void SetZ(float z) {
            z_ = z;
        }

        float X() const { return x_; };

        float Y() const { return y_; };

        float Z() const { return z_; };

        Point3D& OffSet(float x, float y,float z) {
            x_+= x;
            y_ += y;
            z_ += z;
            return *this;
        }

        Point3D& Scale(float value) {
            x_ *= value;
            y_ *= value;
            z_ *= value;
            return *this;
        }

        float Length() { return sqrt(x_ * x_ + y_ * y_ + z_ * z_); }
        //向量归一
        Point3D& Normalize(){
            float len = Length();
            if (len != 0.0f)
            {   
                x_ = x_ / len;
                y_ = y_ / len;
                z_ = z_ / len;
            }
            return *this;
        }   
        //absin
        static Point3D Cross(Point3D& a, Point3D& b) { 
            return  Point3D(a.y_ * b.z_ - a.z_ * b.y_,
                            a.z_ * b.x_ - a.x_ * b.z_,
                            a.x_ * b.y_ - a.y_ * b.x_);
        }
        //abcos
        static float Dot(Point3D& a, Point3D& b) { 
            return  a.x_ * b.x_ + a.y_ * b.y_+ a.z_ * b.z_; 
        }
    private:
        //表示向量时w无用
        float x_=0.0f; 
        float y_=0.0f; 
        float z_=0.0f; 
        float w_=1.0f; 
 };
}
#endif
