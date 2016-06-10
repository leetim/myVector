#pragma once
#include <stdlib.h>
#include <iostream>

template <class T>
struct LT{
	bool operator()(const T& a, const T& b){
		return a < b;
	}
};

template <typename T>
LT<T> getLT(T exampl){
	return LT<T>();
}

typedef std::size_t size_type;


template <class ITERATOR, class Compare>
void mysort(ITERATOR begin, ITERATOR end, Compare comp){
	size_type count = end - begin;
	if (count == 2){
		if (!comp(*begin, begin[1])){
			std::swap(*begin, begin[1]);
		}
		return;
	}
	if (count <= 1){
		return;
	}
	ITERATOR temp = begin + (count / 2);
	ITERATOR mid = end - 1;
	std::swap(end[-1], *temp);
	temp = end - 1;
	for (ITERATOR i = begin; i != mid; ){
		if (comp(*i, *temp)){
			i++;
		}
		else{
			mid--;
			std::swap(*mid, *i);
		}
	}
	mysort(begin, mid, comp);
	mysort(mid, end, comp);
}

template <class ITERATOR>
void mysort(ITERATOR begin, ITERATOR end){
	mysort(begin, end, getLT(*begin));
}