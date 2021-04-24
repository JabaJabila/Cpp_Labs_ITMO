#include <iostream>
#include <vector>
#include <deque>

template<class InputIterator, class UnaryPredicate>
bool all_of(InputIterator begin, InputIterator end, UnaryPredicate p) {
	for (; begin != end; ++begin)
		if (!p(*begin))
			return false;
	return true;
}

template<class InputIterator, class UnaryPredicate>
bool any_of(InputIterator begin, InputIterator end, UnaryPredicate p) {
	for (; begin != end; ++begin)
		if (p(*begin))
			return true;
	return false;
}

template<class InputIterator, class UnaryPredicate>
bool none_of(InputIterator begin, InputIterator end, UnaryPredicate p) {
	for (; begin != end; ++begin)
		if (p(*begin))
			return false;
	return true;
}

template<class InputIterator, class UnaryPredicate>
bool one_of(InputIterator begin, InputIterator end, UnaryPredicate p) {
	bool result = false;
	for (; begin != end; ++begin)
		if (p(*begin)) {
			if (result)
				return false;
			result = true;
		}		
	return result;
}

template<class InputIterator, class BinaryPredicate>
bool is_sorted(InputIterator begin, InputIterator end, BinaryPredicate p) {
	InputIterator next = begin;
	++next;
	--end;
	for (; begin != end; ++begin) {
		if (!p(*next, *begin)) {
			return false;
		}
		++next;
	}	
	return true;
}

template<class InputIterator, class UnaryPredicate>
bool is_partitioned(InputIterator begin, InputIterator end, UnaryPredicate p) {
	for (; begin != end; ++begin)
		if (p(*begin)) 
			break;
	for (; begin != end; ++begin)
		if (!p(*begin)) 
			return false;			
	return true;
}

template<class InputIterator, class BinaryPredicate>
bool is_palindrome(InputIterator begin, InputIterator end, BinaryPredicate p) {
	size_t mid = distance(begin, end) / 2;
	--end;
	for (size_t i = 0; i < mid; ++i) {
		if (!p(*begin, *end)) 
			return false;
		--end;
		++begin;
	}
	return true;
}

template<class InputIterator, class T>
InputIterator find_not(InputIterator begin, InputIterator end, const T& element) {
	for (; begin != end; ++begin)
		if (*begin != element) {
			return begin;
		}		
	return end;
}

template<class InputIterator, class T>
InputIterator find_backward(InputIterator begin, InputIterator end, const T& element) {
	InputIterator true_end = end;
	--end;
	--begin;
	for (; end != begin; --end)
		if (*end == element) {
			return end;
		}	
	return true_end;
}

//----------------------------------------------------------------------------------------------

class Point {

public:
	explicit Point(double x = 0, double y = 0) : x(x),  y(y) {}
	Point(Point const & other) = default;
	Point & operator=(Point const & other) = default;
	~Point() = default;

	double get_x() const {return x;}
	double get_y() const {return y;}
	bool operator==(Point const & right) const {return (x == right.x && y == right.y);}
	bool operator!=(Point const & right) const {return (x != right.x || y != right.y);}

private:
	double x;
	double y;
};


class isGreaterThan {
public:
	isGreaterThan(int value) : x(value) {}

	bool operator()(int value) {
		return value > x;
	}

private:
	int x;
};

template<class T>
bool isEqual(const T& x, const T& y) {
	return x == y;
}

template<class T>
bool isGreater(const T& x, const T& y) {
	return x > y;
}

bool xNotLess(const Point & p1, const Point & p2) {
	return p1.get_x() >= p2.get_x();
}

bool xPositive(const Point & p) {
	return p.get_x() > 0;
}

bool yNegative(const Point & p) {
	return p.get_y() < 0;
}

template<class T>
bool isLess(const T& x, const T& y) {
	return x < y;
}

bool isEven(const int x) {
	return x % 2 == 0;
}

bool bothMod2(const int x, const int y) {
	return x % 2 == y % 2;
}

// ------ TESTS ------

int main() {

	// std::vector<int> t1 {1, 2, 3, 5, 6, 7};
	// std::vector<int> t2 {5, 4, -2, -3, -5};
	// std::deque<int> t3 {1, 2, 3, 4, 5};
	// std::vector<int> t4 {1, 2, 3, 4, 3, 2, 1};
	// std::vector<int> t5 {1, 3, 5, 5, 3, 1};
	// std::vector<int> t6 {1, 2, 4, 8, 3, 2, 1};
	// std::vector<int> t7 {1, 3, 5, 4, 3, 1};
	// std::vector<int> t8 {1, 3, 6, 8, 7, 9};

	// std::cout << all_of(t1.begin(), t1.end(), isGreaterThan(0)) << '\n';
	// std::cout << all_of(t1.begin(), t1.end(), isGreaterThan(1)) << '\n';
	// std::cout << all_of(t1.begin(), t1.end(), isGreaterThan(5)) << '\n'; 
	// std::cout << all_of(t1.begin(), t1.end(), isEven) << '\n';

	// std::cout << any_of(t1.begin(), t1.end(), isGreaterThan(10)) << '\n';
	// std::cout << any_of(t1.begin(), t1.end(), isGreaterThan(50)) << '\n'; 
	// std::cout << any_of(t2.begin(), t2.end(), isEven) << '\n';

	// std::cout << none_of(t1.begin(), t1.end(), isGreaterThan(10)) << '\n';
	// std::cout << none_of(t1.begin(), t1.end(), isGreaterThan(50)) << '\n'; 
	// std::cout << none_of(t2.begin(), t2.end(), isEven) << '\n';

	// std::cout << one_of(t2.begin(), t2.end(), isGreaterThan(0)) << '\n';
	// std::cout << one_of(t1.begin(), t1.end(), isGreaterThan(10)) << '\n';
	// std::cout << one_of(t2.begin(), t2.end(), isGreaterThan(50)) << '\n'; 
	// std::cout << one_of(t2.begin(), t2.end(), isEven) << '\n';

	// std::vector<int>::iterator it1 = find_backward(t2.begin(), t2.end(), 7);
	// std::deque<int>::iterator it2;
	// std::cout << (it1 == t2.end() ? -1 : distance(t2.begin(), it1)) << '\n';
	// it1 = find_backward(t2.begin(), t2.end(), -1);
	// std::cout << (it1 == t2.end() ? -1 : distance(t2.begin(), it1)) << '\n';
	// it2 = find_not(t3.begin(), t3.end(), 7);
	// std::cout << (it2 == t3.end() ? -1 : distance(t3.begin(), it2)) << '\n';
	// it2 = find_not(t3.begin(), t3.begin() + 5, 7);
	// std::cout << (it2 == t3.begin() + 5 ? -1 : distance(t3.begin(), it2)) << '\n';

	// std::cout << is_sorted(t2.begin(), t2.end(), isLess<int>) << '\n';
	// std::cout << is_sorted(t3.begin(), t3.end(), isGreater<int>) << '\n';
	// std::cout << is_sorted(t4.begin(), t4.end(), isGreater<int>) << '\n';

	// std::cout << is_palindrome(t4.begin(), t4.end(), isEqual<int>) << '\n';
	// std::cout << is_palindrome(t5.begin(), t5.end(), isEqual<int>) << '\n';
	// std::cout << is_palindrome(t8.begin(), t8.end(), bothMod2) << '\n';

	// std::cout << is_palindrome(t6.begin(), t6.end(), isEqual<int>) << '\n';
	// std::cout << is_palindrome(t7.begin(), t7.end(), isEqual<int>) << '\n';
	// std::cout << is_palindrome(t7.begin(), t7.end(), bothMod2) << '\n'; 

	// std::cout << is_partitioned(t2.begin(), t2.begin(), isEven) << '\n';
	// std::cout << is_partitioned(t8.begin(), t8.end(), isGreaterThan(4)) << '\n';
	// std::cout << is_partitioned(t4.begin(), t4.end(), isEven) << '\n';

	// Point A{};
	// Point B(1, 1);
	// Point C(-1.5, 2);
	// Point D(3);
	// Point E = A;
	// Point F = B;

	// std::vector<Point> points {A, B, C, D, E};
	// std::vector<Point> points0 {A, B, C, F, E};

	// std::vector<Point> points1;
	// points1.push_back(Point(1, 1));
	// points1.push_back(Point(2, 1));
	// points1.push_back(Point(2, 0));
	// points1.push_back(Point(2, -3));
	// points1.push_back(Point(3, -1));

	// std::vector<Point> points2;
	// points2.push_back(Point());
	// points2.push_back(Point(1, 1));
	// points2.push_back(Point(2, 0));
	// points2.push_back(Point(2, 4));

	// std::vector<Point> points3;
	// points3.push_back(Point());
	// points3.push_back(Point(-1, 3));
	// points3.push_back(Point(-4, 0));
	// points3.push_back(Point(-2, 1));

	// std::vector<Point> points4;
	// points4.push_back(Point());
	// points4.push_back(Point(1, 1));
	// points4.push_back(Point(-2, -1));
	// points4.push_back(Point(-2, 4));

	// std::vector<Point> points5 {Point(), Point(), Point(), Point(1, 0), Point()};


	// std::cout << is_palindrome(points.begin(), points.end(), isEqual<Point>) << '\n';
	// std::cout << is_palindrome(points0.begin(), points0.end(), isEqual<Point>) << '\n';

	// std::cout << is_sorted(points1.begin(), points1.end(), xNotLess) << '\n';
	// std::cout << is_partitioned(points1.begin(), points1.end(), yNegative) << '\n';
	// std::cout << is_partitioned(points4.begin(), points4.end(), yNegative) << '\n';

	// std::cout << all_of(points1.begin(), points1.end(), xPositive) << '\n';
	// std::cout << any_of(points2.begin(), points2.end(), xPositive) << '\n';
	// std::cout << one_of(points2.begin(), points2.end(), xPositive) << '\n';
	// std::cout << one_of(points4.begin(), points4.end(), xPositive) << '\n';
	// std::cout << none_of(points3.begin(), points3.end(), xPositive) << '\n';

	// std::vector<Point>::iterator it3 = find_backward(points.begin(), points.end(), Point());
	// std::cout << (it3 == points.end() ? -1 : distance(points.begin(), it3)) << '\n';
	// it3 = find_not(points5.begin(), points5.end(), Point());
	// std::cout << (it3 == points5.end() ? -1 : distance(points5.begin(), it3)) << '\n';

	return 0;
}