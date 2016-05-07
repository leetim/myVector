#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <myVector.h>
#include <myAllocator.h>
#include <iostream>

class some_class{
public:
	some_class(){
		value = -1;
	};

	void set_value(int n){
		value = n;
	};

	int get_value(){
		return value;
	};
private:
	int value;
};

class TestFoo : public ::testing::Test
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

TEST_F(TestFoo, allocation_deallocation){
	int* ptr = int_alloc.allocate(10);
	int i;
	try{
		for (i = 0; i < 10; i++){
			ptr[i] = 1;
		}
	}
	catch(...){
		ASSERT_EQ(i, 10);
	}
	ASSERT_EQ((ptr + 10) - ptr, 10);
	int_alloc.deallocate(ptr, 10);

	some_class* ptr1 = some_alloc.allocate(17);
	some_alloc.construct(ptr1, 17);
	try{
		for (int i = 0; i < 17; i++){
			ptr1[i].set_value(0);
		}
	}
	catch(...){
		ASSERT_EQ(i, 17);
	}
	for (int i = 0; i < 17; i++){
		some_alloc.destroy(&ptr1[i]);
	}
	some_alloc.deallocate(ptr1, 17);
}

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}