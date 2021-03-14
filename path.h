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
			kClose
		};

		Path(const char* d_str);
		Path();
		~Path() = default;

		bool operator==(const Path& path);

		bool operator!=(const Path& path);

		void Set(const Path& path);

		Path& MakeFromString(const char* d_str);

		std::vector<Point> Approximate(float acceptable_error);

		Rect ComputeBounds() const;

		Path& MakeRect(float x, float y, float width, float height, float rx=0, float ry=0);

		Path& MakeEllipse(float cx,float cy,float ra,float rb);

		Path& MakeCircle(float center_x, float center_y, float radius);

		Path& MakeLine(const Point& a, const Point& b);

		void MoveTo(Point& pt);
		void MoveTo( float x,float y);

		void LineTo(Point&pt);
		void LineTo(float x, float y);

		void CubicBeizerTo(Point& cp1, Point& cp2, Point& pt);
		void CubicBeizerTo(float cp1x,float cp1y,float cp2x,float cp2y, float x,float y);

		void QuadBeizierTo(Point& cp,Point& pt);
		void QuadBeizierTo(float cpx, float cpy, float x, float y);

		void ArcTo(float radiusx, float radiusy, float rot_x, float large_arc, float sweep_flag, Point& pt);
		void ArcTo(float radiusx, float radiusy, float rot_x, float large_arc, float sweep_flag, float endx,float endy);

		void CloseTo();

		bool IsEmpty() {
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

		Point GetPoint(int index) {
			int size = data_.size();
			if (index<0||index > size)
				return Point(0, 0);
			return data_[index];
		}

		int GetVerbCounts() const { return verbs_.size(); }

		void ResetPath() { verbs_.clear(); data_.clear(); }
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

		int GetNumPerElement(PathVerb verb);

		std::vector<PathVerb> verbs_;
		std::vector<Point> data_;
	};
}
#endif
