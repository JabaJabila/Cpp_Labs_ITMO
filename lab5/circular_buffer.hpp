#pragma once

#include <memory>
#include <stdexcept>
#include <initializer_list>

template<class T = int, class Allocator = std::allocator<T>>
class circular_buffer {
public:
	circular_buffer(unsigned capacity = 0, const Allocator& alloc = Allocator())
	: capacity_(capacity + 1),
	  size_(0),
	  first_(capacity),
	  last_(0),
	  alloc_(alloc),
	  data_(alloc_.allocate(capacity + 1)) {}

	circular_buffer(std::initializer_list<T> list, const Allocator& alloc = Allocator())
	: capacity_(list.size() + 1),
	  size_(0),
	  first_(list.size()),
	  last_(0),
	  alloc_(alloc),
	  data_(alloc_.allocate(list.size() + 1)) {
	  	for (auto it = std::begin(list); it != std::end(list); ++it)
        	push_back(*it);
	  }

	circular_buffer(const circular_buffer<T> & other)
	: capacity_(other.capacity_),
	  size_(other.size_),
	  first_(other.first_),
	  last_(other.last_),
	  alloc_(other.alloc_),
	  data_(alloc_.allocate(other.capacity_)) {
		for (unsigned i = 0; i < capacity_; ++i)
			data_[i] = other.data_[i];
	}

	circular_buffer & operator=(const circular_buffer<T> & other) {
		if (other != *this) {
			for (unsigned i = 0; i < capacity_; ++i)
				alloc_.destroy(&(data_[i]));
			alloc_.deallocate(data_, capacity_);
			size_ = other.size_;
			first_ = other.first_,
			capacity_ = other.capacity_;
			last_ = other.last_;
			data_ = alloc_.allocate(capacity_);
			for (unsigned i = 0; i < capacity_; ++i)
				data_[i] = other.data_[i];
		}
		return *this;
	}

	~circular_buffer() {
		for (unsigned i = 0; i < capacity_; ++i)
			alloc_.destroy(&(data_[i]));
		alloc_.deallocate(data_, capacity_);
	}

	bool operator==(const circular_buffer<T> & other) const {
		if (size_ == other.size_ && capacity_ == other.capacity_) {
			for (unsigned i = 0; i < size_; ++i) {
				if (operator[](i) != other[i])
					return false;
			}
			return true;
		}
		return false;
	}

	bool operator!=(const circular_buffer<T> & other) const {return !(other == *this);}

	T& operator[] (const unsigned index) {
		if (index > size_ - 1)
			throw std::out_of_range("THIS INDEX IS OUT OF RANGE!\n");
		return data_[(first_ + index + 1) % capacity_];
	}
	const T& operator[] (const unsigned index) const {
		if (index > size_ - 1)
			throw std::out_of_range("THIS INDEX IS OUT OF RANGE!\n");
		return data_[(first_ + index + 1) % capacity_];
	}

	void push_back(const T& element) {
		if (last_ == first_) {
			if (first_ == capacity_ - 1)
				first_ = 0;
			else
				++first_;
		}
		data_[last_] = element;
		++last_;
		if (last_ == capacity_)
			last_ = 0;
		size_ = size_ == capacity_ - 1 ? size_ : size_ + 1;
	}

	void push_front(const T& element) {
		if (last_ == first_) {
			if (last_ == 0)
				last_ = capacity_ - 1;
			else
				--last_;
		}
		data_[first_] = element;
		if (first_ == 0)
			first_ = capacity_ - 1;
		else
			--first_;
		size_ = size_ == capacity_ - 1 ? size_ : size_ + 1;
	}

	void pop_back() {
		if (size_ == 0)
			throw std::out_of_range("NO DATA IN CONTAINER!\n");
		--size_;
		alloc_.destroy(&(data_[last_]));
		if (last_ == 0) {
			last_ = capacity_ - 1;
		}
		else
			--last_;
	}

	void pop_front() {
		if (size_ == 0)
			throw std::out_of_range("NO DATA IN CONTAINER!\n");
		--size_;
		alloc_.destroy(&(data_[first_]));
		++first_;
		if (first_ == capacity_) {
			first_ = 0;
		}	
	}

	void clear() {
		for (unsigned i = 0; i < capacity_; ++i)
			alloc_.destroy(&(data_[i]));
		size_ = 0;
		first_ = capacity_ - 1;
		last_ = 0;
	}

	void change_capacity(unsigned new_capacity) {
		++new_capacity;
		if (capacity_ == new_capacity)
			return;
		if (new_capacity < size_ + 1)
			throw std::bad_alloc();
		T * new_data = alloc_.allocate(new_capacity);
		for (unsigned i = 0; i < size_; ++i)
			new_data[i] = operator[](i);
		for (unsigned i = 0; i < capacity_; ++i)
			alloc_.destroy(&(data_[i]));
		alloc_.deallocate(data_, capacity_);
		first_ = new_capacity - 1;
		last_ = size_;
		capacity_ = new_capacity;
		data_ = new_data;
	}

	void shrink_to_fit() {change_capacity(size_);}

	unsigned capacity() const {return capacity_ - 1;}
	unsigned size() const {return size_;}

	const T& front() const {
		if (size_ != 0) {
			if (first_ == capacity_ - 1)
				return data_[0];
			return data_[first_ + 1];
		}
		throw std::out_of_range("NO DATA IN CONTAINER!\n");
	}

	const T& back() const {
		if (size_ != 0)
			if (last_ == 0)
				return data_[capacity_- 1];
			return data_[last_ - 1];
		throw std::out_of_range("NO DATA IN CONTAINER!\n");
	}

	T& front() {
		if (size_ != 0) {
			if (first_ == capacity_ - 1)
				return data_[0];
			return data_[first_ + 1];
		}
		throw std::out_of_range("NO DATA IN CONTAINER!\n");
	}

	T& back() {
		if (size_ != 0)
			if (last_ == 0)
				return data_[capacity_- 1];
			return data_[last_ - 1];
		throw std::out_of_range("NO DATA IN CONTAINER!\n");
	}

	bool empty() const {
		return size_ == 0;
	}

	class iterator : public std::iterator<std::random_access_iterator_tag, T> {
	public:
		using diff_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;

		iterator(T* elem, T* left, T* right, T* pivot) : iterator_(elem), left_border_(left), right_border_(right), pivot_(pivot) {}

		iterator& operator++() {
			if (iterator_ == right_border_)
				iterator_ = left_border_;
			else
				++iterator_;	
			return *this;
		}

		iterator operator++(int) {iterator tmp = *this; ++(*this); return tmp;}

		iterator& operator--() {
			if (iterator_ == left_border_)
				iterator_ = right_border_;
			else
				--iterator_;
			return *this;
		}

		iterator operator--(int) {iterator tmp = *this; --(*this); return tmp;}

		iterator& operator+=(diff_type d) {
			if (d < 0)
				return *this -= (-d);
			if (right_border_ - iterator_ < d) {
				diff_type t = right_border_ - iterator_ + 1;
				iterator_ = left_border_ + (d - t);
				return *this;
			}
			iterator_ += d;
			return *this;
		}

		iterator& operator-=(diff_type d) {
			if (d < 0)
				return *this += (-d);
			if (iterator_ - left_border_ < d) {
				diff_type t = (iterator_ - left_border_) + 1;
				iterator_ = right_border_ - (d - t);
				return *this;
			}
			iterator_ -= d;
			return *this;
		}

		diff_type operator-(const iterator& other) const {
			if (iterator_ <= pivot_ && other.iterator_ > pivot_) {
				diff_type t = iterator_ - left_border_ + 1;
				return t + right_border_ - other.iterator_;
			}
			if (iterator_ > pivot_ && other.iterator_ <= pivot_) {
				diff_type t = right_border_ - iterator_;
				return -(other - *this);
			}
			return iterator_ - other.iterator_;
		}

		friend iterator operator+(const iterator& iter, const int num) {iterator tmp = iter; return tmp += num;}
		friend iterator operator+(const int num, const iterator& iter) {iterator tmp = iter; return tmp += num;}
		friend iterator operator-(const iterator& iter, const int num) {iterator tmp = iter; return tmp -= num;}

		T& operator*() {return *iterator_;}
		T* operator->() {return iterator_;}
		T& operator[](const unsigned num) {return *(*this + num);}

		bool operator==(const iterator& other) const {return iterator_ == other.iterator_;}
		bool operator!=(const iterator& other) const {return iterator_ != other.iterator_;}
		bool operator<(const iterator& other) const {
			if (iterator_ > pivot_ && other.iterator_ < pivot_)
				return true;
			if ((iterator_ > pivot_ && other.iterator_ > pivot_) || (iterator_ < pivot_ && other.iterator_ < pivot_))
				return (iterator_ < other.iterator_);
			return false;
		}
		bool operator>(const iterator& other) const {return (other < *this);}
		bool operator<=(const iterator& other) const {return (*this < other || *this == other);}
		bool operator>=(const iterator& other) const {return (other < *this || *this == other);}

	private:
		T* iterator_;
		T* left_border_;
		T* right_border_;
		T* pivot_;
	};

	iterator begin() const {return iterator(&data_[first_ == capacity_ - 1 ? 0 : first_ + 1], data_, data_ + (capacity_ - 1), data_ + last_);}
	iterator end() const {return iterator(&data_[last_], data_, data_ + (capacity_ - 1), data_ + last_);}

	T* get_left_border() const {return data_;}
	T* get_right_border() const {return data_ + (capacity_ - 1);}
	T* get_pivot() const {return data_ + last_;}


private:
	Allocator alloc_;
	T * data_;
	unsigned size_;
	unsigned capacity_;
	unsigned first_;
	unsigned last_;
};