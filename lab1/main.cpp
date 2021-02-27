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
		std::cout << "\n---------------- ТЕСТ #1 ----------------\n\n";
		std::cout << "Координаты точки A: (" << A.get_x() << ", " << A.get_y() << ")\n";
		std::cout << "Координаты точки B: (" << B.get_x() << ", " << B.get_y() << ")\n";
		std::cout << "Координаты точки C: (" << C.get_x() << ", " << C.get_y() << ")\n";
		std::cout << "Координаты точки D: (" << D.get_x() << ", " << D.get_y() << ")\n";
		std::cout << "Координаты точки E: (" << E.get_x() << ", " << E.get_y() << ")\n";
		E == A ? std::cout << "Точка E равна точке A\n" : std::cout << "Точка E не равна точке A\n";
		A == B ? std::cout << "Точка A равна точке B\n" : std::cout << "Точка A не равна точке B\n";
	}
	catch (const char * exception) {
		std::cerr << "Error: " << exception << '\n';
	}

	Segment s1(A, B);
	Segment s2(C, D);

	try {
		std::cout << "\n\n---------------- ТЕСТ #2 ----------------\n\n";		
		std::cout << "Координаты начала отрезка AB: (" << s1.start().get_x() << ", " << s1.start().get_y() << ")\n";
		std::cout << "Координаты конца отрезка AB: (" << s1.end().get_x() << ", " << s1.end().get_y() << ")\n";
		std::cout << "Длина отрезка AB = " << s1.length() << "\n";
		std::cout << "\nКоординаты начала отрезка CD: (" << s2.start().get_x() << ", " << s2.start().get_y() << ")\n";
		std::cout << "Координаты конца отрезка CD: (" << s2.end().get_x() << ", " << s2.end().get_y() << ")\n";
		std::cout << "Длина отрезка CD = " << s2.length() << "\n";
		std::cout << "\nПопытка создать отрезок AA:\n";

		Segment s0(A, A);
	}
	catch (const char * exception) {
		std::cerr << "Error: " << exception << '\n';
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
		std::cout << "\n\n---------------- ТЕСТ #3 ----------------\n\n";		
		std::cout << "Кол-во вершин ломаной №1: " << pl1.get_components().size() << "\n";
		std::cout << "Длина ломаной №1 = " << pl1.length() << "\n";
		std::cout << "\nКол-во вершин ломаной №2: " << pl2.get_components().size() << "\n";
		std::cout << "Длина ломаной №2 = " << pl2.length() << "\n";
		std::cout << "\nКол-во вершин замкнутой ломаной №1: " << cl1.get_components().size() << "\n";
		std::cout << "Длина ломаной №1 = " << cl1.length() << "\n";
		std::cout << "\nКол-во вершин замкнутой ломаной №2: " << cl2.get_components().size() << "\n";
		std::cout << "Длина ломаной №2 = " << cl2.length() << "\n";
		std::cout << "\nПопытка создать замкнутую ломаную с 2 вершинами:\n";

		ClosedPolyline cl3(points2);
	}
	catch (const char * exception) {
		std::cerr << "Error: " << exception << '\n';
	}

	std::cout << "\n\n---------------- ТЕСТ #4 ----------------\n";
	std::cout << "<Динамический полиморфизм для абстрактного класса линий>\n\n";	
	Line * lines[] = {&s1, &s2, &pl0, &cl1, &cl2};

		for (size_t i = 0; i < 5; i++) {
			std::cout << "Линия №" << i + 1 << ": ";
			std::cout << "кол-во вершин - " << lines[i]->get_components().size() << ", ";
			std::cout << "длина = " << lines[i]->length() << '\n';
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
		std::cout << "\n\n---------------- ТЕСТ #5 ----------------\n\n";		
		std::cout << "Кол-во вершин многоугольника: " << pg1.get_components().size() << "\n";
		std::cout << "Периметр = " << pg1.perimeter() << ", площадь = " << pg1.area() << "\n";
		
		points5.push_back(Point(0, 0.5));
		std::cout << "\nПопытка создать невыпуклый многоугольник:\n";
		Polygon pg2(points5);
	}
	catch (const char * exception) {
		std::cerr << "Error: " << exception << '\n';
	}

	Triangle tri1(points6, 3);
	points5.pop_back();

	try {
		std::cout << "\n\n---------------- ТЕСТ #6 ----------------\n\n";		
		std::cout << "Кол-во вершин треугольника: " << tri1.get_components().size() << "\n";
		std::cout << "Периметр = " << tri1.perimeter() << ", площадь = " << tri1.area() << "\n";
		std::cout << "\nПопытка создать тругольник с 4 вершинами:\n";
		Triangle tri2(points5);
	}
	catch (const char * exception) {
		std::cerr << "Error: " << exception << '\n';
	}

	Trapezoid trp1(points8);
	Trapezoid trp2(points9);

	try {
		std::cout << "\n\n---------------- ТЕСТ #7 ----------------\n\n";		
		std::cout << "Кол-во вершин трапеции №1: " << trp1.get_components().size() << "\n";
		std::cout << "Периметр = " << trp1.perimeter() << ", площадь = " << trp1.area() << "\n";

		std::cout << "\nКол-во вершин трапеции №2: " << trp2.get_components().size() << "\n";
		std::cout << "Периметр = " << trp2.perimeter() << ", площадь = " << trp2.area() << "\n";

		std::cout << "\nПопытка создать трапецию без параллельных сторон:\n";
		Trapezoid trp3(points7);

	}
	catch (const char * exception) {
		std::cerr << "Error: " << exception << '\n';
	}

	RegularPolygon rp1(points10);

	try {
		std::cout << "\n\n---------------- ТЕСТ #8 ----------------\n\n";		
		std::cout << "Кол-во вершин правильного многоугольника: " << rp1.get_components().size() << "\n";
		std::cout << "Длина стороны = " << rp1.get_segmentlen() << ", угол между сторонами = " << rp1.get_angle() << " град.\n";
		std::cout << "Периметр = " << rp1.perimeter() << ", площадь = " << rp1.area() <<"\n";
		std::cout << "\nПопытка создать неправильный многоугольник:\n";
		RegularPolygon rp3(points7);

	}
	catch (const char * exception) {
		std::cerr << "Error: " << exception << '\n';
	}



	std::cout << "\n\n---------------- ТЕСТ #9 ----------------\n";
	std::cout << "<Создаём правильный 18-угольник с центром в точке (3, -4) и со стороной равной 5>\n\n";

	RegularPolygon rp3(Point(3, -4), 18, 5);
	std::cout << "Кол-во вершин: " <<rp3.get_components().size() << ", угол между сторонами = " << rp3.get_angle() << " град.\n"; 
	std::cout << "Периметр = " << rp3.perimeter() << ", площадь = " << rp3.area()<< "\n";
	std::vector<Point> mpp = rp3.get_components();
	std::cout << "Координаты вершин:\n";
	for (size_t i = 0; i < 18; i++)
		std::cout << '(' << mpp[i].get_x() << ", " << mpp[i].get_y() << ")\n";


	std::cout << "\n\n---------------- ТЕСТ #10 ----------------\n";
	std::cout << "<Динамический полиморфизм для абстрактного класса фигур>\n\n";	
	Shape * shapes[] = {&pg1, &tri1, &trp1, &trp2, &rp1, &rp3};

	for (size_t i = 0; i < 6; i++) {
		std::cout << "Фигура №" << i + 1 << ": кол-во вершин - " << shapes[i]->get_components().size();
		std::cout << ", периметр = "<< shapes[i]->perimeter() << ", площадь = " << shapes[i]->area() << '\n';
	}

	delete [] points3;
	delete [] points4;
	delete [] points6;

	return 0;
}