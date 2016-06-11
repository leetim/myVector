#include <gtest/gtest.h>
#include <gmock/gmock.h>
// #include <myVector.h>
#include <myString.h>
#include <iostream>
// #include <string>

using namespace std;

class myStringTest : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
};

TEST_F(myStringTest, constructor_test){
	myString s1;
	myString s2 = "123";
	myString s3 = s2;
	ASSERT_TRUE(s2 == s3);
	for (size_t i = 0; i < s2.size(); i++){
		ASSERT_EQ(s2[i], s3[i]);
	}
	ASSERT_EQ(s1.size(), (size_t)0);
}

TEST_F(myStringTest, concretination_test){
	string str1[] = {"123", "456", "kaskks", "aaqqaq",  "", "asessetst"};
	string str2[] = {"lasmsl", "4ssa221156", "lslwswsfsfs", "",  "asdwswsw", "asessetst"};
	for (int i = 0; i < 6; i++){
		myString s1 = str1[i].c_str();
		myString s2 = str2[i].c_str();
		myString s3 = s1 + s2;
		myString s4 = myString((str1[i] + str2[i]).c_str());
		// cout << s3 << endl;
		ASSERT_TRUE(s3 == s4);
	}
}

TEST_F(myStringTest, insert_test){
	myString str1[] = {"123", "456", "kaskks", "aaqqaq",  "", "asessetst"};
	myString str2[] = {"lasmsl", "4ssa221156", "lslwswsfsfs", "",  "asdwswsw", "asessetst"};
	myString res[] = {"1lasmsl23", "454ssa2211566", "kaslslwswsfsfskks",
		"aaqqaq",  "asdwswsw", "asesasessetstsetst"};
	size_t ins[] = {1, 2, 3, 4, 0, 4};
	for (int i = 0; i < 6; i++){
		str1[i].insert(str1[i].begin() + ins[i], str2[i]);
		// cout << s3 << endl;
		ASSERT_TRUE(str1[i] == res[i]);
	}
}

TEST_F(myStringTest, search_test){
	myString str1[] = {"123", "asllsalg456askglask", "iwmsjjkaskks", "aaqqaq",  "asdsad", "asessetst"};
	myString str2[] = {"123", "456", "kas", "b",  "", "asessetst"};
 	int pos[] = {0, 8, 6, 6, 0, 0};
	for (size_t i = 0; i < 6; i++ ){
		myString::iterator it = str1[i].find(str2[i]);
		ASSERT_EQ(pos[i], it - str1[i].begin());
	}

}

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
