#pragma once
#include <initializer_list>
#include <memory>
#include <exception>
#include <stdexcept>
#include <utility>
#include <iostream>
#define MAX_SIZE_START 10

template <class T, class Allocator = std::allocator<T> >
class myVector{
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

	// myVector(Allocator& _alloc = Allocator()){
	// 	alloc = _alloc;
	// 	first = NULL;
	// 	l = 0;
	// 	reserved_memory = MAX_SIZE_START;
	// };

	// myVector(const myVector<value_type>& other, Allocator& _alloc = Allocator()){
	// 	alloc = _alloc;
	// 	reserved_memory = other.reserved_memory;
	// 	first = alloc.allocate(reserved_memory);
	// 	l = other.l;
	// 	for (int i = 0; i < l; i++){
	// 		first[i] = other.first[i];
	// 	}

	// };

	// myVector(std::initializer_list<value_type>& list, Allocator& _alloc = Allocator()){
	// 	alloc = _alloc;
	// 	reserved_memory = list.size() * 2;
	// 	first = alloc.allocate(reserved_memory);
	// 	l = list.size();
	// 	for (int i = 0; i < l; i++){
	// 		first[i] = list.begin()[i];
	// 	}
	// };

	// myVector(iterator _first, iterator _last, Allocator& _alloc = Allocator()){
	// 	alloc = _alloc;
	// 	reserved_memory = (_last - _first + 1) * 2;
	// 	first = alloc.allocate(reserved_memory);
	// 	l = _last - _first + 1;
	// 	for (int i = 0; i < l; i++){
	// 		first[i] = _first[i];
	// 	}
	// };

	// myVector(size_type count, Allocator& _alloc = Allocator()){
	// 	alloc = _alloc;
	// 	l = count;
	// 	reserved_memory = count * 2;
	// 	first = alloc.allocate(reserved_memory);
	// 	for (int i = 0; i < l; i++){
	// 		alloc.construct(&first[i], T());
	// 	}
	// }


	myVector(){
		alloc = Allocator();
		first = alloc.allocate(MAX_SIZE_START);
		l = 0;
		reserved_memory = MAX_SIZE_START;
	};

	myVector(const myVector<value_type>& other){
		alloc = Allocator();
		reserved_memory = other.reserved_memory;
		first = alloc.allocate(reserved_memory);
		l = other.l;
		for (size_type i = 0; i < l; i++){
			first[i] = other.first[i];
		}

	};

	myVector(const std::initializer_list<value_type>& list){
		alloc = Allocator();
		reserved_memory = list.size() * 2;
		first = alloc.allocate(reserved_memory);
		l = list.size();
		for (size_type i = 0; i < l; i++){
			first[i] = list.begin()[i];
		}
	};

	template<class InputIterator>
	myVector(InputIterator _first, InputIterator _last){
		alloc = Allocator();
		reserved_memory = (_last - _first) * 2;
		first = alloc.allocate(reserved_memory);
		l = _last - _first;
		for (size_type i = 0; i < l; i++){
			first[i] = _first[i];
		}
	};

	myVector(size_type count){
		alloc = Allocator();
		l = count;
		reserved_memory = count * 2;
		first = alloc.allocate(reserved_memory);
		for (size_type i = 0; i < l; i++){
			alloc.construct(&first[i], T());
		}
	}

	~myVector(){
		clear();
		alloc.deallocate(first, reserved_memory);
	}

	void operator=(const myVector<T, Allocator>& other){
		clear();
		alloc.deallocate(first, reserved_memory);
		alloc = other.alloc;
		reserved_memory = other.reserved_memory;
		first = alloc.allocate(other.reserved_memory);
		l = other.l;
		for (size_type i = 0; i < l; i++){
			alloc.construct(&first[i], other.first[i]);
		}
	}

	void operator=(std::initializer_list<T>& other){
		assign(other);
	}

	void assign(size_type count, const T& value){
		clear();
		reserved_memory = count * 2;
		first = alloc.allocate(reserved_memory);
		l = count;
		for (size_type i = 0; i < l; i++){
			alloc.construct(&first[i], value);
		}
	}

	void assign(std::initializer_list<T> list){
		clear();
		reserved_memory = list.size() * 2;
		first = alloc.allocate(reserved_memory);
		l = list.size();
		for (size_type i = 0; i < l; i++){
			alloc.construct(&first[i], list.begin()[i]);
		}
	}

	template<class InputIt>
	void assign(InputIt _first, InputIt _last){
		clear();
		l = _last - _first;
		reserved_memory = l * 2;
		first = alloc.allocate(reserved_memory);
		for (size_type i = 0; i < l; i++){
			alloc.construct(&first[i], _first[i]);
		}
	}

	void clear(){
		for (size_type i = 0; i < l; i++){
			alloc.destroy(&first[i]);
		}
		l = 0;
	}

	reference at(size_type pos){
		if (pos >= l){
			throw std::out_of_range("123");
		}
		return first[pos];
	}

	// const_reference at(size_type pos) const{
	// 	if (pos >= l){
	// 		throw std::out_of_range();
	// 	}
	// 	return first[pos];
	// }

	reference operator[](size_type pos){
		return first[pos];
	}

	// const_reference operator[](size_type pos) const{
	// 	return first[pos];
	// }

	reference front(){
		return first[0];
	}

	reference back(){
		return first[l - 1];
	}

	// const_reference front() const{
	// 	return first[0];
	// }

	// const_reference back() const{
	// 	return first[l - 1];
	// }

	iterator begin(){
		return first;
	}

	iterator end(){
		return first + l;
	}

	// const_iterator cbegin(){
	// 	return first;
	// }

	// const_iterator cend(){
	// 	return first + l;
	// }

	Allocator get_allocator(){
		return alloc;
	}

	bool empty(){
		return l == 0;
	}

	size_type size(){
		return l;
	}

	size_type capacity(){
		return reserved_memory;
	}

	void reserve(size_type count){
		if (reserved_memory >= count){
			return;
		}
		pointer temp = alloc.allocate(count);
		for (size_type i = 0; i < l; i++){
			alloc.construct(&temp[i], first[i]);
			alloc.destroy(&first[i]);
		}
		alloc.deallocate(first, reserved_memory);
		reserved_memory = count;
		first = temp;
	}

	iterator insert(iterator pos, const T& value){
		if (l + 1 > reserved_memory){
			pointer temp = alloc.allocate(reserved_memory*2);
			size_type n = pos - begin();
			for (size_type i = 0; i < n; i++){
				alloc.construct(&temp[i], first[i]);
				alloc.destroy(&first[i]);
			}
			alloc.construct(&temp[n], value);
			for (size_type i = n; i < l; i++){
				alloc.construct(&temp[i + 1], first[i]);
				alloc.destroy(&first[i]);
			}
			alloc.deallocate(first, reserved_memory);
			reserved_memory *= 2;
			first = temp;
			l++;
			return &temp[n];
		}
		for (iterator i = end() - 1; i >= pos; i--){
			alloc.construct(i + 1, *i);
			alloc.destroy(i);
		}
		alloc.construct(pos, value);
		l++;
		return pos;
	}

	iterator insert(iterator pos, size_type count, const T& value){
		size_type new_reserved = reserved_memory;
		while (l + count > new_reserved){
			new_reserved *= 2;
		}
		if (l + count > reserved_memory){
			pointer temp = alloc.allocate(new_reserved);
			size_type n = pos - begin();
			for (size_type i = 0; i < n; i++){
				alloc.construct(&temp[i], first[i]);
				alloc.destroy(&first[i]);
			}
			for (size_type i = 0; i < count; i++){
				alloc.construct(&temp[n + i], value);
			}
			for (size_type i = n; i < l; i++){
				alloc.construct(&temp[i + count], first[i]);
				alloc.destroy(&first[i]);
			}
			alloc.deallocate(first, reserved_memory);
			reserved_memory = new_reserved;
			first = temp;
			l += count;
			return &temp[n];
		}
		for (iterator i = end() - 1; i >= pos; i--){
			alloc.construct(i + count, *i);
			alloc.destroy(i);
		}
		for (size_type i = 0; i < count;i++){
			alloc.construct(&pos[i], value);
		}
		l += count;
		return pos;
	}

	template<class InputIt>
	iterator insert(iterator pos, InputIt _begin, InputIt _end){
		size_type count = _end - _begin;
		size_type new_reserved = reserved_memory;
		while (l + count > new_reserved){
			new_reserved *= 2;
		}
		if (l + count > reserved_memory){
			pointer temp = alloc.allocate(new_reserved);
			size_type n = pos - begin();
			for (size_type i = 0; i < n; i++){
				alloc.construct(&temp[i], first[i]);
				alloc.destroy(&first[i]);
			}
			for (size_type i = 0; i < count; i++){
				alloc.construct(&temp[n + i], _begin[i]);
			}
			for (size_type i = n; i < l; i++){
				alloc.construct(&temp[i + count], first[i]);
				alloc.destroy(&first[i]);
			}
			alloc.deallocate(first, reserved_memory);
			reserved_memory = new_reserved;
			first = temp;
			l += count;
			return &temp[n];
		}
		for (iterator i = end() - 1; i >= pos; i--){
			alloc.construct(i + count, *i);
			alloc.destroy(i);
		}
		for (size_type i = 0; i < count;i++){
			alloc.construct(&pos[i], _begin[i]);
		}
		l += count;
		return pos;
	}

	iterator insert(iterator pos, const std::initializer_list<T>& list){
		size_type count = list.size();
		size_type new_reserved = reserved_memory;
		while (l + count > new_reserved){
			new_reserved *= 2;
		}
		if (l + count > reserved_memory){
			pointer temp = alloc.allocate(new_reserved);
			size_type n = pos - begin();
			for (size_type i = 0; i < n; i++){
				alloc.construct(&temp[i], first[i]);
				alloc.destroy(&first[i]);
			}
			for (size_type i = 0; i < count; i++){
				alloc.construct(&temp[n + i], list.begin()[i]);
			}
			for (size_type i = n; i < l; i++){
				alloc.construct(&temp[i + count], first[i]);
				alloc.destroy(&first[i]);
			}
			alloc.deallocate(first, reserved_memory);
			reserved_memory = new_reserved;
			first = temp;
			l += count;
			return &temp[n];
		}
		for (iterator i = end() - 1; i >= pos; i--){
			alloc.construct(i + count, *i);
			alloc.destroy(i);
		}
		for (size_type i = 0; i < count;i++){
			alloc.construct(&pos[i], list.begin()[i]);
		}
		l += count;
		return pos;

	}

	iterator erase(iterator pos){
		alloc.destroy(pos);
		for (iterator i = pos + 1; i < end(); i++){
			alloc.construct(i - 1, *i);
			alloc.destroy(i);
		}
		l--;
		return pos;
	}

	iterator erase(iterator _begin, iterator _end){
		size_type count = _end - _begin;
		for (size_type i = 0; i < count; i++){
			alloc.destroy(&_begin[i]);
		}
		for (iterator i = _begin + count; i < end(); i++){
			alloc.construct(i - count, *i);
			alloc.destroy(i);
		}
		l -= count;
		return _begin;
	}

	void push_back(const T& value){
		if (l + 1 > reserved_memory){
			reserve(reserved_memory * 2);
		}
		alloc.construct(&first[l], value);
		l++;
	}

	template <class... Args>
	void emplace_back(Args&&... args){
		if (l + 1 > reserved_memory){
			reserve(reserved_memory * 2);
		}
		alloc.construct(&first[l], args...);
		l++;		
	}

	// template <class... Args>
	// iterator emplace(iterator pos, Args&&... args){
	// 	if (l + 1 > reserved_memory){
	// 		reserve(reserved_memory * 2);
	// 	}
	// 	for (iterator i = end() - 1; i >= pos; i--){
	// 		alloc.construct(i + 1, *i);
	// 		alloc.destroy(i);
	// 	}
	// 	alloc.construct(pos, args...);
	// 	l++;
	// 	return pos;
	// }

	void pop_back(){
		alloc.destroy(&back());
		l--;		
	}

	void resize(size_type count, const T& value = T()){
		if (count > reserved_memory){
			reserve(reserved_memory * 2);
		}
		for (size_type i = l; i < count; i++){
			alloc.construct(&first[i], value);
		}
		for (size_type i = count; i < l; i++){
			alloc.destroy(&first[i]);
		}
		l = count;
	}


private:
	allocator_type alloc;
	pointer first;
	size_type l;
	size_type reserved_memory;
};

