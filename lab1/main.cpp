#include <iostream>
#include "geometry.hpp"

int main() {

	setlocale(LC_ALL, "Russian");

	Point A{};
	Point B(1, 1);
	Point C(-1.5, 2);
	Point D(3);
	Point E = A;

	try {
		std::cout << "\n---------------- ���� #1 ----------------\n\n";
		std::cout << "���������� ����� A: (" << A.get_x() << ", " << A.get_y() << ")\n";
		std::cout << "���������� ����� B: (" << B.get_x() << ", " << B.get_y() << ")\n";
		std::cout << "���������� ����� C: (" << C.get_x() << ", " << C.get_y() << ")\n";
		std::cout << "���������� ����� D: (" << D.get_x() << ", " << D.get_y() << ")\n";
		std::cout << "���������� ����� E: (" << E.get_x() << ", " << E.get_y() << ")\n";
		E == A ? std::cout << "����� E ����� ����� A\n" : std::cout << "����� E �� ����� ����� A\n";
		A == B ? std::cout << "����� A ����� ����� B\n" : std::cout << "����� A �� ����� ����� B\n";
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	Segment s1(A, B);
	Segment s2(C, D);

	try {
		std::cout << "\n\n---------------- ���� #2 ----------------\n\n";		
		std::cout << "���������� ������ ������� AB: (" << s1.start().get_x() << ", " << s1.start().get_y() << ")\n";
		std::cout << "���������� ����� ������� AB: (" << s1.end().get_x() << ", " << s1.end().get_y() << ")\n";
		std::cout << "����� ������� AB = " << s1.length() << "\n";
		std::cout << "\n���������� ������ ������� CD: (" << s2.start().get_x() << ", " << s2.start().get_y() << ")\n";
		std::cout << "���������� ����� ������� CD: (" << s2.end().get_x() << ", " << s2.end().get_y() << ")\n";
		std::cout << "����� ������� CD = " << s2.length() << "\n";
		std::cout << "\n������� ������� ������� AA:\n";

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
		std::cout << "\n\n---------------- ���� #3 ----------------\n\n";		
		std::cout << "���-�� ������ ������� �1: " << pl1.get_components().size() << "\n";
		std::cout << "����� ������� �1 = " << pl1.length() << "\n";
		std::cout << "\n���-�� ������ ������� �2: " << pl2.get_components().size() << "\n";
		std::cout << "����� ������� �2 = " << pl2.length() << "\n";
		std::cout << "\n���-�� ������ ��������� ������� �1: " << cl1.get_components().size() << "\n";
		std::cout << "����� ������� �1 = " << cl1.length() << "\n";
		std::cout << "\n���-�� ������ ��������� ������� �2: " << cl2.get_components().size() << "\n";
		std::cout << "����� ������� �2 = " << cl2.length() << "\n";
		std::cout << "\n������� ������� ��������� ������� � 2 ���������:\n";

		ClosedPolyline cl3(points2);
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	std::cout << "\n\n---------------- ���� #4 ----------------\n";
	std::cout << "<������������ ����������� ��� ������������ ������ �����>\n\n";	
	Line * lines[] = {&s1, &s2, &pl0, &cl1, &cl2};

		for (size_t i = 0; i < 5; i++) {
			std::cout << "����� �" << i + 1 << ": ";
			std::cout << "���-�� ������ - " << lines[i]->get_components().size() << ", ";
			std::cout << "����� = " << lines[i]->length() << '\n';
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
		std::cout << "\n\n---------------- ���� #5 ----------------\n\n";		
		std::cout << "���-�� ������ ��������������: " << pg1.get_components().size() << "\n";
		std::cout << "�������� = " << pg1.perimeter() << ", ������� = " << pg1.area() << "\n";
		
		points5.push_back(Point(0, 0.5));
		std::cout << "\n������� ������� ���������� �������������:\n";
		Polygon pg2(points5);
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	Triangle tri1(points6, 3);
	points5.pop_back();

	try {
		std::cout << "\n\n---------------- ���� #6 ----------------\n\n";		
		std::cout << "���-�� ������ ������������: " << tri1.get_components().size() << "\n";
		std::cout << "�������� = " << tri1.perimeter() << ", ������� = " << tri1.area() << "\n";
		std::cout << "\n������� ������� ���������� � 4 ���������:\n";
		Triangle tri2(points5);
	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	Trapezoid trp1(points8);
	Trapezoid trp2(points9);

	try {
		std::cout << "\n\n---------------- ���� #7 ----------------\n\n";		
		std::cout << "���-�� ������ �������� �1: " << trp1.get_components().size() << "\n";
		std::cout << "�������� = " << trp1.perimeter() << ", ������� = " << trp1.area() << "\n";

		std::cout << "\n���-�� ������ �������� �2: " << trp2.get_components().size() << "\n";
		std::cout << "�������� = " << trp2.perimeter() << ", ������� = " << trp2.area() << "\n";

		std::cout << "\n������� ������� �������� ��� ������������ ������:\n";
		Trapezoid trp3(points7);

	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}

	RegularPolygon rp1(points10);

	try {
		std::cout << "\n\n---------------- ���� #8 ----------------\n\n";		
		std::cout << "���-�� ������ ����������� ��������������: " << rp1.get_components().size() << "\n";
		std::cout << "����� ������� = " << rp1.get_segmentlen() << ", ���� ����� ��������� = " << rp1.get_angle() << " ����.\n";
		std::cout << "�������� = " << rp1.perimeter() << ", ������� = " << rp1.area() <<"\n";
		std::cout << "\n������� ������� ������������ �������������:\n";
		RegularPolygon rp3(points7);

	}
	catch (const std::logic_error & err) {
		std::cerr << "Error: " << err.what() << '\n';
	}



	std::cout << "\n\n---------------- ���� #9 ----------------\n";
	std::cout << "<������ ���������� 18-�������� � ������� � ����� (3, -4) � �� �������� ������ 5>\n\n";

	RegularPolygon rp3(Point(3, -4), 18, 5);
	std::cout << "���-�� ������: " <<rp3.get_components().size() << ", ���� ����� ��������� = " << rp3.get_angle() << " ����.\n"; 
	std::cout << "�������� = " << rp3.perimeter() << ", ������� = " << rp3.area()<< "\n";
	std::vector<Point> mpp = rp3.get_components();
	std::cout << "���������� ������:\n";
	for (size_t i = 0; i < 18; i++)
		std::cout << '(' << mpp[i].get_x() << ", " << mpp[i].get_y() << ")\n";


	std::cout << "\n\n---------------- ���� #10 ----------------\n";
	std::cout << "<������������ ����������� ��� ������������ ������ �����>\n\n";	
	Shape * shapes[] = {&pg1, &tri1, &trp1, &trp2, &rp1, &rp3};

	for (size_t i = 0; i < 6; i++) {
		std::cout << "������ �" << i + 1 << ": ���-�� ������ - " << shapes[i]->get_components().size();
		std::cout << ", �������� = "<< shapes[i]->perimeter() << ", ������� = " << shapes[i]->area() << '\n';
	}

	delete [] points3;
	delete [] points4;
	delete [] points6;

	return 0;
}