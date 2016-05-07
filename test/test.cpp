#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <myVector.h>
#include <iostream>

class TestFoo : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
};

TEST_F(TestFoo, test1)
{
	ASSERT_EQ(5, 5);
}

TEST_F(TestFoo, test2)
{
	ASSERT_EQ(4, 5);
}

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}