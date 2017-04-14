/*
 * Progarm Name: case-gtest.cpp
 * Created Time: 2017-02-24 13:36:05
 * Last modified: 2017-03-31 11:30:04
 * @author: minphone.linails linails@foxmail.com 
 */

#include <pthread.h>
#include "case-gtest.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "event-mecha.hpp"

using std::cout;
using std::endl;
using std::string;

int foo(int a, int b)
{
    if(0 == a || 0 == b){
        throw "don't do that!";
    }

    int c = a % b;
    if(0 == c){
        return b;
    }

    return foo(b, c);
}

TEST(fooTest, HandleNoneZeroInput)
{
    EXPECT_EQ(2, foo(4, 10));
    EXPECT_EQ(6, foo(30, 18));
}

TEST(fooTest, zero)
{
    EXPECT_EQ(2, foo(4, 10));
    EXPECT_EQ(6, foo(30, 18));
}

TEST(fooTest1, zero)
{
    EXPECT_EQ(2, foo(4, 10));
    EXPECT_EQ(6, foo(30, 18));
}

CaseGtest::CaseGtest()
{
}

CaseGtest::~CaseGtest()
{
}

int  CaseGtest::cg_main(int argc, char **argv)
{
    int ret = 0 ;

    ret = this->base_assert();  assert(-1 != ret);


    /* 
     * init google test
     * */
    ::testing::AddGlobalTestEnvironment(new GlobalCase);
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

int  CaseGtest::base_assert(void)
{
    int ret = 0;

    cout << "base_assert() ..." << endl;

    {
        string s1 = "abcdefg-s1";
        string s2 = "abcdefg-s1";

        EXPECT_STREQ(s1.c_str(), s1.c_str());
    }

    return ret;
}

TEST_F(SuiteCase, suit0)
{
    string s1 = "abcdefg-s1";
    string s2 = "abcdefg-s1";
    cout << "suit0" << endl;
    EXPECT_STREQ(s1.c_str(), s1.c_str());
    EXPECT_EQ(10, this->m_uc.get());
}

TEST_F(SuiteCase, suit1)
{
    string s1 = "abcdefg-s1";
    string s2 = "abcdefg-s1";
    cout << "suit1" << endl;
    EXPECT_STREQ(s1.c_str(), s1.c_str());
    EXPECT_EQ(10, this->m_uc.get());
}

TEST_F(CaseCase, case0)
{
    string s1 = "abcdefg-s1";
    string s2 = "abcdefg-s1";
    cout << "case0" << endl;
    EXPECT_STREQ(s1.c_str(), s1.c_str());
    ASSERT_EQ(10, this->m_uc.get());
}

TEST_F(CaseCase, case1)
{
    string s1 = "abcdefg-s1";
    string s2 = "abcdefg-s1";
    cout << "case1" << endl;
    EXPECT_STREQ(s1.c_str(), s1.c_str());
}

TEST_F(CaseCase, private_func)
{
}

