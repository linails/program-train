/*
 * Progarm Name: event-mecha.hpp
 * Created Time: 2017-02-24 16:17:09
 * Last modified: 2017-02-24 16:42:15
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _EVENT_MECHA_HPP_
#define _EVENT_MECHA_HPP_

/* 
 * Note :
 *
 * gtest 提供了3种事件机制
 * 01. 全局的，所有 case 执行前后
 * 02. TestSuite 级别的，在某一批 case 中第一个 case 前，最后一个 case 执行后
 * 03. TestCase 级别的，每个 TestCase 前后
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 01. 要实现全局事件，类必须继承 testing::Environment 类，实现里面的 SetUp 和 TearDown 方法
 *   <1> SetUp() 方法在所有 case 执行前执行
 *   <2> TearDown() 方法在所有 case 执行后执行
 *
 * 02. TestSuite 级别的，类必须继承自 testing::Test
 *   <1> SetUpTestCase() 方法在第一个 TestCase 执行前执行
 *   <2> TearDownTestCase() 方法在最后一个 TestCase 执行后执行
 *
 * 03. TestCase 级别的，每个 TestCase 前后
 *   <1> SetUp() 方法在每个 case 执行前执行
 *   <2> TearDown() 方法在每个 case 执行后执行
 *
 * */

#include <gtest/gtest.h>

/* 
 * 01
 * */
class GlobalCase : public testing::Environment{
public:
    virtual void SetUp(void);
    virtual void TearDown(void);
};

/* 
 * 02
 * */
class SuiteCase : public testing::Test{
protected:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
protected:
    //static T* shared_resource_;
};

/* 
 * 03
 * */
class CaseCase : public testing::Test{
protected:
    virtual void SetUp(void);
    virtual void TearDown(void);
};

#endif //_EVENT_MECHA_HPP_

