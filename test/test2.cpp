#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <myVector.h>
#include <myAllocator.h>
#include <algorithm>
#include <iostream>
#include <initializer_list>

using namespace std;

class some_class{
public:
	some_class(){
		value = -1;
	};


	some_class(int v){
		value = v;
	};

	void set_value(int n){
		value = n;
	};

	int get_value(){
		return value;
	};
private:
	int value;
	int value2;
	int value3;
};

class VectorTest : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
	typedef myVector<int> vec_int;
	typedef myVector<some_class> vec_some;
	myVector<int> iv;
	myVector<some_class> sv;
};

TEST_F(VectorTest, vector_constructors_int){
	vec_int a1;
	vec_int a2(5);
	vec_int a3 = {1, 2, 3, 4};
	vec_int a4({1, 2, 3, 4});
	vec_int a5(a4);
	vec_int a6 = a4;
	vec_int a7(a3.begin(), a3.end());
	ASSERT_EQ(a1.size(), (size_t)0);
	ASSERT_EQ(a2.size(), (size_t)5);
	ASSERT_EQ(a2[0], int());
	ASSERT_EQ(a3.size(), (size_t)4);
	ASSERT_EQ(a3[0], 1);
	ASSERT_EQ(a3[1], 2);
	ASSERT_EQ(a3[2], 3);
	ASSERT_EQ(a3[3], 4);
	ASSERT_EQ(a5.size(), a4.size());
	ASSERT_EQ(a5.front(), a4.front());
	ASSERT_EQ(a5.back(), a4.back());
	ASSERT_EQ(a7.size(), a3.size());
}

TEST_F(VectorTest, reference_assign_int){
	vec_int a = {1, 2, 3, 4, 5, 6};
	vec_int b;
	b = a;
	ASSERT_EQ(b.size(), a.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], b[i]);
		ASSERT_EQ(a[i], (int)(i + 1));
		ASSERT_EQ(a.at(i), (int)(i + 1));
	}
	try{
		a.at(7);
		throw 2;
	}
	catch(int e){
		ASSERT_TRUE(false);
	}
	catch(std::out_of_range const& exc){
		ASSERT_TRUE(true);
	}
	ASSERT_EQ(a.back(), 6);
	ASSERT_EQ(a.front(), 1);
	b.assign((size_t)3, 4);
	ASSERT_EQ(b.size(), (size_t)3);
	for (size_t i = 0; i < b.size(); i++){
		ASSERT_EQ(b[i], 4);
	}
	b.assign({0, 1, 2, 3});
	ASSERT_EQ(b.size(), (size_t)4);
	for (size_t i = 0; i < b.size(); i++){
		ASSERT_EQ(b[i], (int)i);
	}
	b.assign(a.begin(), a.begin() + 5);
	ASSERT_EQ(b.size(), (size_t)5);
	for (size_t i = 0; i < b.size(); i++){
		ASSERT_EQ(b[i], (int)(i + 1));
	}
	ASSERT_FALSE(b.empty());
	b.clear();
	ASSERT_TRUE(b.empty());
}

TEST_F(VectorTest, vector_assign_int_test){
	vec_int a = {1, 2, 3, 4};
	vec_int temp;
	temp = a;
	ASSERT_EQ(a.size(), temp.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], temp[i]);
	}

	temp.clear();
	temp = {1, 2, 3, 4};
	ASSERT_EQ(a.size(), temp.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], temp[i]);
	}

	temp.clear();
	temp.assign((size_t)5, 4);
	ASSERT_EQ(temp.size(), (size_t)5);
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(4, temp[i]);
	}

	temp.clear();
	temp.assign(a.begin(), a.end());
	ASSERT_EQ(a.size(), temp.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], temp[i]);
	}
}

TEST_F(VectorTest, vector_insert_int_test){
	vec_int a = {1, 2, 3, 4, 5};
	vec_int::iterator i = a.begin() + 2;
	a.insert(i, 6);
	ASSERT_EQ(a.size(), (size_t)6);
	ASSERT_EQ(a[0], 1);
	ASSERT_EQ(a[1], 2);
	ASSERT_EQ(a[2], 6);
	ASSERT_EQ(a[3], 3);
	ASSERT_EQ(a[4], 4);
	ASSERT_EQ(a[5], 5);

	a = {1, 2, 3, 4, 5};
	i = a.begin() + 2;
	a.insert(i, (size_t)3, 6);
	ASSERT_EQ(a.size(), (size_t)8);
	ASSERT_EQ(a[0], 1);
	ASSERT_EQ(a[1], 2);
	ASSERT_EQ(a[2], 6);
	ASSERT_EQ(a[3], 6);
	ASSERT_EQ(a[4], 6);
	ASSERT_EQ(a[5], 3);
	ASSERT_EQ(a[6], 4);
	ASSERT_EQ(a[7], 5);

	a = {1, 2, 3, 4, 5};
	i = a.begin() + 2;
	vec_int b = {7, 8, 9};
	a.insert(i, b.begin(), b.end());
	ASSERT_EQ(a.size(), (size_t)8);
	ASSERT_EQ(a[0], 1);
	ASSERT_EQ(a[1], 2);
	ASSERT_EQ(a[2], 7);
	ASSERT_EQ(a[3], 8);
	ASSERT_EQ(a[4], 9);
	ASSERT_EQ(a[5], 3);
	ASSERT_EQ(a[6], 4);
	ASSERT_EQ(a[7], 5);

	a = {1, 2, 3, 4, 5};
	i = a.begin() + 2;
	a.insert(i, {7, 8, 9});
	ASSERT_EQ(a.size(), (size_t)8);
	ASSERT_EQ(a[0], 1);
	ASSERT_EQ(a[1], 2);
	ASSERT_EQ(a[2], 7);
	ASSERT_EQ(a[3], 8);
	ASSERT_EQ(a[4], 9);
	ASSERT_EQ(a[5], 3);
	ASSERT_EQ(a[6], 4);
	ASSERT_EQ(a[7], 5);

	vec_int a1;
	a1.insert(a1.begin(), (size_t)10, 0);
	for (size_t i = 0; i < a1.size(); i++){
		ASSERT_EQ(a1[i], 0);
	}

	vec_int temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, 6);
	ASSERT_EQ(temp.size(), (size_t)11);
	ASSERT_EQ(*i, 6);
	ASSERT_EQ(i[-1], 0);
	ASSERT_EQ(i[1], 0);

	temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, (size_t)3, 4);
	ASSERT_EQ(temp.size(), (size_t)13);
	for (size_t j = 0; j < (size_t)3; j++){
		ASSERT_EQ(i[j], 4);
	}
	ASSERT_EQ(i[-1], int());
	ASSERT_EQ(i[4], int());

	temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, b.begin(), b.end());
	ASSERT_EQ(temp.size(), (size_t)13);
	for (size_t j = 0; j < (size_t)3; j++){
		ASSERT_EQ(i[j], b[j]);
	}
	ASSERT_EQ(i[-1], int());
	ASSERT_EQ(i[4], int());

	temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, {7, 8, 9});
	ASSERT_EQ(temp.size(), (size_t)13);
	for (size_t j = 0; j < (size_t)3; j++){
		ASSERT_EQ(i[j], b[j]);
	}
	ASSERT_EQ(i[-1], int());
	ASSERT_EQ(i[4], int());
}

TEST_F(VectorTest, vector_reserve_int_test){
	vec_int a = {1, 2, 3, 4, 5};
	a.reserve(16);
	ASSERT_EQ(a.capacity(), (size_t)16);
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], (int)(i + 1));
	}
	a.reserve(3);
	ASSERT_EQ(a.capacity(), (size_t)16);
}

TEST_F(VectorTest, vector_erase_int_test){
	vec_int a = {1, 2, 3, 4, 5};
	a.erase(a.begin() + 2);
	vec_int b = {1, 2, 4, 5};
	ASSERT_EQ(a.size(), b.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], b[i]);
	}

	a = {1, 2, 3, 4, 5};
	b = {1, 5};
	a.erase(a.begin() + 1, a.end() - 1);
	ASSERT_EQ(a.size(), b.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], b[i]);
	}	
}

TEST_F(VectorTest, vector_push_pop_back_int_test){
	vec_int a;
	for (int i = 0; i < 20; i++){
		a.push_back(i);
	}
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], (int)i);
	}
	for (int i = 0; i < 10; i++){
		a.pop_back();
	}
	ASSERT_EQ(a.size(), (size_t)10);
}


TEST_F(VectorTest, vector_resize_int_test){
	vec_int a = {1, 2, 3, 4, 5};
	a.resize(15, -2);
	ASSERT_EQ(a.size(), (size_t)15);
	for (size_t i = 0; i < 5; i++){
		ASSERT_EQ(a[i], (int)(i + 1));
	}
	for (size_t i = 5; i < a.size(); i++){
		ASSERT_EQ(a[i], -2);
	}
	a.resize(3, 15);
	ASSERT_EQ(a.size(), (size_t)3);
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], (int)(i + 1));
	}
}

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}