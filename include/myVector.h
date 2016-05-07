#pragma once
#include <initializer_list>
#include <memory>
#include <exception>
#define MAX_SIZE_START 10

template <class T, class Allocator = std::allocator<T> >
class myVector{
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef std::size_t size_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef value_type* iterator;

public:
	myVector(Allocator& _alloc = Allocator()){
		alloc = _alloc;
		first = NULL;
		l = 0;
		max_size = MAX_SIZE_START;
	};

	myVector(const myVector<value_type>& other, Allocator& _alloc = Allocator()){
		alloc = _alloc;
		max_size = other.max_size;
		first = alloc.allocate(max_size);
		l = other.l;
		for (int i = 0; i < l; i++){
			first[i] = other.first[i];
		}

	};

	myVector(std::initializer_list<value_type>& list, Allocator& _alloc = Allocator()){
		alloc = _alloc;
		max_size = list.size() * 2;
		first = alloc.allocate(max_size);
		l = list.size();
		for (int i = 0; i < l; i++){
			first[i] = list.begin()[i];
		}
	};

	myVector(iterator _first, iterator _last, Allocator& _alloc = Allocator()){
		alloc = _alloc;
		max_size = (_last - _first + 1) * 2;
		first = alloc.allocate(max_size);
		l = _last - _first + 1;
		for (int i = 0; i < l; i++){
			first[i] = _first[i];
		}
	};

	myVector(size_type count, Allocator& _alloc = Allocator()){
		alloc = _alloc;
		l = count;
		max_size = count * 2;
		first = alloc.allocate(max_size);
		alloc.construct(first, l);
	}


	myVector(){
		alloc = Allocator();
		first = NULL;
		l = 0;
		max_size = MAX_SIZE_START;
	};

	myVector(const myVector<value_type>& other){
		alloc = Allocator();
		max_size = other.max_size;
		first = alloc.allocate(max_size);
		l = other.l;
		for (int i = 0; i < l; i++){
			first[i] = other.first[i];
		}

	};

	myVector(std::initializer_list<value_type>& list){
		alloc = Allocator();
		max_size = list.size() * 2;
		first = alloc.allocate(max_size);
		l = list.size();
		for (int i = 0; i < l; i++){
			first[i] = list.begin()[i];
		}
	};

	template<class InputIterator>
	myVector(InputIterator _first, InputIterator _last){
		alloc = Allocator();
		max_size = (_last - _first + 1) * 2;
		first = alloc.allocate(max_size);
		l = _last - _first + 1;
		for (int i = 0; i < l; i++){
			first[i] = _first[i];
		}
	};

	myVector(size_type count){
		alloc = Allocator();
		l = count;
		max_size = count * 2;
		first = alloc.allocate(max_size);
		alloc.construct(first, l);
	}

	~myVector(){
		clear();
	}

	myVector<T, Allocator>& operator=(const myVector<T, Allocator>& other){
		clear();
		alloc = other.alloc;
		first = alloc.allocate(other.max_size);
		l = other.l;
		for (int i = 0; i < l; i++){
			first[i] = other.first[i];
		}
		return this;
	}

	myVector<T, Allocator>& operator=(std::initializer_list<T>& other){
		clear();
		max_size = other.size() * 2;
		first = alloc.allocate(max_size);
		l = other.size();
		for (int i = 0; i < l; i++){
			first[i] = other.begin()[i];
		}
		return this;
	}

	myVector<T, Allocator>& assign(size_type count, const T& value){
		clear();
		max_size = count * 2;
		first = alloc.allocate(max_size);
		alloc.construct(first, count);
		l = count;
		for (int i = 0; i < l; i++){
			first[i] = value;
		}
		return this;
	}

	myVector<T, Allocator>& assign(std::initializer_list<T> list){
		clear();
		max_size = list.size() * 2;
		first = alloc.allocate(max_size);
		alloc.construct(first, list.size());
		l = list.size();
		for (int i = 0; i < l; i++){
			first[i] = list.begin()[i];
		}
		return this;
	}

	template<class InputIterator>
	myVector<T, Allocator>& assign(InputIterator _first, InputIterator _last){
		clear();
		l = _last - _first + 1;
		max_size = l * 2;
		first = alloc.allocate(max_size);
		alloc.construct(first, l);
		for (int i = 0; i < l; i++){
			first[i] = _first[i];
		}
		return this;
	}

	myVector<T, Allocator>& clear(){
		for (int i = 0; i < l; i++){
			alloc.destroy(&first[i]);
		}
		alloc.deallocate(first, max_size);
		first = NULL;
		l = 0;
		return this;
	}

	reference at(size_type pos){
		if (pos >= l){
			throw std::out_of_range();
		}
		return first[pos];
	}

	const_reference at(size_type pos) const{
		if (pos >= l){
			throw std::out_of_range();
		}
		return first[pos];
	}

	reference operator[](size_type){
		return first[pos];
	}

	const_reference operator[](size_type) const{
		return first[pos];
	}

	reference front(){
		return first[0];
	}

	reference back(){
		return first[l - 1];
	}

	Allocator get_allocator(){
		return alloc;
	}




private:

	allocator_type alloc;
	pointer first;
	size_type l;
	size_type max_size;
};

