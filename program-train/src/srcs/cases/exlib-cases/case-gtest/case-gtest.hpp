/*
 * Progarm Name: case-gtest.hpp
 * Created Time: 2017-02-24 13:36:11
 * Last modified: 2017-02-24 14:49:32
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CASE_GTEST_HPP_
#define _CASE_GTEST_HPP_

/* 
 * Note :
 *
 *  gtest 中的所有断言相关的宏分为两类
 *  01. ASSERT_* 系列在检查点失败时，退出当前函数
 *  02. EXPECT_* 系列在检查点失败时，继续往下执行
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * |    *_TRUE(condition);
 * |    *_FALSE(condition);
 * |    *_EQ(expected, actual);                 // expected == actual
 * |    *_NE(val1, val2);                       // val1 != val2
 * |    *_LT(val1, val2);                       // val1 < val2
 * |    *_LE(val1, val2);                       // val1 <= val2
 * |    *_GT(val1, val2);                       // val1 > val2
 * |    *_GE(val1, val2);                       // val1 >= val2
 * |    *_STREQ(expected_str, actual_str);      // the two C strings have the same content
 * |    *_STRNE(str1, str);                     // the two C strings have different content
 * |    *_STRCASEEQ(expected_str, actual_str);  // the two C strings have the same content, ignoring case
 * |    *_STRCASENE(str1, str);                 // the two C strings have different content, ignoring case
 *
 * */

class CaseGtest{
public:
    CaseGtest();
    ~CaseGtest();
    int  cg_main(int argc, char **argv);
private:
    int  first_case(int argc, char **argv);
    int  base_assert(void);
};

#endif //_CASE_GTEST_HPP_
