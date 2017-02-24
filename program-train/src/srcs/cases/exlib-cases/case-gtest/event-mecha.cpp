/*
 * Progarm Name: event-mecha.cpp
 * Created Time: 2017-02-24 16:17:05
 * Last modified: 2017-02-24 16:42:04
 * @author: minphone.linails linails@foxmail.com 
 */

#include "event-mecha.hpp"
#include <iostream>
#include <gtest/gtest.h>

using std::cout;
using std::endl;

void GlobalCase::SetUp(void)
{
    cout << "GlobalCase SetUp()" << endl;
}

void GlobalCase::TearDown(void)
{
    cout << "GlobalCase TearDown()" << endl;
}

void SuiteCase::SetUpTestCase(void)
{
    cout << "SuiteCase SetUpTestCase()" << endl;
}

void SuiteCase::TearDownTestCase(void)
{
    cout << "SuiteCase TearDownTestCase()" << endl;
}

void CaseCase::SetUp(void)
{
    cout << "CaseCase SetUp()" << endl;
}

void CaseCase::TearDown(void)
{
    cout << "CaseCase TearDown()" << endl;
}

