#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <myVector.h>
#include <myAllocator.h>
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <sort.h>
#include <vector>
#include <ctime>
#define K 30000

using namespace std;


class VectorTest : public ::testing::Test
{
protected:
	void SetUp()
	{
		srand(time(0));
		sv.reserve(K);
		for (int i = 0; i < K; i++){
			sv.push_back(rand());
		}
		sv2 = sv;
		mv = myVector<int>(sv.begin(), sv.end());
		mv2 = mv;
		for (size_t i = 0; i < sv.size(); i++){
			if (sv[i] != mv[i]){
				throw 5;
			}
		}
	}
	void TearDown()
	{
	}

	vector<int> sv;
	vector<int> sv2;
	myVector<int> mv;
	myVector<int> mv2;
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
		ASSERT_TRUE(v[i - 1] <= v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), gt);
	for (size_t i = 1; i < v.size(); i++){
		// cout << v[i] << endl;
		ASSERT_TRUE(v[i - 1] >= v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), GT());
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] <= v[i]);
	}
}


TEST_F(VectorTest, my_vector_speed){
	myVector<int> v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end());
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] <= v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), gt);
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] >= v[i]);
	}

	v = {7, 2, 3, 5, 6, 9, 1};
	mysort(v.begin(), v.end(), GT());
	for (size_t i = 1; i < v.size(); i++){
		ASSERT_TRUE(v[i - 1] <= v[i]);
	}

}

TEST_F(VectorTest, speed_stand){
	mysort(sv.begin(), sv.end());
	for (size_t i = 0; i < sv.size(); i++){
		// cout << sv[i - 1] << " " << sv[i] << endl;
		ASSERT_TRUE(sv[i - 1] <= sv[i]);
	}
}

TEST_F(VectorTest, speed_standsort){
	sort(sv2.begin(), sv2.end());
	for (size_t i = 1; i < sv2.size(); i++){
		ASSERT_TRUE(sv2[i - 1] <= sv2[i]);
	}
}

TEST_F(VectorTest, speed_my){
	mysort(mv.begin(), mv.end());
	for (size_t i = 1; i < mv.size(); i++){
		ASSERT_TRUE(mv[i - 1] <= mv[i]);
	}
}

TEST_F(VectorTest, stand_sortspeed_my){
	sort(mv2.begin(), mv2.end());
	for (size_t i = 1; i < mv2.size(); i++){
		ASSERT_TRUE(mv2[i - 1] <= mv2[i]);
	}
}


int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
