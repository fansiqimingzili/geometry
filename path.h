#ifndef PATH_H
#define PATH_H
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "define.h"
#include "point.h"
#include "rect.h"
#include "utils.h"
#include "parse.h"

namespace geometry {
	class Path
	{
	public:
		enum class PathVerb {
			kMove,
			kLine,
			kCubic,
			kQuad,
			kConic,
			kClose,
		};

		Path(const char* d_str);
		Path();
		~Path() = default;

		bool operator==(const Path& other);

		bool operator!=(const Path& other);

		void Set(const Path& path);

		void MakeFromString(const char* d_str);

		std::vector<Point> Approximate(float acceptable_error);

		Rect ComputeBounds() const;

		Path& MakeRect(float x, float y, float width, float height, float rx=0, float ry=0);

		Path& MakeEllipse(float cx,float cy,float ra,float rb);

		Path& MakeCircle(float center_x, float center_y, float radius);

		Path& MakeLine(const Point& a, const Point& b);

		void MoveTo(const Point& pt);
		void MoveTo( float x,float y);

		void LineTo(const Point&pt);
		void LineTo(float x, float y);

		void CubicBeizerTo(const Point& cp1,const Point& cp2,const Point& pt);
		void CubicBeizerTo(float cp1x,float cp1y,float cp2x,float cp2y, float x,float y);

		void QuadBeizierTo(const Point& cp,const Point& pt);
		void QuadBeizierTo(float cpx, float cpy, float x, float y);

		void ArcTo(float radiusx, float radiusy, float rot_x, float large_arc, float sweep_flag, Point& pt);
		void ArcTo(float radiusx, float radiusy, float rot_x, float large_arc, float sweep_flag, float endx,float endy);

		void CloseTo();

		Path& ReversePathTo(const Path&other);

		bool IsEmpty() const{
			if (GetVerbCounts()== 0)
				return true;
		}

		bool IsLastContourClosed() const {
			int verb_count =GetVerbCounts();
			if (verb_count== 0) {
				return false;
			}
			return PathVerb::kClose == verbs_[verb_count - 1];
		}

		PathVerb GetVerbAt(int index) {
			int size = verbs_.size();
			return verbs_[index];
		}

		Point GetPointAt(int index){
			int size = data_.size();
			return data_[index];
		}

		int GetVerbCounts() const{ return verbs_.size(); }
		int GetPointCounts()const{ return data_.size(); }

		std::vector<PathVerb> GetVerbs() const{ return verbs_;}
		std::vector<Point> GetPoints() const{ return data_;}

		int GetNumPerVerb (PathVerb verb)const;

		void ResetPath() { verbs_.clear(); data_.clear(); }

		Point& GetLastPoint() {
			if(data_.size()>0)
				return data_.back();
		}
	private:
		bool SubdividePoints(const Point* points,BezierCalculation bezierfunction,
			float t0, const Point& p0, float t1, const Point& p1, float& mid_t, Point& mid_p, float error_squared);

		void AddMove(std::vector<Point>& segment_points, const Point& p);

		void AddLine(std::vector<Point>& segment_points, const Point& p);

		void AddBezier(const Point* points,BezierCalculation bezierFunction, std::vector<Point>& segment_points,
			float error_squared, bool double_check_division);

		void CreateVerbSegments(PathVerb verb, const Point points[], std::vector<Point>& segment_points, float errorSquared);

		bool FromSVGString(char cmd, std::vector<float>&data,int cnum,Point&c, Point &lastc);

		int GetNumPerElement(char cmd);

		std::vector<PathVerb> verbs_;
		std::vector<Point> data_;
	};
}
#endif
