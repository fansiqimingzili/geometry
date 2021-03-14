#include "conic.h"

namespace geometry{
    Conic::Conic():ra_(0.0f),rb_(0.0f),rotx_(0.0f),large_arc_(1),sweep_direction_(1),
                   x1_(0.0f),y1_(0.0f),x2_(0.0f),y2_(0.0f){

    }
    Conic::Conic(float ra,float rb,float rotx,int large_arc,int sweep_direction,
                 float x1,float y1,float x2,float y2){
        ra_= fabsf(ra);			                                // y radius
		rb_ = fabsf(rb);			                            // x radius
		rotx_ = rotx / 180.0f * PI;		                        // x rotation angle
		large_arc_ = fabsf(large_arc) > 1e-6 ? 1 : 0;	        // Large arc
		sweep_direction_= fabsf(sweep_direction) > 1e-6 ? 1 : 0;// Sweep direction
		x1_ = x1;					                            // start point
		y1_ = y1;
		x2_=  x2;                                               // end point
		y2_ = y2;
    }

    Point Conic::ComputeCenterP(){
        float dx = x1_ - x2_;
		float dy = y1_ - y2_;
        float sinrx = sinf(rotx_);
		float cosrx = cosf(rotx_);
		float x1p = cosrx * dx / 2.0f + sinrx * dy / 2.0f;
		float y1p = -sinrx * dx / 2.0f + cosrx * dy / 2.0f;

        float s = 0.0f;
		float sa = (ra_ * ra_) * (rb_ * rb_) - (ra_ * ra_) * (y1p * y1p) - (rb_ * rb_) * (x1p * x1p);
		float sb = (ra_ * ra_) * (y1p * y1p) + (rb_ * rb_) * (x1p * x1p);
		if (sa < 0.0f) sa = 0.0f;
		if (sb > 0.0f)
			s = sqrtf(sa / sb);
		if (large_arc_ == sweep_direction_)
			s = -s;
		float cxp = s * ra_ * y1p / rb_;
		float cyp = s * -rb_ * x1p / ra_;
        return Point(cxp,cyp);
    }
    Point Conic::ComputeCenter(){
		float cx = (x1_ + x2_) / 2.0f + cosf(rotx_) * ComputeCenterP().X() - sinf(rotx_) *  ComputeCenterP().Y() ;
		float cy = (y1_ + y2_) / 2.0f + sinf(rotx_) * ComputeCenterP().X()  + cosf(rotx_) * ComputeCenterP().Y() ;
        return Point(cx,cy);
    }
    float Conic::CaculateDeltaAngle(){
		float ux = (x1p - cxp) / rx;
		float uy = (y1p - cyp) / ry;
		float vx = (-x1p - cxp) / rx;
		float vy = (-y1p - cyp) / ry;
		float a1 = VecAngle(1.0f, 0.0f, ux, uy);	// Initial angle
		float da = VecAngle(ux, uy, vx, vy);		// Delta angle
    }
    void  ConicToCubics(){
        
    }
}