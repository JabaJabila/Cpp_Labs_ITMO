#include <iostream>
#include <algorithm>
#include "circular_buffer.hpp"

template<class InputIterator, class T>
	InputIterator ffind(InputIterator begin, InputIterator end, const T& element) {
		for (; begin != end; ++begin) {
			if (*begin == element) {
				return begin;
			}
		}
		return end;
	}

template<class InputIterator, class T>
	InputIterator rffind(InputIterator begin, InputIterator end, const T& element) {
		InputIterator true_end = end;
		--end;
		for (; begin != end; --end) {
			if (*end == element)
				return end;
		}
		if (*end == element)
				return end;
		return true_end;
	}

template<class InputIterator>
	void printc(InputIterator begin, InputIterator end) {
		for (; begin != end; ++begin)
			std::cout << *begin << ' ';
	}

template<class T>
bool isLess(const T& x, const T& y) {
	return x > y;
}

template<class InputIterator>
void printb(InputIterator begin, InputIterator end) {
	--end;
	for (; begin != end; --end)
		std::cout << *end << ' ';
	std::cout << *end << '\n';
}

int main() {

	circular_buffer<int> itb2 {-1, 0, 1, 2, 3};
	itb2.push_back(4);
	itb2.push_back(5);

	// std::cout << *(itb2.begin() += 1) << " ";
	// std::cout << *(itb2.begin() += 2) << " ";
	// std::cout << *(itb2.begin() += 3) << " ";
	// std::cout << *(itb2.begin() += 4) << " ";
	// std::cout << *(itb2.begin() += 5) << " ";
	// std::cout << *(itb2.end() += -1) << " ";
	// std::cout << *(itb2.end() += -2) << " ";
	// std::cout << *(itb2.end() -= 1) << " ";
	// std::cout << *(itb2.end() -= 2) << " ";
	// std::cout << *(itb2.end() -= 3) << " ";
	// std::cout << *(itb2.end() -= 4) << " ";
	// std::cout << *(itb2.end() -= 5) << " ";
	// std::cout << *(itb2.begin() -= -4) << "\n";

	std::cout << (std::binary_search(itb2.begin(), itb2.end(), 1)) << " ";
	std::cout << (std::binary_search(itb2.begin() + 1, itb2.end(), 1)) << " ";
	std::cout << (std::binary_search(itb2.begin() + 1, itb2.end(), 2)) << " ";
	std::cout << (std::binary_search(itb2.begin() + 1, itb2.end(), 3)) << " ";
	std::cout << (std::binary_search(itb2.begin() + 1, itb2.end(), 4)) << " ";
	std::cout << (std::binary_search(itb2.begin() + 1, itb2.end(), 5)) << " ";
	std::cout << (std::binary_search(itb2.begin(), itb2.end(), 0)) << "\n";

	std::cout << std::is_heap(itb2.begin(), itb2.end()) << " ";
	std::make_heap(itb2.begin(), itb2.end());
	std::cout << std::is_heap(itb2.begin(), itb2.end()) << "\n";
	for (auto i : itb2)
		std::cout << i << " ";

	
	// circular_buffer<int>::iterator iter1 = itb2.begin();
	// iter1++;
	// iter1++;
	// std::cout << itb2.end() - itb2.begin() << " ";
	// std::cout << itb2.begin() - itb2.end() << " ";
	// std::cout << itb2.end() - iter1 << " ";
	// std::cout << iter1 - itb2.begin() << " ";
	// std::cout << itb2.begin() - iter1 << " ";
	// iter1++;
	// iter1++;
	// std::cout << itb2.end() - iter1 << " ";
	// std::cout << iter1 - itb2.end() << " ";


	// circular_buffer<int> buf1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	// buf1.push_front(0);
	// circular_buffer<int> buf3;
	// buf3 = buf1;

	// for (unsigned i = 0; i < buf3.size(); ++i)
	// 	std::cout << buf3[i] << ' ';
	// std::cout << '\n' << buf3.size() << ' ' << buf3.capacity() << ' ' << buf3.front() << ' ' << buf3.back() << ' ' << buf3.empty() << ' ' << (buf3 == buf1) << "\n\n";

	// buf3.push_back(10);

	// for (unsigned i = 0; i < buf3.size(); ++i)
	// 	std::cout << buf3[i] << ' ';
	// std::cout << '\n' << buf3.size() << ' ' << buf3.capacity() << ' ' << buf3.front() << ' ' << buf3.back() << ' ' << buf3.empty() << ' ' << (buf3 == buf1) << "\n\n";

	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.empty() << "\n\n";

	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << "\n\n";

	// buf1.clear();
	// std::cout << buf1.empty() << "\n";
	// buf1.push_front(0);
	// buf1.push_front(-1);
	// buf1.push_front(-2);
	// buf1.push_front(-3);

	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << "\n\n";

	// buf1.pop_front();
	// buf1.pop_front();
	// buf1.pop_front();
	// buf1.pop_front();
	// buf1.pop_front();
	// buf1.pop_back();
	// buf1.pop_back();

	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << "\n\n";

	// circular_buffer<int> buf2 {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};

	// std::cout << (buf1 == buf2) << "\n\n";

	// buf1.push_back(11);
	// buf1.push_back(12);

	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << "\n\n";

	// buf1.push_back(-1);
	// buf1.push_back(-2);
	// buf1.push_back(-3);

	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';
	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';
	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';
	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';
	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';
	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';
	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';
	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// buf1.push_back(-3);
	// buf1.push_back(-4);
	// buf1.push_back(-5);
	// buf1.push_back(-6);
	// buf1.push_back(-7);
	// buf1.push_back(-8);
	// buf1.push_back(-9);
	// buf1.push_back(-10);
	// buf1.push_back(-11);
	// buf1.push_back(-12);
	// buf1.push_back(-13);
	// buf1.push_back(-14);
	// buf1.push_back(-15);
	// buf1.push_back(-16);
	// buf1.push_back(-17);
	// buf1.push_back(-18);
	// buf1.push_back(-19);
	// buf1.push_back(-20);

	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// buf1.push_back(1);
	// buf1.push_back(2);
	// buf1.push_back(3);
	// buf1.push_back(4);
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// buf1.pop_back();
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// buf1.push_back(1);
	// buf1.push_back(2);
	// buf1.push_back(3);
	// buf1.push_back(4);
	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// buf1.pop_back();
	// buf1.pop_back();
	// buf1.pop_back();
	// buf1.pop_back();
	// buf1.pop_back();
	// buf1.pop_back();
	// buf1.pop_back();
	// buf1.pop_back();
	// buf1.pop_back();

	// for (unsigned i = 0; i < buf1.size(); ++i)
	// 	std::cout << buf1[i] << ' ';
	// std::cout << '\n' << buf1.size() << ' ' << buf1.capacity() << ' ' << buf1.front() << ' ' << buf1.back() << ' ' << buf1.empty() << '\n';

	// circular_buffer<unsigned> buf4 {1, 2, 3, 4, 5};
	// buf4.push_back(7);
	// buf4.push_back(8);
	// buf4.pop_back();
	// buf4.pop_back();
	// buf4.pop_front();
	// buf4.pop_front();


	// for (unsigned i = 0; i < buf4.size(); ++i)
	// 	std::cout << buf4[i] << ' ';
	// std::cout << '\n' << buf4.size() << ' ' << buf4.capacity() << ' ' << buf4.front() << ' ' << buf4.back() << ' ' << buf4.empty() << "\n\n";
 
	// buf4.push_back(7);
	// buf4.push_back(8);
	// buf4.push_front(1);
	// buf4.push_front(2);

	// for (unsigned i = 0; i < buf4.size(); ++i)
	// 	std::cout << buf4[i] << ' ';
	// std::cout << '\n' << buf4.size() << ' ' << buf4.capacity() << ' ' << buf4.front() << ' ' << buf4.back() << ' ' << buf4.empty() << "\n\n";

	// buf4.push_back(1);

	// for (unsigned i = 0; i < buf4.size(); ++i)
	// 	std::cout << buf4[i] << ' ';
	// std::cout << '\n' << buf4.size() << ' ' << buf4.capacity() << ' ' << buf4.front() << ' ' << buf4.back() << ' ' << buf4.empty() << "\n\n";

	// buf4.push_back(2);
	// buf4.push_back(3);
	// buf4.push_front(9);

	// for (unsigned i = 0; i < buf4.size(); ++i)
	// 	std::cout << buf4[i] << ' ';
	// std::cout << '\n' << buf4.size() << ' ' << buf4.capacity() << ' ' << buf4.front() << ' ' << buf4.back() << ' ' << buf4.empty() << "\n\n";

	// buf4.pop_back();
	// buf4.pop_back();
	
	// for (unsigned i = 0; i < buf4.size(); ++i)
	// 	std::cout << buf4[i] << ' ';
	// std::cout << '\n' << buf4.size() << ' ' << buf4.capacity() << ' ' << buf4.front() << ' ' << buf4.back() << ' ' << buf4.empty() << "\n\n";

	// buf4.pop_front();
	// buf4.pop_front();
	// for (unsigned i = 0; i < buf4.size(); ++i)
	// 	std::cout << buf4[i] << ' ';
	// std::cout << '\n' << buf4.size() << ' ' << buf4.capacity() << ' ' << buf4.front() << ' ' << buf4.back() << ' ' << buf4.empty() << "\n\n";

	// buf4[0] = 101;
	// for (unsigned i = 0; i < buf4.size(); ++i)
	// 	std::cout << buf4[i] << ' ';
	// std::cout << '\n' << buf4.size() << ' ' << buf4.capacity() << ' ' << buf4.front() << ' ' << buf4.back() << ' ' << buf4.empty() << "\n\n";

	// circular_buffer<int> b1 {1, 2, 3, 4, 5};
	// circular_buffer<int> b2 {2, 3, 6, 7, 8};
	// circular_buffer<int> b3;
	// b3 = b1;

	// std::cout << (b1 == b2) << ' ' << (b1 == b3) << '\n';

	// b2.push_front(1);
	// b2.pop_back();
	// b2.pop_back();
	// b2.push_back(4);
	// b2.push_back(5);

	// std::cout << '\n' << (b1 == b2) << '\n';

	// b2.change_capacity(8);

	// for (unsigned i = 0; i < b2.size(); ++i)
	// 	std::cout << b2[i] << ' ';
	// std::cout << '\n' << b2.size() << ' ' << b2.capacity() << ' ' << b2.front() << ' ' << b2.back() << ' ' << b2.empty() << "\n\n";

	// b2.push_back(6);
	// b2.push_back(7);
	// b2.push_back(8);

	// for (unsigned i = 0; i < b2.size(); ++i)
	// 	std::cout << b2[i] << ' ';
	// std::cout << '\n' << b2.size() << ' ' << b2.capacity() << ' ' << b2.front() << ' ' << b2.back() << ' ' << b2.empty() << "\n\n";

	// b2.pop_front();
	// b2.pop_back();
	// b2.shrink_to_fit();

	// for (unsigned i = 0; i < b2.size(); ++i)
	// 	std::cout << b2[i] << ' ';
	// std::cout << '\n' << b2.size() << ' ' << b2.capacity() << ' ' << b2.front() << ' ' << b2.back() << ' ' << b2.empty() << "\n\n";

	// b2.push_front(9);
	// b2.push_front(8);
	// b2.push_front(7);
	// b2.push_front(6);

	// for (unsigned i = 0; i < b2.size(); ++i)
	// 	std::cout << b2[i] << ' ';
	// std::cout << '\n' << b2.size() << ' ' << b2.capacity() << ' ' << b2.front() << ' ' << b2.back() << ' ' << b2.empty() << "\n\n";

	// b2.pop_back();
	// b2.pop_back();
	// b2.change_capacity(5);

	// for (unsigned i = 0; i < b2.size(); ++i)
	// 	std::cout << b2[i] << ' ';
	// std::cout << '\n' << b2.size() << ' ' << b2.capacity() << ' ' << b2.front() << ' ' << b2.back() << ' ' << b2.empty() << "\n\n";

	// b2.push_back(10);

	// for (unsigned i = 0; i < b2.size(); ++i)
	// 	std::cout << b2[i] << ' ';
	// std::cout << '\n' << b2.size() << ' ' << b2.capacity() << ' ' << b2.front() << ' ' << b2.back() << ' ' << b2.empty() << "\n\n";

	// b2.clear();
	// std::cout << '\n' << b2.size() << ' ' << b2.capacity() << ' ' << b2.empty() << "\n\n";

	// circular_buffer<int> itb {1, 2, 3, 4, 5};
	// printc(itb.begin(), itb.end());
	// std::cout << "\n" << *ffind(itb.begin(), itb.end(), 3) << "\n";
	// itb.push_back(6);

	// printc(itb.begin(), itb.end());
	// std::cout << "\n" << *ffind(itb.begin(), itb.end(), 3) << "\n";

	// itb.push_back(7);
	// itb.push_back(8);


	// printc(itb.begin(), itb.end());
	// if (rffind(itb.begin(), itb.end(), 7) == itb.end())
	// 	std::cout << "\n" << -1 << "\n";
	// else
	// 	std::cout << "\n" << *rffind(itb.begin(), itb.end(), 7) << "\n";

	// itb.pop_back();
	// itb.pop_back();

	// printc(itb.begin(), itb.end());
	// if (rffind(itb.begin(), itb.end(), 7) == itb.end())
	// 	std::cout << "\n" << -1 << "\n";
	// else
	// 	std::cout << "\n" << *rffind(itb.begin(), itb.end(), 7) << "\n";

	// itb.push_front(1);
	// itb.push_front(2);
	// itb.push_front(3);
	// itb.push_front(4);
	// itb.push_front(5);
	// itb.push_front(6);

	// std::cout << "\n";
	// printb(itb.begin(), itb.end());
	// printc(itb.begin(), itb.end());
	// if (rffind(itb.begin(), itb.end(), 2) == itb.end())
	// 	std::cout << "\n" << -1 << "\n";
	// else
	// 	std::cout << "\n" << *rffind(itb.begin(), itb.end(), 2) << "\n";

	// std::cout << std::is_sorted(itb.begin(), itb.end(), isLess<int>) << "\n";

	return 0;
}