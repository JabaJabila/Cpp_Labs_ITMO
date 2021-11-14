#include <iostream>
#include "geometry.hpp"

int main() {

	Point A{};
	Point B(1, 1);
	Point C(-1.5, 2);
	Point D(3);
	Point E = A;

	std::cout << "\n---------------- TEST #1 ----------------\n\n";
	std::cout << "Coordinates of point A: (" << A.get_x() << ", " << A.get_y() << ")\n";
	std::cout << "Coordinates of point B: (" << B.get_x() << ", " << B.get_y() << ")\n";
	std::cout << "Coordinates of point C: (" << C.get_x() << ", " << C.get_y() << ")\n";
	std::cout << "Coordinates of point D: (" << D.get_x() << ", " << D.get_y() << ")\n";
	std::cout << "Coordinates of point E: (" << E.get_x() << ", " << E.get_y() << ")\n";
	E == A ? std::cout << "Point E equals point A\n" : std::cout << "Point E not equals point A\n";
	A != B ? std::cout << "Point A not equals point B\n" : std::cout << "Point A equals point B\n";

	Segment s1(A, B);
	Segment s2(C, D);

	try {
		std::cout << "\n\n---------------- TEST #2 ----------------\n\n";		
		std::cout << "Coordinates of start of segment AB: (" << s1.start().get_x() << ", " << s1.start().get_y() << ")\n";
		std::cout << "Coordinates of end of segment AB: (" << s1.end().get_x() << ", " << s1.end().get_y() << ")\n";
		std::cout << "Length of segment AB = " << s1.length() << "\n";
		std::cout << "\nCoordinates of start of segment CD: (" << s2.start().get_x() << ", " << s2.start().get_y() << ")\n";
		std::cout << "Coordinates of end of segment CD: (" << s2.end().get_x() << ", " << s2.end().get_y() << ")\n";
		std::cout << "Length of segment CD = " << s2.length() << "\n";
		std::cout << "\nAttempt to crate a segment AA:\n";

		Segment s0(A, A);
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}


	std::vector<Point> points1;
	points1.push_back(Point());
	points1.push_back(Point(1, 1));
	points1.push_back(Point(2, 1));
	points1.push_back(Point(2, 0));
	points1.push_back(Point(2, 0));
	points1.push_back(Point(1, -1));

	std::vector<Point> points2;
	points2.push_back(Point());
	points2.push_back(Point());
	points2.push_back(Point(2, 0));
	points2.push_back(Point(2, 0));

	Polyline pl0(points1);
	Polyline pl1(points2);
	pl1 = pl0;

	Polyline pl2(points2);

	Point * points3 = new Point[4];
	points3[0] = Point(1, 1);
	points3[1] = Point(2, 0);
	points3[2] = Point();
	points3[3] = Point(0, -1);

	ClosedPolyline cl1(points3, 4);

	Point * points4 = new Point[5];
	points4[0] = Point();
	points4[1] = Point(2, 0);
	points4[2] = Point(0, -2);
	points4[3] = Point(0, -2);
	points4[4] = Point();

	ClosedPolyline cl0(points4, 5);
	ClosedPolyline cl2 = cl0;

	try {
		std::cout << "\n\n---------------- TEST #3 ----------------\n\n";		
		std::cout << "Count of points of polyline #1: " << pl1.get_components().size() << "\n";
		std::cout << "Length of polyline #1 = " << pl1.length() << "\n";
		std::cout << "\nCount of points of polyline #2: " << pl2.get_components().size() << "\n";
		std::cout << "Length of polyline #2 = " << pl2.length() << "\n";
		std::cout << "\nCount of points of closed polyline #1: " << cl1.get_components().size() << "\n";
		std::cout << "Length of closed polyline #1 = " << cl1.length() << "\n";
		std::cout << "\nCount of points of closed polyline #2: " << cl2.get_components().size() << "\n";
		std::cout << "Length of closed polyline #2 = " << cl2.length() << "\n";
		std::cout << "\nAttempt to create a closed polyline with 2 points:\n";

		ClosedPolyline cl3(points2);
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	std::cout << "\n\n---------------- TEST #4 ----------------\n";
	std::cout << "<Dynamic polymorphism of Line abstract class>\n\n";	
	Line * lines[] = {&s1, &s2, &pl0, &cl1, &cl2};

		for (size_t i = 0; i < 5; i++) {
			std::cout << "Line #" << i + 1 << ": ";
			std::cout << "count of points - " << lines[i]->get_components().size() << ", ";
			std::cout << "length = " << lines[i]->length() << '\n';
		}  

	std::vector<Point> points5;
	points5.push_back(Point(1, 1));
	points5.push_back(Point(1, -1));
	points5.push_back(Point(-1, -1));
	points5.push_back(Point(-1, 1));

	Point * points6 = new Point[3];
	points6[0] = Point();
	points6[1] = Point(0, 2);
	points6[2] = Point(2, 0);

	std::vector<Point> points7;
	points7.push_back(Point(1, 1));
	points7.push_back(Point(2, 3));
	points7.push_back(Point(5, 4));
	points7.push_back(Point(6, 1));

	std::vector<Point> points8;
	points8.push_back(Point(-1));
	points8.push_back(Point(-5, 2));
	points8.push_back(Point(-3, 4));
	points8.push_back(Point(-1, 3));

	std::vector<Point> points9;
	points9.push_back(Point(1, 1));
	points9.push_back(Point(3, -1));
	points9.push_back(Point(0, -1));
	points9.push_back(Point(-1, 1));

	std::vector<Point> points10;
	points10.push_back(Point(2.5, 4.330127));
	points10.push_back(Point(-2.5, 4.330127));
	points10.push_back(Point(-5.0, 6.123233995736766e-16));
	points10.push_back(Point(-2.5, -4.330127));
	points10.push_back(Point(2.5, -4.330127));
	points10.push_back(Point(5.0, -1.2246467991473533e-15));

	Polygon pg1(points5);

	try {
		std::cout << "\n\n---------------- TEST #5 ----------------\n\n";		
		std::cout << "Count of points of polygon: " << pg1.get_components().size() << "\n";
		std::cout << "Perimeter = " << pg1.perimeter() << ", area = " << pg1.area() << "\n";
		
		points5.push_back(Point(0, 0.5));
		std::cout << "\nAttempt to create not convex polygon:\n";
		Polygon pg2(points5);
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	Triangle tri1(points6, 3);
	points5.pop_back();

	try {
		std::cout << "\n\n---------------- TEST #6 ----------------\n\n";		
		std::cout << "Count of points of triangle: " << tri1.get_components().size() << "\n";
		std::cout << "Perimeter = " << tri1.perimeter() << ", area = " << tri1.area() << "\n";
		std::cout << "\nAttempt to create a triangle with 4 points:\n";
		Triangle tri2(points5);
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	Trapezoid trp1(points8);
	Trapezoid trp2(points9);

	try {
		std::cout << "\n\n---------------- TEST #7 ----------------\n\n";		
		std::cout << "Count of points of trapezoid #1: " << trp1.get_components().size() << "\n";
		std::cout << "Perimeter = " << trp1.perimeter() << ", area = " << trp1.area() << "\n";

		std::cout << "\nCount of points of trapezoid #2: " << trp2.get_components().size() << "\n";
		std::cout << "Perimeter = " << trp2.perimeter() << ", area = " << trp2.area() << "\n";

		std::cout << "\nAttempt to create a trapezoid without parallel sides:\n";
		Trapezoid trp3(points7);

	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	RegularPolygon rp1(points10);

	try {
		std::cout << "\n\n---------------- TEST #8 ----------------\n\n";		
		std::cout << "Count of points of regular polygon: " << rp1.get_components().size() << "\n";
		std::cout << "Side length = " << rp1.get_segmentlen() << ", angle between sides = " << rp1.get_angle() << " degrees\n";
		std::cout << "Perimeter = " << rp1.perimeter() << ", area = " << rp1.area() <<"\n";
		std::cout << "\nAttempt to create not regular polygon:\n";
		RegularPolygon rp3(points7);

	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}



	std::cout << "\n\n---------------- TEST #9 ----------------\n";
	std::cout << "<Creating regular ectagon with center in point (3, -4) and with size length 5>\n\n";

	RegularPolygon rp3(Point(3, -4), 18, 5);
	std::cout << "Count of points: " <<rp3.get_components().size() << ", angle between sides = " << rp3.get_angle() << " degrees\n"; 
	std::cout << "Perimeter = " << rp3.perimeter() << ", area = " << rp3.area()<< "\n";
	std::vector<Point> mpp = rp3.get_components();
	std::cout << "Coordinates of points:\n";
	for (size_t i = 0; i < 18; i++)
		std::cout << '(' << mpp[i].get_x() << ", " << mpp[i].get_y() << ")\n";


	std::cout << "\n\n---------------- TEST #10 ----------------\n";
	std::cout << "<Dynamic polymorphism of Shape abstract class>\n\n";	
	Shape * shapes[] = {&pg1, &tri1, &trp1, &trp2, &rp1, &rp3};

	for (size_t i = 0; i < 6; i++) {
		std::cout << "Shape #" << i + 1 << ": count of points - " << shapes[i]->get_components().size();
		std::cout << ", perimeter = "<< shapes[i]->perimeter() << ", area = " << shapes[i]->area() << '\n';
	}

	delete [] points3;
	delete [] points4;
	delete [] points6;

	return 0;
}