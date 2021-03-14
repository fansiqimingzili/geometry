#ifndef CONIC_H
#define CONIC_H

#include "define.h"
#include "point.h"
namespace geometry {
    class Conic{
    public:
        Conic();
        Conic(float ra,float rb,float rotx,int large_arc,int sweep_direction,float x1,float y1,float x2,float y2);
        ~Conic()=default;

        Point ComputeCenterP();
        Point ComputeCenter();
        float CaculateDeltaAngle();
        void  ConicToCubics();
    private:
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