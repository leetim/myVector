#pragma once
#include <myAllocator.h>
#include <myVector.h>
#include <iostream>
#define MY_STRING_BUF_SIZE 10

template<class T, class Allocator = myAllocator<T> >
class myBasicString{
public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef std::size_t size_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef myBasicString<T, Allocator> self_type;

	myBasicString(): arr(){
		arr.emplace_back();
	}

	myBasicString(const value_type p[]): arr(){
		size_type l = get_length(p);
		arr.assign(&p[0], &p[l]);
		arr.push_back(T());
	}

	myBasicString(const self_type &other){
		arr = other.arr;
	}

	void operator=(const self_type& other){
		arr = other.arr;
	}

	void operator=(const value_type other[]){
		size_type l = get_length(other);
		arr.assign(other, &other[l+1]);
	}

	reference operator[](int i){
		return arr[i];
	}

	const_reference operator[](int i) const{
		return arr[i];
	}

	size_type size() const{
		return arr.size() - 1;
	}

	iterator begin(){
		return arr.begin();
	}

	iterator end(){
		return arr.end() - 1;
	}

	const_iterator cbegin() const{
		return arr.cbegin();
	}

	const_iterator cend() const{
		return arr.cend() - 1;
	}

	iterator insert(iterator pos, self_type& other){
		// std::cout << 3 << std::endl;
		return arr.insert(pos, other.begin(), other.end());
	}

	iterator insert(iterator pos, const value_type other[]){
		size_type l = get_length(other);
		arr.insert(pos, other, &other[l]);
		return pos;
	}

	self_type operator+(self_type& other){
		self_type s = *this;
		// std::cout << arr.capacity() << std::endl;
		s.insert(s.end(), other);
		return s;
	}

	iterator find(const self_type& other){
		for (iterator i = begin(); (i != end()) && ((size_type)(end() - i) >= other.size()); i++){
			try{
				for (size_type j = 0; j < other.size(); j++){
					if (i[j] != other[j]){
						throw false;
					}
				}
				return i;
			}
			catch (bool e){

			}
		}
		return end();
	}

	template<class T2, class Alloc>
	friend bool operator==(const myBasicString<T2, Alloc>& l, const myBasicString<T2, Alloc>& r);
	template<class T2, class Alloc>
	friend bool operator<(const myBasicString<T2, Alloc>& l, const myBasicString<T2, Alloc>& r);

	template <class Traits>
	friend std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& os,
		const self_type& str);

	template <class Traits>
	friend std::basic_istream<T, Traits>& operator>>(std::basic_ostream<T, Traits>& os,
		const self_type& str);

private:

	static size_type get_length(const value_type p[]){
		size_type l = 0;
		while (p[l] != T()){
			l++;
		}
		return l;
	}

	myVector<T, Allocator> arr;
};

typedef myBasicString<char> myString;



template<class T, class Alloc>
bool operator==(const myBasicString<T, Alloc>& l, const myBasicString<T, Alloc>& r){
	if (l.size() != r.size()){
			return false;
	}
	for (std::size_t i = 0; i < l.size(); i++){
		if (l[i] != r[i]){
			return false;
		}
	}
	return true;
}

template<class T, class Alloc>
bool operator<(const myBasicString<T, Alloc>& l, const myBasicString<T, Alloc>& r){
	std::size_t n = (l.size() < r.size()) ? l.size() : r.size();
	for (std::size_t i = 0; i < n; i++){
		if (l[i] != r[i]){
			return l[i] < r[i];
		}
	}
	return l.size() < r.size();
}

// template <class T, class Traits, class Allocator>
// std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& os, const myBasicString<T, Allocator>& str){
// 	os << str.begin();
// }
//
// template <class T, class Traits, class Allocator>
// std::basic_istream<T, Traits>& operator>>(std::basic_ostream<T, Traits>& is, const myBasicString<T, Allocator>& str){
//
// }
