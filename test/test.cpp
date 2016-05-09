#include <gtest/gtest.h>
#include <gmock/gmock.h>
// #include <myVector.h>
#include <myAllocator.h>
#include <iostream>

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

	some_class(int v1, int v2, int v3){
		value = v1;
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

private:
	int value;
	int value2;
	int value3;
};

class AllocTest : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
	myAllocator<int> int_alloc;
	myAllocator<some_class> some_alloc;
};

TEST_F(AllocTest, allocation_deallocation_int){
	int* ptr = int_alloc.allocate(10);
	for (int i = 0; i < 10; i++){
		int_alloc.construct(&ptr[i], i);
	}
	try{
		for (int i = 0; i < 10; i++){
			ptr[i] = 1;
		}
	}
	catch(...){
		ASSERT_TRUE(false);
	}
	for (int i = 0; i < 10; i++){
		int_alloc.destroy(&ptr[i]);
	}
	ASSERT_EQ((ptr + 10) - ptr, 10);
	int_alloc.deallocate(ptr, 10);
}

TEST_F(AllocTest, allocation_deallocation_some_class){
	some_class* ptr1 = some_alloc.allocate(17);
	for (int i = 0; i < 17; i++){
		some_alloc.construct(&ptr1[i], i, i+1, i+2);
		ASSERT_EQ(ptr1[i].get_value(), i);
		ASSERT_EQ(ptr1[i].get_value2(), i+1);
		ASSERT_EQ(ptr1[i].get_value3(), i+2);
	}
	try{
		for (int i = 0; i < 17; i++){
			ASSERT_EQ(i, ptr1[i].get_value());
		}
	}
	catch(...){
		ASSERT_TRUE(false);
	}
	for (int i = 0; i < 17; i++){
		some_alloc.destroy(&ptr1[i]);
	}
	some_alloc.deallocate(ptr1, 17);
}

TEST_F(AllocTest, allocator_EQ_NEQ_test){
	ASSERT_FALSE(some_alloc == int_alloc);
	ASSERT_TRUE(some_alloc != int_alloc);
	ASSERT_TRUE(some_alloc == myAllocator<some_class>());
	ASSERT_TRUE(some_alloc == myAllocator<some_class>(some_alloc));
}

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}