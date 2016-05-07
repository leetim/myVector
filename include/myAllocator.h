#pragma once

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

	myAllocator(){};
	myAllocator(const myAllocator<T>& other){};

	pointer allocate(size_type n){
		return static_cast<pointer>(::operator new(n * sizeof(value_type)));
	}

	void deallocate(pointer ptr, size_type n){
		::operator delete(ptr);
	}

	void construct(pointer item){
		item = new value_type();
	}

	template<typename U, typename... ARGS>
	void construct(U* item, ARGS*... args){
		construct(item);
		construct(args...);
	}

	void construct(pointer& item, size_type n){
		for (size_type i = 0; i < n; i++){
			item[i] = value_type();
		}
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
