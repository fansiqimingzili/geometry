#include "path.h"
namespace geometry {
	Path::Path(const char* d_str) {
		if (d_str)
			MakeFromString(d_str);
	}

	Path::Path() {

	}

	Path& Path::MakeFromString(const char* d_str) {

		const char* s = d_str;
		char cmd = '\0';						//d的首字符
		std::vector<float> arg;					//每个命令的数据
		int cnum = 0;							//当前的verb点数量
		char item[512];							//解析数据；
		geometry::Point c(0, 0);
		geometry::Point lastc(0, 0);
		if (s) {
			while (*s) {
				s = parse::Parse::GetNextPathItem(s, item);
				if (!*item) break;
				if (cmd != '\0' && parse::Parse::IsCoordinate(item)) {

					arg.push_back((float)atof(item));

				}
				else {

					if (!FromSVGString(cmd, arg, cnum,c,lastc))
						return;
					cmd = item[0];
					arg.clear();
					cnum = GetNumPerElement(cmd);
					if (cnum == -1) {
						cmd = '\0';
						cnum = 0;
					}
				}
			}
			if (!FromSVGString(cmd, arg, cnum, c, lastc))
				return;
		}
		return *this;
	}

	Path& Path::MakeRect(float x,float y,float width,float height,float rx,float ry) {
		ResetPath();
		if (rx < 0.00001f || ry < 0.0001f) {
			MoveTo(x, y);
			LineTo(x + width, y);
			LineTo(x + width, y + height);
			LineTo(x, y + height);
		}
		else {
			// Rounded rectangle
			MoveTo(x + rx, y);
			LineTo(x + height - rx, y);
			CubicBeizerTo(x + width - rx * (1 - KAPPA90), y, x + width, y + ry * (1 - KAPPA90), x + width, y + ry);
			LineTo(x + width, y + height - ry);
			CubicBeizerTo( x + width, y + height - ry * (1 - KAPPA90), x + width - rx * (1 - KAPPA90), y + height, x + width - rx, y + height);
			LineTo(x + rx, y + height);
			CubicBeizerTo(x + rx * (1 - KAPPA90), y + height, x, y + height - ry * (1 - KAPPA90), x, y + height - ry);
			LineTo(x, y + ry);
			CubicBeizerTo(x, y + ry * (1 - KAPPA90), x + rx * (1 - KAPPA90), y, x + rx, y);
		}
		return *this;
	}

	Path& Path::MakeEllipse(float cx, float cy, float ra, float rb) {
		ResetPath();
		MoveTo(cx + ra, cy);
		CubicBeizerTo(cx + ra, cy + rb * KAPPA90, cx + ra * KAPPA90, cy + rb, cx, cy + rb);
		CubicBeizerTo(cx - ra * KAPPA90, cy + rb, cx - ra, cy + rb * KAPPA90, cx - ra, cy);
		CubicBeizerTo(cx - ra, cy - rb * KAPPA90, cx - ra * KAPPA90, cy - rb, cx, cy - rb);
		CubicBeizerTo(cx + ra * KAPPA90, cy - rb, cx + ra, cy - rb * KAPPA90, cx + ra, cy);
		return *this;
	}

	Path& Path::MakeCircle(float center_x, float center_y, float radius) {
		ResetPath();
		MoveTo(center_x + radius, center_y);
		CubicBeizerTo(center_x + radius, center_y + radius * KAPPA90, center_x + radius * KAPPA90, center_y + radius, center_x, center_y + radius);
		CubicBeizerTo(center_x - radius * KAPPA90, center_y + radius, center_x - radius, center_y + radius * KAPPA90, center_x - radius, center_y);
		CubicBeizerTo(center_x - radius, center_y - radius * KAPPA90, center_x - radius * KAPPA90, center_y - radius, center_x, center_y - radius);
		CubicBeizerTo(center_x + radius * KAPPA90, center_y - radius, center_x + radius, center_y - radius * KAPPA90, center_x + radius, center_y);
		return *this;
	}

	Path& Path::MakeLine(const Point& a, const Point& b) {
		ResetPath();
		MoveTo(a.X(),a.Y());
		LineTo(b.X(), b.Y());
		return *this;
	}

	std::vector<Point> Path::Approximate(float acceptable_error) {
		Point points[4];
		std::vector<Point> segment_points;
		float error_squared = acceptable_error * acceptable_error;
		auto iter = verbs_.cbegin();
		auto data_iter = data_.cbegin();
		points[0] = *data_iter;
		for (; iter != verbs_.cend(); iter++) {
			int cnum = GetNumPerElement(*iter);
			for (int i = 0; i <=cnum; i++) {
				if (*iter == PathVerb::kMove)
					break;
				points[i] = *data_iter++;
			}
			if (*iter == PathVerb::kMove) {
				points[0] = *data_iter;
				continue;
			}
			data_iter--;
			CreateVerbSegments(*iter,points, segment_points, error_squared);
		}
		if (segment_points.empty()) {
			int numVerbs = this->GetVerbCounts();
			if (numVerbs == 1) {
				AddMove(segment_points, this->GetPoint(0));
			}
			else {
				// Invalid or empty path. Fall back to point(0,0)
				AddMove(segment_points, Point(0, 0));
			}
		}
		return segment_points;
	}

	Rect Path::ComputeBounds() const {
		Rect bounds;
		if (!GetVerbCounts()) {
			return  bounds.CreateRectFromLTRB(0, 0, 0, 0);
		}
		if (verbs_[0] == PathVerb::kMove)
			bounds.SetLTRB(data_[0].X(), data_[0].Y(), data_[0].X(), data_[0].Y());

		geometry::Point lastc(data_[0].X(), data_[0].Y());
		int data_index = 1;
		for (int index = 1; index < GetVerbCounts();index++) {
			switch (verbs_[index]) {
			case PathVerb::kMove:
			case PathVerb::kLine:
				bounds.ExpandBounds(data_[data_index]);
				lastc = data_[data_index];
				data_index = data_index + 1;
				break;
			case PathVerb::kCubic:
			{
				// Bezier end point
				bounds.ExpandBounds(data_[data_index + 2]);
				// Extremities
				Point point[4];
				point[0] = lastc;
				point[1] = data_[data_index];
				point[2] = data_[data_index + 1];
				point[3] = data_[data_index + 2];

				const float a = 3.0f * (-point[0].X() + 3.0f * (point[1].X() - point[2].X()) + point[3].X());
				const float b = 6.0f * (point[0].X() - 2.0f * point[1].X() + point[2].X());
				const float c = 3.0f * (point[1].X() - point[0].X());

				const float d = 3.0f * (-point[0].Y() + 3.0f * (point[1].Y() - point[2].Y()) + point[3].Y());
				const float e = 6.0f * (point[0].Y() - 2.0f * point[1].Y() + point[2].Y());
				const float f = 3.0f * (point[1].Y() - point[0].Y());

				float rootx[2] = { -1.0f, -1.0f }; // Max 2 roots
				int numrootsx = SolveQuad(a, b, c, &rootx[0]);
				float rooty[2] = { -1.0f, -1.0f }; // Max 2 roots
				int numrootsy =SolveQuad(d, e, f, &rooty[0]);
				for (int iroot = 0; iroot < numrootsx; iroot++) {
					const float t = rootx[iroot];
					if (t > 1e-5f && t < (1.0f - 1e-5f)) {
						Point pos = CubicBezierCalculation(t, point);
						bounds.ExpandBounds(pos);
					}
				}
				for (int iroot = 0; iroot < numrootsy; iroot++) {
					const float t = rooty[iroot];
					if (t > 1e-5f && t < (1.0f - 1e-5f)) {
						Point pos = CubicBezierCalculation(t, point);
						bounds.ExpandBounds(pos);
					}
				}

				lastc = data_[data_index + 2];
				data_index = data_index + 3;
			}
			break;
			case PathVerb::kQuad:
			{
				// Bezier end point
				bounds.ExpandBounds(data_[data_index + 1]);
				// Extremities
				Point point[4];
				point[0] = lastc;
				point[1] = data_[data_index];
				point[2] = data_[data_index + 1];

				const float a = point[2].X() - point[1].X();
				const float b = point[1].X() - point[0].X();
				const float c = point[2].Y() - point[1].Y();
				const float d = point[1].Y() - point[0].Y();
				// dBezier(2,t)/dt = 2 * (a * t + b)
				const float t1 = -b / a;
				const float t2 = -d / c;
				const float t[2] = { t1,t2 };
				for (int i = 0; i < 2; i++)
					if (fabs(a) > 1e-5f) {
						if (t[i] > 1e-5f && t[i] < (1.0f - 1e-5f)) {
							Point pos = QuadraticBezierCalculation(t[i], point);
							bounds.ExpandBounds(pos);
						}
					}
				lastc = data_[data_index + 1];
				break;
			}
			case PathVerb::kClose:
				// Noop
				break;
			default:
				break;
			}
		}
		return bounds;
	}

	void Path::Set(const Path& path) {
		verbs_ = path.verbs_;
		data_ = path.data_;
	}

	void Path::MoveTo(Point& pt) {
		this->MoveTo(pt.X(), pt.Y());
	}

	void Path::MoveTo(float x, float y) {
		Point pt(x, y);
		verbs_.push_back(PathVerb::kMove);
		data_.push_back(pt);
	}

	void Path::LineTo(Point& pt) {
		this->LineTo(pt.X(), pt.Y());
	}

	void Path::LineTo(float x, float y) {
		Point pt(x, y);
		verbs_.push_back(PathVerb::kLine);
		data_.push_back(pt);
	}

	void Path::CubicBeizerTo(Point& cp1, Point& cp2, Point& pt) {
		this->CubicBeizerTo(cp1.X(), cp1.Y(), cp2.X(), cp2.Y(), pt.X(), pt.Y());
	}
	void Path::CubicBeizerTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y) {
		Point cp1(cp1x, cp1y), cp2(cp2x, cp2y), p(x, y);
		verbs_.push_back(PathVerb::kCubic);
		data_.push_back(cp1);
		data_.push_back(cp2);
		data_.push_back(p);
	}

	void Path::QuadBeizierTo(Point& cp, Point& pt) {
		this->QuadBeizierTo(cp.X(), cp.Y(), pt.X(), pt.Y());
	}

	void Path::QuadBeizierTo(float cpx, float cpy, float x, float y) {
		Point cp(cpx, cpy), p(x, y);
		verbs_.push_back(PathVerb::kQuad);
		data_.push_back(cp);
		data_.push_back(p);
	}

	void Path::ArcTo(float radiusx, float radiusy, float rot_x, float large_arc, float sweep_flag, Point& pt) {

		this->ArcTo(radiusx, radiusy, rot_x, large_arc, sweep_flag, pt.X(), pt.Y());

	}
	void Path::ArcTo(float radiusx, float radiusy, float rot_x, float large_arc, float sweep_flag, float endx, float endy) {

		float rx = fabsf(radiusx);				// y radius
		float ry = fabsf(radiusy);				// x radius
		float rotx = rot_x / 180.0f * PI;		// x rotation angle
		int fa = fabsf(large_arc) > 1e-6 ? 1 : 0;	// Large arc
		int fs = fabsf(sweep_flag) > 1e-6 ? 1 : 0;	// Sweep direction
		float x1 = data_.back().X();							// start point
		float y1 = data_.back().Y();
		float x2 = endx;
		float y2 = endy;


		float dx = x1 - x2;
		float dy = y1 - y2;
		float d = sqrtf(dx * dx + dy * dy);
		if (d < 1e-6f || rx < 1e-6f || ry < 1e-6f) {
			// The arc degenerates to a line
			LineTo(x2, y2);
		}

		float sinrx = sinf(rotx);
		float cosrx = cosf(rotx);

		// Convert to center point parameterization.
		// http://www.w3.org/TR/SVG11/implnote.html#ArcImplementationNotes
		// 1) Compute x1', y1'
		float x1p = cosrx * dx / 2.0f + sinrx * dy / 2.0f;
		float y1p = -sinrx * dx / 2.0f + cosrx * dy / 2.0f;
		d = (x1p * x1p) / (rx * rx) + (y1p * y1p) / (ry * ry);
		if (d > 1) {
			d = sqrtf(d);
			rx *= d;
			ry *= d;
		}
		// 2) Compute cx', cy'
		float s = 0.0f;
		float sa = (rx * rx) * (ry * ry) - (rx * rx) * (y1p * y1p) - (ry * ry) * (x1p * x1p);
		float sb = (rx * rx) * (y1p * y1p) + (ry * ry) * (x1p * x1p);
		if (sa < 0.0f) sa = 0.0f;
		if (sb > 0.0f)
			s = sqrtf(sa / sb);
		if (fa == fs)
			s = -s;
		float cxp = s * rx * y1p / ry;
		float cyp = s * -ry * x1p / rx;

		// 3) Compute cx,cy from cx',cy'
		float cx = (x1 + x2) / 2.0f + cosrx * cxp - sinrx * cyp;
		float cy = (y1 + y2) / 2.0f + sinrx * cxp + cosrx * cyp;

		// 4) Calculate theta1, and delta theta.
		float ux = (x1p - cxp) / rx;
		float uy = (y1p - cyp) / ry;
		float vx = (-x1p - cxp) / rx;
		float vy = (-y1p - cyp) / ry;
		float a1 = VecAngle(1.0f, 0.0f, ux, uy);	// Initial angle
		float da = VecAngle(ux, uy, vx, vy);		// Delta angle

	//	if (vecrat(ux,uy,vx,vy) <= -1.0f) da = NSVG_PI;
	//	if (vecrat(ux,uy,vx,vy) >= 1.0f) da = 0;

		if (fs == 0 && da > 0)
			da -= 2 * PI;
		else if (fs == 1 && da < 0)
			da += 2 * PI;

		// Approximate the arc using cubic spline segments.
		float t[6];
		t[0] = cosrx; t[1] = sinrx;
		t[2] = -sinrx; t[3] = cosrx;
		t[4] = cx; t[5] = cy;

		// Split arc into max 90 degree segments.
		// The loop assumes an iteration per end point (including start and end), this +1.
		int ndivs = (int)(fabsf(da) / (PI * 0.5f) + 1.0f);
		float hda = (da / (float)ndivs) / 2.0f;
		float kappa = fabsf(4.0f / 3.0f * (1.0f - cosf(hda)) / sinf(hda));
		if (da < 0.0f)
			kappa = -kappa;

		float px = 0.0f;
		float py = 0.0f;
		float ptanx = 0.0f;
		float ptany = 0.0f;

		for (int i = 0; i <= ndivs; i++) {
			float a = a1 + da * ((float)i / (float)ndivs);
			dx = cosf(a);
			dy = sinf(a);

			const float dxrx = dx * rx;
			const float dyry = dy * ry;
			const float x = dxrx * t[0] + dyry * t[2] + t[4];
			const float y = dxrx * t[1] + dyry * t[3] + t[5];

			const float dyrxkappa = dy * rx * kappa;
			const float dxrykappa = dx * ry * kappa;

			const float tanx = dxrykappa * t[2] - dyrxkappa * t[0];
			const float tany = dxrykappa * t[3] - dyrxkappa * t[1];

			if (i > 0) {
				CubicBeizerTo(px + ptanx, py + ptany, x - tanx, y - tany, x, y);
			}

			px = x;
			py = y;
			ptanx = tanx;
			ptany = tany;
		}
	}

	void Path::CloseTo() {
		verbs_.push_back(PathVerb::kClose);
		data_.push_back(data_[0]);
	}

	bool Path::FromSVGString(char cmd, std::vector<float>& data, int cnum, Point& c, Point& lastc) {
		float a[7] = { 0 };
		int size = data.size();
		bool rel = false;
		if (data.size() ==0&& cmd!='Z'&&cmd!='z') {
			return true;
		}
		if (data.size() < cnum)
		{
			SVG_CHECK(data.size() < cnum, "paras less it need");
			data.clear();
			return false;
		}
		switch (cmd) {
		case 'M':
		case 'm':
			if ((cmd == 'm' ? true : false) && size > 0)
			{
				a[0] = c.X() + data[0];
				a[1] = c.Y() + data[1];
			}
			else
			{
				a[0] = data[0];
				a[1] = data[1];
			}
			if (data.size() == cnum && data.size() > 0)
			{
				MoveTo(a[0], a[1]);
			}
			if (data.size() > cnum && data.size() > 0)
			{
				SVG_CHECK(data.size() < cnum, "paras more than it need");
				MoveTo(a[0], a[1]);
				return false;
			}
			c.Set(a[0], a[1]); lastc = c;
			break;
		case 'L':
		case 'l':
			if ((cmd == 'l' ? true : false) && size > 0)
			{
				a[0] = c.X() + data[0];
				a[1] = c.Y() + data[1];
			}
			else
			{
				a[0] = data[0];
				a[1] = data[1];
			}
			goto LineCommon;
		case 'H':
		case 'h':
			if ((cmd == 'h' ? true : false) && size > 0)
			{
				a[0] = c.X() + data[0];
				a[1] = c.Y();
			}
			else
			{
				a[0] = data[0];
				a[1] = c.Y();
			}
			goto LineCommon;
		case 'V':
		case 'v':
			if ((cmd == 'v' ? true : false) && size > 0)
			{
				a[0] = c.X();
				a[1] = c.Y() + data[0];
			}
			else
			{
				a[0] = c.X();
				a[1] = data[0];
			}
		LineCommon:
			if (data.size() == cnum && data.size() > 0)
			{
				LineTo(a[0], a[1]);
			}
			if (data.size() > cnum && data.size() > 0)
			{
				SVG_CHECK(data.size() < cnum, "paras more than it need");
				LineTo(a[0], a[1]);
				return false;
			}
			c.Set(a[0], a[1]); lastc = c;
			break;
		case 'C':
		case 'c':
			if ((cmd == 'c' ? true : false) && size > 0)
			{
				a[0] = c.X() + data[0];
				a[1] = c.Y() + data[1];
				a[2] = c.X() + data[2];
				a[3] = c.Y() + data[3];
				a[4] = c.X() + data[4];
				a[5] = c.Y() + data[5];
			}
			else
			{
				a[0] = data[0];
				a[1] = data[1];
				a[2] = data[2];
				a[3] = data[3];
				a[4] = data[4];
				a[5] = data[5];
			}
			goto CubicCommon;
		case 'S':
		case 's':
			if ((cmd == 's' ? true : false) && size > 0)
			{
				a[0] = lastc.X();
				a[1] = lastc.Y();
				a[2] = c.X() + data[0];
				a[3] = c.Y() + data[1];
				a[4] = c.X() + data[2];
				a[5] = c.Y() + data[3];
			}
			else
			{
				a[0] = lastc.X();
				a[1] = lastc.Y();
				a[2] = data[0];
				a[3] = data[1];
				a[4] = data[2];
				a[5] = data[3];
			}
		CubicCommon:
			if (data.size() == cnum && data.size() > 0)
			{
				CubicBeizerTo(a[0], a[1], a[2], a[3], a[4], a[5]);
			}
			if (data.size() > cnum && data.size() > 0)
			{
				SVG_CHECK(data.size() < cnum, "paras more than it need");
				CubicBeizerTo(a[0], a[1], a[2], a[3], a[4], a[5]);
				return false;
			}
			lastc.Set(a[2], a[3]); c.Set(a[4], a[5]);
			break;
		case 'Q':
		case 'q':
			if ((cmd == 'q' ? true : false) && size > 0)
			{
				a[0] = c.X() + data[0];
				a[1] = c.Y() + data[1];
				a[2] = c.X() + data[2];
				a[3] = c.Y() + data[3];
			}
			else
			{
				a[0] = data[0];
				a[1] = data[1];
				a[2] = data[2];
				a[3] = data[3];
			}
			goto QuadCommon;
		case 'T':
		case 't':
			if ((cmd == 't' ? true : false) && size > 0)
			{
				a[0] = lastc.X();
				a[1] = lastc.Y();
				a[2] = c.X() + data[0];
				a[3] = c.Y() + data[1];
			}
			else
			{
				a[0] = lastc.X();
				a[1] = lastc.Y();
				a[2] = data[0];
				a[3] = data[1];
			}
		QuadCommon:
			if (data.size() == cnum && data.size() > 0)
			{
				QuadBeizierTo(a[0], a[1], a[2], a[3]);
			}
			if (data.size() > cnum && data.size() > 0)
			{
				SVG_CHECK(data.size() < cnum, "paras more than it need");
				QuadBeizierTo(a[0], a[1], a[2], a[3]);
				return false;
			}
			lastc.Set(a[0], a[1]); c.Set(a[2], a[3]);
			break;
		case 'A':
		case 'a':
			if ((cmd == 'a' ? true : false) && size > 0)
			{
				a[5] = c.X() + data[5];
				a[6] = c.Y() + data[6];
			}
			else
			{
				a[5] = data[5];
				a[6] = data[6];
			}
			if (data.size() == cnum && data.size() > 0)
			{
				ArcTo(data[0], data[1], data[2], data[3], data[4], a[5], a[6]);
			}
			if (data.size() > cnum && data.size() > 0)
			{
				SVG_CHECK(data.size() < cnum, "paras more than it need");
				ArcTo(data[0], data[1], data[2], data[3], data[4], a[5], a[6]);
				return false;
			}
			c.Set(a[5], a[6]); lastc = c;
			break;
		case 'Z':
		case 'z':
			CloseTo();
			c.Set(0, 0);
			break;
		default:
			return false;
		}

	}

	bool Path::SubdividePoints(const Point* points, BezierCalculation bezierfunction,
		float t0, const Point& p0, float t1, const Point& p1, float& mid_t, Point& mid_p, float error_squared) {
		mid_t = (t1 + t0) / 2;
		float mid_x = (p1.X() + p0.X()) / 2;
		float mid_y = (p1.Y() + p0.Y()) / 2;

		mid_p = (*bezierfunction)(mid_t, points);
		float error_x = mid_p.X() - mid_x;
		float error_y = mid_p.Y() - mid_y;
		float mid_error_squared = (error_x * error_x) + (error_y * error_y);
		return mid_error_squared > error_squared;
	}

	void Path::AddMove(std::vector<Point>& segment_points, const Point& p) {
		segment_points.push_back(p);
	}

	void Path::AddLine(std::vector<Point>& segment_points, const Point& p) {
		if (segment_points.empty()) {
			segment_points.push_back(Point(0, 0));
			//AddMove(segment_points, p);
			//return;
		}
		else if (segment_points.back() == p) {
			return; // Empty line
		}
		segment_points.push_back(p);
	}

	void Path::AddBezier(const Point* points, BezierCalculation bezierFunction, std::vector<Point>& segment_points,
		float error_squared, bool double_check_division) {
		typedef std::map<float,Point> PointMap;
		PointMap T_ToPoint;

		T_ToPoint[0] = (*bezierFunction)(0, points);
		T_ToPoint[1] = (*bezierFunction)(1, points);

		PointMap::iterator iter = T_ToPoint.begin();
		PointMap::iterator next = iter;
		++next;
		while (next != T_ToPoint.end()) {
			bool need_subdivision = true;
			Point mid_point;
			do {
				float mid_t;
				need_subdivision = SubdividePoints(points, bezierFunction, iter->first,
					iter->second, next->first, next->second, mid_t, mid_point, error_squared);
				if (!need_subdivision && double_check_division) {
					Point quarter_point;
					float quarter_t;
					need_subdivision = SubdividePoints(points, bezierFunction, iter->first,
						iter->second, mid_t, mid_point, quarter_t, quarter_point, error_squared);
					if (need_subdivision) {
						// Found an inflection point. No need to double-check.
						double_check_division = false;

					}

				}
				if (need_subdivision) {
					next = T_ToPoint.insert(iter, PointMap::value_type(mid_t, mid_point));
				}

			} while (need_subdivision);
			iter = next;
			next++;

		}
		// Now that each division can use linear interpolation with less than the allowed error
		for (iter = T_ToPoint.begin(); iter != T_ToPoint.end(); ++iter) {
		   AddLine(segment_points,iter->second);
		}
	}

	void Path::CreateVerbSegments(PathVerb verb, const Point points[], std::vector<Point>& segment_points, float errorSquared) {
		switch (verb) {
		case PathVerb::kMove:
			AddMove(segment_points,points[0]);
			break;
		case PathVerb::kClose:
			AddLine(segment_points,points[1]);
			break;
		case PathVerb::kLine:
			AddLine(segment_points,points[1]);
			break;
		case PathVerb::kQuad:
			AddBezier(points, QuadraticBezierCalculation, segment_points,errorSquared, false);
			break;
		case PathVerb::kCubic:
			AddBezier(points, CubicBezierCalculation, segment_points,errorSquared, true);
			break;
		default:
			break;

		}
	}

	int Path::GetNumPerElement(char cmd)
	{
		switch (cmd) {
		case 'v':
		case 'V':
		case 'h':
		case 'H':
			return 1;
		case 'm':
		case 'M':
		case 'l':
		case 'L':
		case 't':
		case 'T':
			return 2;
		case 'q':
		case 'Q':
		case 's':
		case 'S':
			return 4;
		case 'c':
		case 'C':
			return 6;
		case 'a':
		case 'A':
			return 7;
		case 'z':
		case 'Z':
			return 0;
		}
		return -1;
	}

	int Path::GetNumPerElement(PathVerb verb) {
		switch (verb) {
		case PathVerb::kMove:
		case PathVerb::kLine:
		case PathVerb::kClose:
			return 1;
		case PathVerb::kQuad:
			return 2;
		case PathVerb::kCubic:
			return 3;
		}
		return -1;
	}

}