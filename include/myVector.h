#pragma once
#include <memory>

template <class T, class Allocator = std::allocator<T> >
class myVector{
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef std::size_t size_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;


public:

};

template <class T>
class myAllocator{
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef const reference const_reference;
	typedef const pointer const_pointer;
	typedef std::size_t size_type;
	typedef int difference_type;
public:
	pointer allocate(size_type n);
	pointer deallocate(pointer ptr, size_type n);

	myAllocator(){};
	myAllocator(const myAllocator<T>& other){};

	template <class U1, class U2>
	friend bool operator==(const myAllocator<U1>& left, const myAllocator<U2>& right){
		return sizeof(U1) == sizeof(U2);
	};

	template <class U1, class U2>
	friend bool operator==(const myAllocator<U1>& left, const myAllocator<U2>& right){
		return !(left == right);
	};

};

