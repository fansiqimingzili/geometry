#ifndef CONIC_H
#define CONIC_H

#include "define.h"
#include "point.h"
#include "utils.h"
namespace geometry {
    class Conic{
    public:
        Conic();
        Conic(float ra,float rb,float rotx,int large_arc,int sweep_direction,float x1,float y1,float x2,float y2);
        ~Conic()=default;

        float ComputeDistance();
        Point ComputeCenter();
        float CaculateInitAngle();
        float CaculateDeltaAngle();

        float GetRadiusA(){
            return ra_;
        }
        float GetRadiusB(){
            return rb_;
        }

        float GetRotX(){
            return rotx_;
        }
        Point GetArcEnd(){
            return Point (x2_,y2_);
        }

    private:
        Point ComputePointP();
        Point ComputeCenterP();
        float ra_;
        float rb_;
        float rotx_;
        int large_arc_;
        int sweep_direction_;
        float x1_,y1_;
        float x2_,y2_;
    };
}
#endif