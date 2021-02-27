#pragma once
#include <vector>
#include <cmath>

#define PI 3.14159265

class Point {

public:
	explicit Point(double x = 0, double y = 0) : x(x),  y(y) {}
	Point(Point const & other) = default;
	Point & operator=(Point const & other) = default;
	~Point() = default;

	double get_x() const {return x;}
	double get_y() const {return y;}
	bool operator==(Point const & right) const {return (x == right.x && y == right.y);}

private:
	double x;
	double y;
};


class Line {

public:
	virtual double length() const = 0;
	virtual std::vector<Point> get_components() const = 0;
	virtual ~Line() {} 
};


class Segment : public Line {

public:
	explicit Segment(Point d1 = Point(), Point d2 = Point(1, 1));
	Segment(Segment const & other) = default;
	Segment & operator=(Segment const & other) = default;
	~Segment() = default;

	double length() const;
	std::vector<Point> get_components() const;
	Point start() const {return d1;}
	Point end() const {return d2;}

private:
	Point d1;
	Point d2;
};


class Polyline : public Line {

public:
	Polyline() = delete;
	explicit Polyline(std::vector<Point> & ps);
	Polyline(Point * ps, size_t size);
	Polyline(Polyline const & other) = default;
	Polyline & operator=(Polyline const & other) = default;
	~Polyline() = default;

	double length() const;
	std::vector<Point> get_components() const {return points;}

private:
	void delete_repeated();

protected:
	std::vector<Point> points;
};


class ClosedPolyline : public Polyline {

public:
	ClosedPolyline() = delete;
	explicit ClosedPolyline(std::vector<Point> & ps);
	ClosedPolyline(Point * ps, size_t size);
	ClosedPolyline(ClosedPolyline const & other) = default;
	ClosedPolyline & operator=(ClosedPolyline const & other) = default;
	~ClosedPolyline() = default;

	double length() const;
	std::vector<Point> get_components() const {return points;}

private:
	void check_closed();
};


class Shape {

public:
	virtual double perimeter() const = 0;
	virtual double area() const = 0;
	virtual std::vector<Point> get_components() const = 0;
	virtual ~Shape() {}
};


class Polygon : public Shape {

public:
	Polygon() = delete;
	explicit Polygon(const std::vector<Point> & ps);
	Polygon(Point * ps, size_t size);
	Polygon(Polygon const & other) = default;
	Polygon & operator=(Polygon const & other) = default;
	~Polygon() = default;

	std::vector<Point> get_components() const {return points;};
	double perimeter() const;
	double area() const;

private:
	bool check_sign(Point & prev, Point & curr, Point & next, bool positive);
	bool check_convexity();

protected:
	std::vector<Point> points;

	void delete_repeated();
};


class Triangle : public Polygon {

public:
	Triangle() = delete;
	explicit Triangle(std::vector<Point> & ps);
	Triangle(Point * ps, size_t size);
	Triangle(Triangle const & other) = default;
	Triangle & operator=(Triangle const & other) = default;
	~Triangle() = default;

	std::vector<Point> get_components() const {return points;};
	double perimeter() const {return Polygon::perimeter();};
	double area() const;
};


class Trapezoid : public Polygon {

public:
	Trapezoid() = delete;
	explicit Trapezoid(std::vector<Point> & ps);
	Trapezoid(Point * ps, size_t size);
	Trapezoid(Trapezoid const & other) = default;
	Trapezoid & operator=(Trapezoid const & other) = default;
	~Trapezoid() = default;

	std::vector<Point> get_components() const {return points;};
	double perimeter() const {return Polygon::perimeter();};
	double area() const {return Polygon::area();}

private:
	bool check_parallel();
};


class RegularPolygon : public Polygon {

public:
	RegularPolygon() = delete;
	explicit RegularPolygon(std::vector<Point> & ps);
	RegularPolygon(Point * ps, size_t size);
	explicit RegularPolygon(Point center, unsigned n_sides = 3, double size_len = 1) 
		: count(n_sides)
		, angle((((double)(n_sides - 2)) / n_sides) * 180)
		, segmentlen(fabs(size_len))
		, Polygon(build_rpoly(center, n_sides, size_len)) {}
	RegularPolygon(RegularPolygon const & other) = default;
	RegularPolygon & operator=(RegularPolygon const & other) = default;
	~RegularPolygon() = default;

	std::vector<Point> get_components() const {return points;};
	double get_angle() const {return angle;}
	double get_segmentlen() const {return segmentlen;}
	double perimeter() const {return segmentlen * count;};
	double area() const {return Polygon::area();}

private:
	static std::vector<Point> build_rpoly(Point & center, unsigned n, double side);
	bool check_regularity();

	double segmentlen;
	double angle;
	unsigned count;
};