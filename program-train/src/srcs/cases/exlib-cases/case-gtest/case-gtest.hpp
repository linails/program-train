/*
 * Progarm Name: case-gtest.hpp
 * Created Time: 2017-02-24 13:36:11
 * Last modified: 2017-03-31 10:31:07
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
 * |    *_DEATH(statement, regex);              // statement crashes with the given error
 * |    *_EXIT(statement, predicate, regex);    // statement exits with the given error and its exit code matches predicate
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * |    *_THROW(statement, exception_type);     // statement throws an exception of the given type
 * |    *_ANY_THROW(statement);                 // statement throws an exception of any type
 * |    *_NO_THROW(statement);                  // statement doesn't throw any exception
 * |    *_FLOAT_EQ(expected, actual);           // the two float values are almost equal
 * |    *_DOUBLE_EQ(expected, actual);          // the two double values are almost equal
 * |    *_NEAR(val1, val2, abs_error);          // the different between val1 and val2 doesn't exceed the given absolute error
 *
 * */

class CaseGtest{
public:
    CaseGtest();
    ~CaseGtest();
    int  cg_main(int argc, char **argv);
private:
    int  base_assert(void);
};

#endif //_CASE_GTEST_HPP_

