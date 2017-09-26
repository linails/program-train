/*
 * Progarm Name: test-illegal-check.hpp
 * Created Time: 2017-04-14 15:15:16
 * Last modified: 2017-04-14 15:22:22
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TEST_ILLEGAL_CHECK_HPP_
#define _TEST_ILLEGAL_CHECK_HPP_

#include <gtest/gtest.h>
#include "conflict-check.hpp"
#include "common.hpp"

class TesterIllegalCheck : public testing::Test{
protected:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    static int  init_scenes(void);
protected:
    static vector<device_t>    devices_set;
    static vector<scene_t>     orig_scenes;
};

#endif //_TEST_ILLEGAL_CHECK_HPP_

