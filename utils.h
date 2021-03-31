#ifndef GRAPHIC_UTILS_H
#define GRAPHIC_UTILS_H
#include <string.h>
#include <vector>
#include <algorithm>
#include "point.h"
#include "line.h"
#include "define.h"
namespace geometry {

	typedef Line Ray2D;
	typedef Point Vector;

	static float VecLength(float x, float y) { return sqrtf(x * x + y * y); }

	static float VecCos(float ux, float uy, float vx, float vy)
	{
		return (ux * vx + uy * vy) / (VecLength(ux, uy) * VecLength(vx, vy));
	}

	static float VecAngle(float ux, float uy, float vx, float vy)
	{
		float r = VecCos(ux, uy, vx, vy);
		if (r < -1.0f)
			r = -1.0f;
		if (r > 1.0f)
			r = 1.0f;
		return ((ux * vy < uy* vx) ? -1.0f : 1.0f) * acosf(r);
	}

	static  float Distance(const Point& a, const Point& b) {
		return sqrtf((a.X() - b.X()) * (a.X() - b.X()) + (a.Y() - b.Y()) * (a.Y() - b.Y()));
	};
	//�ж��ཻ
	static bool IsDetectIntersect(Ray2D ray, Point p1, Point p2)
	{
		float pointy;//����Y���꣬x�̶�ֵ
		if (p1.X() == p2.X())
		{
			return false;
		}
		else if (p1.Y() == p2.Y())
		{
			pointy = p1.Y();
		}
		else
		{
			//ֱ������ʽ���̣�(y-y2)/(y1-y2) = (x-x2)/(x1-x2)
			float a = p1.X() - p2.X();
			float b = p1.Y() - p2.Y();
			float c = p2.Y() / b - p2.X() / a;
			pointy = b / a * ray.GetStartPointX() + b * c;
		}

		if (pointy < ray.GetStartPointY())
		{
			//����yС���������y
			return false;
		}
		else
		{
			Point left_point = p1.X() < p2.X() ? p1 : p2;//��˵�
			Point right_point = p1.X() < p2.X() ? p2 : p1;//�Ҷ˵�
			//����xλ���߶������˵�x֮�⣬�ཻ���߶�ĳ���˵�ʱ����������L���������һ�ߵĶ˵��Ϊ����(�����ǣ�ֻ���Ҷ˵��Ϊ����)
			if ((ray.GetStartPointX()<= left_point.X()) || (ray.GetStartPointX()> right_point.X()))
			{
				return false;
			}
		}

		return true;
	}
	//�жϵ��Ƿ��ڶ������
	static bool IsPointInsidePolygon(Point point, std::vector<Point>vertice_points)
	{
		int len = vertice_points.size();
		// Ray2D ray = new Ray2D(point, new Vector3(0, 1)); //y��������
		Ray2D ray;
		ray.SetStartPoint(point);
		ray.SetEndPoint(0, 1);
		//ray.x = 0;
		//ray.y = 1;
		//ray.origin_.x_ = point.x_;
		//ray.origin_.y_ = point.y_;
		int num = 0;
		for (int i = 1; i < len; i++)
		{
			if (IsDetectIntersect(ray, vertice_points[i - 1], vertice_points[i]))
			{
				num++;
			}
		}

		//���Ǳջ�
		if (vertice_points[0] != vertice_points[len - 1])
		{
			if (IsDetectIntersect(ray, vertice_points[len - 1], vertice_points[0]))
			{
				num++;
			}
		}
		int inner = num % 2;
		return inner == 1;
	}
	//����ζ����Ƿ�ɻ���
	static bool IsCanDivide(int index, std::vector<Point>vertice_points)
	{
		int len = vertice_points.size();
		std::vector<Point>triangle_points;
		int next = (index == len - 1) ? 0 : index + 1;
		int pre = (index == 0) ? len - 1 : index - 1;
		triangle_points.push_back(vertice_points[pre]);
		triangle_points.push_back(vertice_points[index]);
		triangle_points.push_back(vertice_points[next]);
		for (int i = 0; i < len; i++)
		{
			if (i != index && i != pre && i != next)
			{
				if (IsPointInsidePolygon(vertice_points[i], triangle_points))
				{
					return false;
				}
			}
		}
		return true;
	}

	 //͹����������ʷ�
	static std::vector<int> ConvexPolygonDivide(std::vector<Point> vertice_points, std::vector<int> indexes) {
	 	int len = vertice_points.size();
	 	if (len > 1 && (vertice_points[0] == vertice_points[len - 1])) {
	 		len--;
	 	}
	 	int triangleNum = len - 2;
	 	std::vector<int>triangles;
	 	for (int i = 0; i < triangleNum; i++)
	 	{
	 		triangles.push_back(indexes[0]);
	 		triangles.push_back(indexes[i + 1]);
	 		triangles.push_back(indexes[i + 2]);
	 	}
	 	return triangles;
	 }
	 //������������ʷ�
	static std::vector<int> PolygonTriangleDivide(std::vector<Point> vertice_points, std::vector<int> indexes)
	 {
	 	int len = vertice_points.size();
	 	if (len <= 3)
	 		return ConvexPolygonDivide(vertice_points, indexes);
	 	int index = 0;
	 	std::vector<int> covex_index;
	 	bool IsCovexPolygon = true;//�ж϶�����Ƿ���͹�����
	 	for (index = 0; index < len; index++)
	 	{
	 		std::vector<geometry::Point> polygon;
	 		polygon = vertice_points;
	 		std::vector <geometry::Point>::iterator iter = polygon.begin() + index;
	 		polygon.erase(iter);
	 		if (IsPointInsidePolygon(vertice_points[index], polygon))
	 		{
	 			IsCovexPolygon = false;
	 			break;
	 		}
	 		else
	 		{
	 			covex_index.push_back(index);
	 		}
	 	}

	 	if (IsCovexPolygon)
	 		return ConvexPolygonDivide(vertice_points, indexes);

	 	//���ҿɻ��ֶ���
	 	int can_divide_index = -1;//�ɻ��ֶ�������
	 	for (int i = 0; i < len; i++)
	 	{
	 		if (i >= index)
	 		{
	 			std::vector<Point> polygon;
	 			polygon = vertice_points;
	 			std::vector <Point>::iterator iter = polygon.begin() + i;
	 			polygon.erase(iter);
	 			if (!IsPointInsidePolygon(vertice_points[i], polygon) && IsCanDivide(i, vertice_points))
	 			{
	 				can_divide_index = i;
	 				break;
	 			}
	 		}
	 		else
	 		{

	 			//            if(covex_index.empty()){
	 			//                can_divide_index = i;
	 			//                break;
	 			//            }
	 			std::vector<int>::iterator result = find(covex_index.begin(), covex_index.end(), i);
	 			if (*result != -1 && IsCanDivide(i, vertice_points))
	 			{
	 				can_divide_index = i;
	 				break;
	 			}
	 		}
	 	}

	 	if (can_divide_index < 0)
	 	{
	 		return {};
	 	}

	 	//�ÿɻ��ֶ��㽫������λ���Ϊһ�������κ�һ�������
	 	std::vector<int> Triangles;
	 	int next = (can_divide_index == len - 1) ? 0 : can_divide_index + 1;
	 	int pre = (can_divide_index == 0) ? len - 1 : can_divide_index - 1;
	 	Triangles.push_back(indexes[pre]);
	 	Triangles.push_back(indexes[can_divide_index]);
	 	Triangles.push_back(indexes[next]);
	 	//�޳��ɻ��ֶ��㼰����
	 	vertice_points.erase(vertice_points.begin() + can_divide_index);
	 	indexes.erase(indexes.begin() + can_divide_index);
	 	//�ݹ黮��
	 	std::vector<int> TempTriangles = PolygonTriangleDivide(vertice_points, indexes);
	 	//	std::cout << vertice_points.size() << std::endl;

	 	Triangles.insert(Triangles.end(), TempTriangles.begin(), TempTriangles.end());
	 	return Triangles;
	 }
		

	//�߶��ཻ  ����ʵ��
	//   A      C
	//     \   /
	//      \ /
	//      / \
	//     D   B
	static bool IsIntersect(Point p1_st, Point p1_end,Point p2_st, Point p2_end) {
		bool intersect = false;
		Vector vec1 = p1_end-p1_st;	//AB
		Vector vec2 = p2_end - p2_st;//CD
		Vector e1 = p2_st-p1_st ;	//AC C-A
		Vector e2 = p1_st - p2_st;  //CA A-C
		Vector e3 = p1_end-p2_st ;// CB	B-C
		Vector e4 = p2_end - p1_st;//AD D-A
		float t1 = e3 * vec2;//CD  CB
		float t2 = e2 * vec2; //CD  CA
		float t3 = e1 * vec1;//AB  AC
		float t4 = e4 * vec1;// AB  AD
		if (((t1 * t2)<0) && ((t3 * t4) <0)) {
			intersect = true;
		}
		return intersect;
	}

	//�����Ƿ�գ��Ƿ��Ǽ򵥶����
	static bool IsPolygonSimple(std::vector<Point>contour_points) {
		bool simple = true;
		for (int i = 0; i < contour_points.size() - 2; i++) {
			for (int j = 2; j < contour_points.size(); j++) {
				if (IsIntersect(contour_points[i], contour_points[i + 1], contour_points[j], contour_points[j + 1])) {
					simple = false;
				}
			}
		}
		return simple;
	}

	//�Ƿ���͹�����
	static bool IsPolygonConvex(std::vector<Point> contour_points) {
		//ʹ�ýǶȺ��жϰ�͹�ԣ�͹����ε��ڽǺ�Ϊ��n-2��*180��
		auto num = contour_points.size();
		float angleSum = 0.0;
		for (int i = 0; i < num; i++)
		{
			Vector e1;
			if (i == 0)
			{
				e1 = contour_points[num - 1] - contour_points[i];
			}
			else
			{
				e1 = contour_points[i - 1] - contour_points[i];
			}
			Vector e2;
			if (i == num - 1)
			{
				e2 = contour_points[0] - contour_points[i];
			}
			else
			{
				e2 = contour_points[i + 1] - contour_points[i];
			}
			//��׼����������
			e1.Normalize();
			e2.Normalize();
			float mdot = e1 * e2;
			//�����Сֵ
			float theta = acos(mdot);
			// float theta = acos(mdot);
				//�Ӻ�
			angleSum += theta;
		}
		//�����ڽǺ�
		float convexAngleSum = (float)(num - 2) * HALF_PI;
		//�жϰ�͹��
		if (angleSum < convexAngleSum - (float)num * 0.00001)
		{
			//�������
			return true;

		}
		//͹����
		return false;
	}

	// //������α�������ߵ�����
	// Vector EvalQuadTangentAt(const Point src[3], float t) {
	// 	// The derivative equation is 2(b - a +(a - 2b +c)t). This returns a
	// 	// zero tangent vector when t is 0 or 1, and the control point is equal
	// 	// to the end point. In this case, use the quad end points to compute the tangent.
	// 	if ((t == 0 && src[0] == src[1]) || (t == 1 && src[1] == src[2])) {
	// 		return src[2] - src[0];
	// 	}
	// 	// SkASSERT(src);
	// 	// SkASSERT(t >= 0 && t <= SK_Scalar1);

	// 	Sk2s P0 = from_point(src[0]);
	// 	Sk2s P1 = from_point(src[1]);
	// 	Sk2s P2 = from_point(src[2]);

	// 	Sk2s B = P1 - P0;
	// 	Sk2s A = P2 - P1 - B;
	// 	Sk2s T = A * Sk2s(t) + B;

	// 	return to_vector(T + T);
	// }

	static bool IsClockwise(const Point& before, const Point& after) {
    	return  Point::Cross(before.X(), before.Y(), after.X(), after.Y());
	}

	//����beizer����
	static float CubicCoordinateCalculation(float t, float p0, float p1, float p2, float p3) {
		float oneMinusT = 1 - t;
		float oneMinusTSquared = oneMinusT * oneMinusT;
		float oneMinusTCubed = oneMinusTSquared * oneMinusT;
		float tSquared = t * t;
		float tCubed = tSquared * t;
		return (oneMinusTCubed * p0) + (3 * oneMinusTSquared * t * p1)
			+ (3 * oneMinusT * tSquared * p2) + (tCubed * p3);
	}

	//����beizer����
	static float QuadraticCoordinateCalculation(float t, float p0, float p1, float p2) {
		float oneMinusT = 1 - t;
		return oneMinusT * ((oneMinusT * p0) + (t * p1)) + t * ((oneMinusT * p1) + (t * p2));

	}

	static Point QuadraticBezierCalculation(float t, const Point* p) {
		float x = QuadraticCoordinateCalculation(t, p[0].X(), p[1].X(), p[2].X());
		float y = QuadraticCoordinateCalculation(t, p[0].Y(), p[1].Y(), p[2].Y());
		return Point(x, y);

	}

	static Point CubicBezierCalculation(float t, const Point* p) {
		float x = CubicCoordinateCalculation(t, p[0].X(), p[1].X(), p[2].X(), p[3].X());
		float y = CubicCoordinateCalculation(t, p[0].Y(), p[1].Y(), p[2].Y(), p[3].Y());
		return Point(x, y);
	}

	//����η��̵ĸ�
	static int SolveQuad(float a, float b, float c, float* t)
	{
		if (fabs(a) < 1e-5f) {
			if (fabs(b) > 1e-5f) {
				t[0] = -c / b;
				return 1;
			}
		}
		else {
			const float desc = b * b - 4.0f * a * c;
			if (fabs(desc) > 1e-5f) {
				const float desc_sqrt = sqrt(desc);
				t[0] = (-b + desc_sqrt) / (2.0f * a);
				t[1] = (-b - desc_sqrt) / (2.0f * a);

				return 2;
			}
		}

		return 0;
	}
	typedef Point(*BezierCalculation)(float t, const Point* points);
}
#endif