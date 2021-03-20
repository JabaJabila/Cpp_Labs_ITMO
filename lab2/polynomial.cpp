#include <iostream>
#include <vector>

class Polynomial {
public:
	Polynomial() : components_({0}), size_(1) {}
	explicit Polynomial(std::vector<double> & comps) : components_(comps), size_(comps.size()) {};

	Polynomial(double * array, size_t size) {
		size_ = size;
		for (size_t i = 0; i < size; ++i)
			components_.push_back(array[i]);
	}

	Polynomial(Polynomial const & other) = default;
	Polynomial & operator=(Polynomial const & other) = default;
	~Polynomial() = default;

	size_t get_size() const {return size_;}
	std::vector<double> get_components() const {return components_;}

	bool operator==(Polynomial const & other) const {
		if (size_ != other.size_)
			return false;
		for (size_t i = 0; i < size_; ++i)
			if (components_[i] != other[i])
				return false;
		return true;
	}

	bool operator!=(Polynomial const & other) const {return !(*this == other);}

	bool operator>(Polynomial const & other) const {
		if (size_ > other.size_)
			return true;
		if (size_ < other.size_)
			return false;
		for (size_t i = size_; i > 0; i--) {
			if (components_[i - 1] > other[i - 1])
				return true;
			if (components_[i - 1] < other[i - 1])
				return false;
		}
		return false;
	}

	bool operator<(Polynomial const & other) const {return (other > *this);}
	bool operator>=(Polynomial const & other) const {return (*this > other || *this == other);}
	bool operator<=(Polynomial const & other) const {return (*this < other || *this == other);}

	const double & operator[](const size_t index) const {return components_[index];}
	double & operator[](const size_t index) {return components_[index];}

	Polynomial operator-() const {
		Polynomial new_poly(*this);
		for (size_t i = 0; i < size_; ++i)
			new_poly[i] *= -1;
		return new_poly;
	}

	Polynomial operator+() const {return Polynomial (*this);}

	Polynomial & operator+=(Polynomial const & right) {
		size_t num;
		size_ > right.size_ ? num = right.size_ : num = size_;
		for (size_t i = 0; i < num; ++i)
			components_[i] += right[i];
		right.size_ > size_ ? size_ = right.size_ : size_;
		for (size_t i = num; i < size_; ++i)
			components_.push_back(right[i]);

		return *this;
	}

	Polynomial & operator-=(Polynomial const & right) {return *this+=(-right);}

	Polynomial & operator+=(double const right) {
		components_[0] += right;
		return *this;
	}

	Polynomial & operator-=(double const right) {return *this +=(-right);}

	Polynomial & operator*=(Polynomial const & right) {
		std::vector<double> new_comps;
		new_comps.assign(size_ + right.size_ - 1, 0);
		for (size_t i = 0; i < size_; ++i)
			for (size_t j = 0; j < right.size_; ++j)
				new_comps[i + j] += components_[i] * right.components_[j];

		size_ = size_ + right.size_ - 1;
		components_ = new_comps;
		return *this;
	}

	Polynomial & operator*=(const double right) {
		for (size_t i = 0; i < size_; ++i)
			components_[i] *= right;
		return *this;
	}

	Polynomial & operator/=(const double right) {return *this*=(1/right);}

	friend std::ostream & operator<<(std::ostream &, const Polynomial &);

private:
	std::vector<double> components_;
	size_t size_;
};

//--------------------------------------------------------------------------------------------------

Polynomial operator+(Polynomial const & left, Polynomial const & right) {
	Polynomial tmp = left;
	return tmp += right;
}

Polynomial operator+(Polynomial const & left, const double right) {
	std::vector<double> tmp = {right};
	return left + Polynomial(tmp);
}

Polynomial operator-(Polynomial const & left, Polynomial const & right) {return (left + (-right));}
Polynomial operator-(Polynomial const & left, const double right) {return (left + (-right));}
Polynomial operator+(const double left, Polynomial const & right) {return right + left;}
Polynomial operator-(const double left, Polynomial const & right) {return -right + left;}

Polynomial operator*(Polynomial const & left, Polynomial const & right) {
	Polynomial tmp = left;
	return tmp*=right;
}

Polynomial operator*(Polynomial const & left, const double right) {
	Polynomial tmp = left;
	return tmp*=right;
}

Polynomial operator*(const double left, Polynomial const & right) {
	Polynomial tmp = right;
	return tmp*=left;
}

Polynomial operator/(Polynomial const & left, const double right) {
	Polynomial tmp = left;
	return tmp/=right;
}

std::ostream & operator<<(std::ostream & stream, const Polynomial & poly) {
	stream << poly[0] << ' ';
	if (poly.size_ > 1) {
		if (poly[1] > 0)
			stream << "+ "<< poly[1] << "x ";
		else if (poly[1] < 0)
			stream << "- "<< -poly[1] << "x ";
	}
	for (size_t i = 2; i < poly.size_; ++i)
		if (poly[i] > 0)
			stream << "+ "<< poly[i] << "x^" << i << ' ';
		else if (poly[i] < 0)
			stream << "- "<< -poly[i] << "x^" << i << ' ';
	return stream;
}

std::istream & operator>>(std::istream & stream, Polynomial & poly) {
	double x;
	std::vector<double> v;
	while (stream >> x)
		v.push_back(x);
	Polynomial tmp(v);
	poly = tmp;
	return stream;
}

// int main() {                                // TESTS
// 	std::vector<double> v1 = {4, -4, 1};
// 	std::vector<double> v2 = {-5, 2};
// 	std::vector<double> v3 = {-8, 1, -4, 2};
// 	double * array = new double[3];
// 	array[0] = -2;
// 	array[1] = 3;
// 	array[2] = 1;

// 	Polynomial p1(v1);
// 	Polynomial p2(array, 3);
// 	Polynomial p3(v2);

// 	std::cout << p1 << "\n";
// 	std::cout << p3 << "\n";
// 	std::cout << (p1 == p3) << "\n";
// 	std::cout << (p1 != p3) << "\n";
// 	std::cout << (p1 > p3) << "\n";
// 	std::cout << (p1 < p3) << "\n";
// 	std::cout << (p1 >= p3) << "\n";
// 	std::cout << (p1 <= p3) << "\n";
// 	p1 = p3;
// 	std::cout << (p1 == p3) << "\n";
// 	std::cout << (p1 != p3) << "\n";
// 	std::cout << (p1 > p3) << "\n";
// 	std::cout << (p1 < p3) << "\n";
// 	std::cout << (p1 >= p3) << "\n";
// 	std::cout << (p1 <= p3) << "\n";

// 	delete [] array;

// 	return 0;
// }