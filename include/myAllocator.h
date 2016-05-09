#pragma once

template <class T>
class myAllocator{
public:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef const T& const_reference;
	typedef const T* const_pointer;
	typedef std::size_t size_type;
	typedef int difference_type;

	myAllocator() throw(){};
	myAllocator(const myAllocator<T>& other) throw(){};
	~myAllocator() throw(){};

	pointer allocate(size_type n){
		return static_cast<pointer>(::operator new(n * sizeof(value_type)));
	}

	void deallocate(pointer ptr, size_type n){
		::operator delete(ptr);
	}

	template<class... Args>
	void construct(pointer item, Args&&... args){
		item = new((void *)item) T(args...);
	}

	void destroy(pointer item){
		item->~T();
	}

	void operator=(const myAllocator<T>& other){}

	template <class U1, class U2>
	friend bool operator==(const myAllocator<U1>& left, const myAllocator<U2>& right);
	template <class U1, class U2>
	friend bool operator!=(const myAllocator<U1>& left, const myAllocator<U2>& right);

};


template <class U1, class U2>
bool operator==(const myAllocator<U1>& left, const myAllocator<U2>& right){
	return sizeof(U1) == sizeof(U2);
};

template <class U1, class U2>
bool operator!=(const myAllocator<U1>& left, const myAllocator<U2>& right){
	return !(left == right);
};
