#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <myVector.h>
#include <myAllocator.h>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#define S(N) some_class(N)

using namespace std;

class some_class{
public:
	some_class(){
		value = -1;
		value2 = -1;
		value3 = -1;
	};


	some_class(int v){
		value = v;
		value2 = -1;
		value3 = -1;
	};

	some_class(const some_class& other){
		value = other.value;
		value2 = other.value2;
		value3 = other.value3;
	};

	some_class(int v, int v2, int v3){
		value = v;
		value2 = v2;
		value3 = v3;
	};

	void set_value(int n){
		value = n;
	};

	int get_value(){
		return value;
	};

	int get_value2(){
		return value2;
	};
	int get_value3(){
		return value3;
	};

	friend bool operator==(const some_class& left, const some_class& right);
private:
	int value;
	int value2;
	int value3;
};

bool operator==(const some_class& left, const some_class& right){
	return (left.value == right.value) && (left.value2 == right.value2) && (left.value3 == right.value3);
}



class VectorTest : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
	// typedef myVector<int> vec_some;
	typedef myVector<some_class> vec_some;
	// myVector<int> iv;
	myVector<some_class> sv;
};

TEST_F(VectorTest, vector_constructors_int){
	vec_some a1;
	vec_some a2(5);
	vec_some a3 = {S(1), S(2), S(3), S(4)};
	vec_some a4({S(1), S(2), S(3), S(4)});
	vec_some a5(a4);
	vec_some a6 = a4;
	vec_some a7(a3.begin(), a3.end());
	ASSERT_EQ(a1.size(), (size_t)0);
	ASSERT_EQ(a2.size(), (size_t)5);
	ASSERT_EQ(a2[0], some_class());
	ASSERT_EQ(a3.size(), (size_t)4);
	ASSERT_EQ(a3[0], S(1));
	ASSERT_EQ(a3[1], S(2));
	ASSERT_EQ(a3[2], S(3));
	ASSERT_EQ(a3[3], S(4));
	ASSERT_EQ(a5.size(), a4.size());
	ASSERT_EQ(a5.front(), a4.front());
	ASSERT_EQ(a5.back(), a4.back());
	ASSERT_EQ(a7.size(), a3.size());
}

TEST_F(VectorTest, reference_assign_int){
	vec_some a = {S(1), S(2), S(3), S(4), S(5), S(6)};
	vec_some b;
	b = a;
	ASSERT_EQ(b.size(), a.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], b[i]);
		ASSERT_EQ(a[i], some_class(i + 1));
		ASSERT_EQ(a.at(i), some_class(i + 1));
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
	ASSERT_EQ(a.back(), S(6));
	ASSERT_EQ(a.front(), S(1));
	b.assign((size_t)3, S(4));
	ASSERT_EQ(b.size(), (size_t)3);
	for (size_t i = 0; i < b.size(); i++){
		ASSERT_EQ(b[i], S(4));
	}
	b.assign({S(0), S(1), S(2), S(3)});
	ASSERT_EQ(b.size(), (size_t)4);
	for (size_t i = 0; i < b.size(); i++){
		ASSERT_EQ(b[i], S(i));
	}
	b.assign(a.begin(), a.begin() + 5);
	ASSERT_EQ(b.size(), (size_t)5);
	for (size_t i = 0; i < b.size(); i++){
		ASSERT_EQ(b[i], S(i + 1));
	}
	ASSERT_FALSE(b.empty());
	b.clear();
	ASSERT_TRUE(b.empty());
}

TEST_F(VectorTest, vector_assign_some_test){
	vec_some a = {S(1), S(2), S(3), S(4)};
	vec_some temp;
	temp = a;
	ASSERT_EQ(a.size(), temp.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], temp[i]);
	}

	temp.clear();
	temp = {S(1), S(2), S(3), S(4)};
	ASSERT_EQ(a.size(), temp.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], temp[i]);
	}

	temp.clear();
	temp.assign((size_t)5, S(4));
	ASSERT_EQ(temp.size(), (size_t)5);
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(S(4), temp[i]);
	}

	temp.clear();
	temp.assign(a.begin(), a.end());
	ASSERT_EQ(a.size(), temp.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], temp[i]);
	}
}

TEST_F(VectorTest, vector_insert_some_test){
	vec_some a = {S(1), S(2), S(3), S(4), S(5)};
	vec_some::iterator i = a.begin() + 2;
	a.insert(i, S(6));
	ASSERT_EQ(a.size(), (size_t)6);
	ASSERT_EQ(a[0], S(1));
	ASSERT_EQ(a[1], S(2));
	ASSERT_EQ(a[2], S(6));
	ASSERT_EQ(a[3], S(3));
	ASSERT_EQ(a[4], S(4));
	ASSERT_EQ(a[5], S(5));

	a = {S(1), S(2), S(3), S(4), S(5)};
	i = a.begin() + 2;
	a.insert(i, (size_t)3, S(6));
	ASSERT_EQ(a.size(), (size_t)8);
	ASSERT_EQ(a[0], S(1));
	ASSERT_EQ(a[1], S(2));
	ASSERT_EQ(a[2], S(6));
	ASSERT_EQ(a[3], S(6));
	ASSERT_EQ(a[4], S(6));
	ASSERT_EQ(a[5], S(3));
	ASSERT_EQ(a[6], S(4));
	ASSERT_EQ(a[7], S(5));

	a = {S(1), S(2), S(3), S(4), S(5)};
	i = a.begin() + 2;
	vec_some b = {S(7), S(8), S(9)};
	a.insert(i, b.begin(), b.end());
	ASSERT_EQ(a.size(), (size_t)8);
	ASSERT_EQ(a[0], S(1));
	ASSERT_EQ(a[1], S(2));
	ASSERT_EQ(a[2], S(7));
	ASSERT_EQ(a[3], S(8));
	ASSERT_EQ(a[4], S(9));
	ASSERT_EQ(a[5], S(3));
	ASSERT_EQ(a[6], S(4));
	ASSERT_EQ(a[7], S(5));

	a = {S(1), S(2), S(3), S(4), S(5)};
	i = a.begin() + 2;
	a.insert(i, {S(7), S(8), S(9)});
	ASSERT_EQ(a.size(), (size_t)8);
	ASSERT_EQ(a[0], S(1));
	ASSERT_EQ(a[1], S(2));
	ASSERT_EQ(a[2], S(7));
	ASSERT_EQ(a[3], S(8));
	ASSERT_EQ(a[4], S(9));
	ASSERT_EQ(a[5], S(3));
	ASSERT_EQ(a[6], S(4));
	ASSERT_EQ(a[7], S(5));

	vec_some a1;
	a1.insert(a1.begin(), (size_t)10, S(0));
	for (size_t i = 0; i < a1.size(); i++){
		ASSERT_EQ(a1[i], S(0));
	}

	vec_some temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, S(6));
	ASSERT_EQ(temp.size(), (size_t)11);
	ASSERT_EQ(*i, S(6));
	ASSERT_EQ(i[-1], S(0));
	ASSERT_EQ(i[1], S(0));

	temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, (size_t)3, S(4));
	ASSERT_EQ(temp.size(), (size_t)13);
	for (size_t j = 0; j < (size_t)3; j++){
		ASSERT_EQ(i[j], S(4));
	}
	ASSERT_EQ(i[-1], some_class(0));
	ASSERT_EQ(i[4], some_class(0));

	temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, b.begin(), b.end());
	ASSERT_EQ(temp.size(), (size_t)13);
	for (size_t j = 0; j < (size_t)3; j++){
		ASSERT_EQ(i[j], b[j]);
	}
	ASSERT_EQ(i[-1], some_class(0));
	ASSERT_EQ(i[4], some_class(0));

	temp = a1;
	i = temp.begin() + 4;
	i = temp.insert(i, {S(7), S(8), S(9)});
	ASSERT_EQ(temp.size(), (size_t)13);
	for (size_t j = 0; j < (size_t)3; j++){
		ASSERT_EQ(i[j], b[j]);
	}
	ASSERT_EQ(i[-1], some_class(0));
	ASSERT_EQ(i[4], some_class(0));
}

TEST_F(VectorTest, vector_reserve_some_test){
	vec_some a = {S(1), S(2), S(3), S(4), S(5)};
	a.reserve(16);
	ASSERT_EQ(a.capacity(), (size_t)16);
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], S(i + 1));
	}
	a.reserve(3);
	ASSERT_EQ(a.capacity(), (size_t)16);
}

TEST_F(VectorTest, vector_erase_some_test){
	vec_some a = {S(1), S(2), S(3), S(4), S(5)};
	a.erase(a.begin() + 2);
	vec_some b = {S(1), S(2), S(4), S(5)};
	ASSERT_EQ(a.size(), b.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], b[i]);
	}

	a = {S(1), S(2), S(3), S(4), S(5)};
	b = {S(1), S(5)};
	a.erase(a.begin() + 1, a.end() - 1);
	ASSERT_EQ(a.size(), b.size());
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], b[i]);
	}	
}

TEST_F(VectorTest, vector_push_pop_back_some_test){
	vec_some a;
	for (int i = 0; i < 20; i++){
		a.push_back(S(i));
	}
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], S(i));
	}
	for (int i = 0; i < 10; i++){
		a.pop_back();
	}
	ASSERT_EQ(a.size(), (size_t)10);
}


TEST_F(VectorTest, vector_resize_some_test){
	vec_some a = {S(1), S(2), S(3), S(4), S(5)};
	a.resize(15, S(-2));
	ASSERT_EQ(a.size(), (size_t)15);
	for (size_t i = 0; i < 5; i++){
		ASSERT_EQ(a[i], S(i + 1));
	}
	for (size_t i = 5; i < a.size(); i++){
		ASSERT_EQ(a[i], S(-2));
	}
	a.resize(3, S(15));
	ASSERT_EQ(a.size(), (size_t)3);
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], S(i + 1));
	}
}

TEST_F(VectorTest, vector_emplace_back_some_test){
	vec_some a = {S(1), S(2), S(3), S(4), S(5)};
	vec_some b = {S(1), S(2), S(3), S(4), S(5), some_class(5, 4, 3)};
	b.emplace_back(5, 4, 3);
	for (size_t i = 0; i < a.size(); i++){
		ASSERT_EQ(a[i], b[i]);
	}

}

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}