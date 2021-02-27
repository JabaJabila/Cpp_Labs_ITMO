#include "geometry.hpp"

Segment::Segment(Point d1, Point d2) : d1(d1), d2(d2) {
	if (d1 == d2)
		throw "Impossible to create a segment with start point mathces end point!!!";
}

double Segment::length() const {
	return sqrt(pow((d1.get_x() - d2.get_x()), 2.0) + pow((d1.get_y() - d2.get_y()), 2.0));
}

std::vector<Point> Segment::get_components() const {
	std::vector<Point> temp;
	temp.push_back(d1);
	temp.push_back(d2);
	return temp; 
}


Polyline::Polyline(std::vector<Point> & ps) : points(ps) {
	if (points.size() >= 2)
		delete_repeated();
	if (points.size() < 2)
		throw "Impossible to create a polyline with less than 2 points";
}

Polyline::Polyline(Point * ps, size_t size) {
	if (size >= 2) {
		for (size_t i = 0; i < size; i++)
			points.push_back(ps[i]);
		delete_repeated();
	}
	if (size < 2 || points.size() < 2)
		throw "Impossible to create a polyline with less than 2 points";
}

double Polyline::length() const {
	double length = 0;
	Point prev = points[0];
	for (size_t i = 1; i < points.size(); i++) {
		length += Segment(prev, points[i]).length();
		prev = points[i];
	}
	return length;
}

void Polyline::delete_repeated() {
	Point prev = points[0];
	for (size_t i = 1; i < points.size(); i++) {
		if (prev == points[i])  {
			points.erase(points.begin() + i);
			i--;
		}
		else
			prev = points[i];
	}
}


ClosedPolyline::ClosedPolyline(std::vector<Point> & ps) : Polyline(ps) {
	check_closed();
	if (points.size() < 3)
		throw "Impossible to create a closed polyline with less than 3 points";
}

ClosedPolyline::ClosedPolyline(Point * ps, size_t size) : Polyline(ps, size) {
	check_closed();
	if (points.size() < 3)
		throw "Impossible to create a closed polyline with less than 3 points";
}

double ClosedPolyline::length() const {
	double length = Polyline::length();
	length += Segment(points[0], points[points.size() - 1]).length();
	return length;
}

void ClosedPolyline::check_closed() {
	if (points[points.size() - 1] == points[0])
		points.erase(points.end() - 1);
}


Polygon::Polygon(const std::vector<Point> & ps) : points(ps) {
	delete_repeated();
	if (points.size() < 3)
		throw "Impossible to create a polygon with less than 3 points";
	if (points.size() >= 4)
		if (!check_convexity())
			throw "Polygon isn't convex!!!";
}

Polygon::Polygon(Point * ps, size_t size) {
	if (size >= 3) {
		for (size_t i = 0; i < size; i++)
			points.push_back(ps[i]);
		delete_repeated();
	}
	if (size < 3 || points.size() < 3)
		throw "Impossible to create a polygon with less than 3 points";
	if (points.size() >= 4)
		if (!check_convexity())
			throw "Polygon isn't convex!!!";
}

double Polygon::perimeter() const {
	double length = 0;
	Point prev = points[0];
	for (size_t i = 1; i < points.size(); i++) {
		length += Segment(prev, points[i]).length();
		prev = points[i];
	}
	length += Segment(points[0], points[points.size() - 1]).length();
	return length;
}

double Polygon::area() const {
	double area = 0;
	Point prev = points[0];
	for (size_t i = 1; i < points.size(); i++) {
		area += prev.get_x() * points[i].get_y() - prev.get_y() * points[i].get_x();
		prev = points[i];
	}
	area += (points[points.size() - 1].get_x() * points[0].get_y() - 
		     points[points.size() - 1].get_y() * points[0].get_x());
	return fabs(area / 2);
}

bool Polygon::check_sign(Point & prev, Point & curr, Point & next, bool positive) {
	Point ABvector(curr.get_x() - prev.get_x(), curr.get_y() - prev.get_y());
	Point BCvector(next.get_x() - curr.get_x(), next.get_y() - curr.get_y()); 
	return ((positive && (ABvector.get_x() * BCvector.get_y() - ABvector.get_y() * BCvector.get_x() > 0)) || 
	   	   ((!positive) && (ABvector.get_x() * BCvector.get_y() - ABvector.get_y() * BCvector.get_x() < 0)));
}

bool Polygon::check_convexity() {
	Point prev = points[0];
	Point next = points[2];
	Point ABvector(points[1].get_x() - prev.get_x(), points[1].get_y() - prev.get_y());
	Point BCvector(next.get_x() - points[1].get_x(), next.get_y() - points[1].get_y());
	bool positive = ((ABvector.get_x() * BCvector.get_y() - ABvector.get_y() * BCvector.get_x()) > 0);

	for (size_t i = 2; i < points.size() - 1; i++) {
		if (!check_sign(points[i - 1], points[i], points[i + 1], positive))
			return false;
	}
	if ((!check_sign(points[points.size() - 2], points[points.size() - 1], points[0], positive)) ||
		(!check_sign(points[points.size() - 1], points[0], points[1], positive)))
			return false;

	return true;
}

void Polygon::delete_repeated() {
	Point prev = points[0];
	for (size_t i = 1; i < points.size(); i++) {
		if (prev == points[i])  {
			points.erase(points.begin() + i);
			i--;
		}
		else
			prev = points[i];
	}
	if (points[points.size() - 1] == points[0])
		points.erase(points.end() - 1);
}


Triangle::Triangle(std::vector<Point> & ps) : Polygon(ps) {
	if (points.size() != 3)
		throw "It's not a triangle!!!";
}

Triangle::Triangle(Point * ps, size_t size) : Polygon(ps, size) {
	if (points.size() != 3)
		throw "It's not a triangle!!!";
}

double Triangle::area() const {
	double semiper = perimeter() / 2;
	double a = Segment(points[0], points[1]).length();
	double b = Segment(points[1], points[2]).length();
	double c = Segment(points[2], points[0]).length();
	return sqrt(semiper * (semiper - a) * (semiper - b) * (semiper - c));	
}


Trapezoid::Trapezoid(std::vector<Point> & ps) : Polygon(ps) {
	if (points.size() != 4 || !check_parallel())
	throw "It's not a trapezoid!!!";
}

Trapezoid::Trapezoid(Point * ps, size_t size) : Polygon(ps, size) {
	if (points.size() != 4 || !check_parallel())
		throw "It's not a trapezoid!!!";
}

bool Trapezoid::check_parallel() {
	Point ABvector(points[1].get_x() - points[0].get_x(), points[1].get_y() - points[0].get_y());
	Point BCvector(points[2].get_x() - points[1].get_x(), points[2].get_y() - points[1].get_y());
	Point CDvector(points[3].get_x() - points[2].get_x(), points[3].get_y() - points[2].get_y());
	Point DAvector(points[0].get_x() - points[3].get_x(), points[0].get_y() - points[3].get_y());

	double v_mult1 = ABvector.get_x() * CDvector.get_y() - ABvector.get_y() * CDvector.get_x();
	double v_mult2 = BCvector.get_x() * DAvector.get_y() - BCvector.get_y() * DAvector.get_x();

	if ((v_mult1 == 0 || v_mult2 == 0) && !(v_mult1 == 0 && v_mult2 == 0))
		return true;
	return false;
}


RegularPolygon::RegularPolygon(std::vector<Point> & ps) : Polygon(ps) {
	if (!check_regularity())
		throw "It's not a regular polygon!!!";
}

RegularPolygon::RegularPolygon(Point * ps, size_t size) : Polygon(ps, size) {
	if (!check_regularity())
		throw "It's not a regular polygon!!!";
}

double RegularPolygon::area() const {
	double r = segmentlen / (2 * sin(PI / count)) * cos(PI / count);
	double per = perimeter();
	return 0.5 * per * r;
}

std::vector<Point> RegularPolygon::build_rpoly(Point & center, unsigned n, double side) {
	std::vector<Point> temp;
	double r = side / (2 * sin(PI / n));
	for (size_t i = 1; i <= n; i++)
		temp.push_back(Point((center.get_x() + r * cos(2 * PI * i / n)), 
					  (center.get_y() + r * sin(2 * PI * i / n))));
	return temp;
}

bool RegularPolygon::check_regularity() {
	count = points.size();
	angle = ((double)(count - 2) / count) * 180;
	Point prev = points[1];
	segmentlen = Segment(points[0], prev).length();
	double alpha, beta;
	for (size_t i = 2; i < count; i++) {
		if (fabs(Segment(prev, points[i]).length() - segmentlen) >= 0.001)
			return false;

		Point BAvector(points[i].get_x() - prev.get_x(), points[i].get_y() - prev.get_y());
		Point BCvector(points[i - 2].get_x() - prev.get_x(), points[i - 2].get_y() - prev.get_y());

		alpha = (BAvector.get_x() * BCvector.get_x() + BAvector.get_y() * BCvector.get_y()) / (segmentlen * segmentlen);

		if (fabs((acos(alpha) * 180 / PI) - angle) >= 0.001)
			return false;

		prev = points[i];
	}

	if (fabs(Segment(prev, points[0]).length() - segmentlen) >= 0.001)
			return false;

	Point BAvector(points[0].get_x() - prev.get_x(), points[0].get_y() - prev.get_y());
	Point BCvector(points[points.size() - 2].get_x() - prev.get_x(), points[points.size() - 2].get_y() - prev.get_y());

	alpha = (BAvector.get_x() * BCvector.get_x() + BAvector.get_y() * BCvector.get_y()) / (segmentlen * segmentlen);

	BAvector = Point(points[1].get_x() - points[0].get_x(), points[1].get_y() - points[0].get_y());
	BCvector = Point(points[count - 1].get_x() - points[0].get_x(), points[count - 1].get_y() - points[0].get_y());

	beta = (BAvector.get_x() * BCvector.get_x() + BAvector.get_y() * BCvector.get_y()) / (segmentlen * segmentlen);

	if (fabs((acos(alpha) * 180 / PI) - angle) >= 0.001 || fabs((acos(beta) * 180 / PI) - angle) >= 0.001)
			return false;
	return true;
}