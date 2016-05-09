#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <myVector.h>
#include <myAllocator.h>
#include <iostream>
#include <initializer_list>
#include <sort.h>
#include <vector>

using namespace std;


class VectorTest : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
};

// template<class T>
bool gt(const int& a, const int& b){
	return a > b;
}

struct GT{
	bool operator()(const int& a, const int& b){
		return a < b;
	}
};

TEST_F(VectorTest, sort_test_v){
	vector<int> v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end());
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] < v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), gt);
	for (size_t i = 1; i < v.size(); i++){
		// cout << v[i] << endl;
		ASSERT_TRUE(v[i - 1] > v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), GT());
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] < v[i]);
	}
}


TEST_F(VectorTest, my_vector_speed){
	myVector<int> v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end());
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] < v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), gt);
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] > v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), GT());
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] < v[i]);
	}

}


int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}