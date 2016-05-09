#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <myVector.h>
#include <myAllocator.h>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <vector>
#define S(N) some_class(N)
#define K 3000000
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
	myVector<some_class, myAllocator<some_class> > myv;
	vector<some_class> standv;
};

TEST_F(VectorTest, stand_vector_speed){
	standv.clear();
	for (int i = 0; i < K; i++){
		standv.push_back(S(i));
	}
	for (int i = 0; i < K; i++){
		ASSERT_EQ(standv[i], S(i));
	}
}


TEST_F(VectorTest, my_vector_speed){
	myv.clear();
	for (int i = 0; i < K; i++){
		myv.push_back(S(i));
	}
	for (int i = 0; i < K; i++){
		ASSERT_EQ(myv[i], S(i));
	}	
}


int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}