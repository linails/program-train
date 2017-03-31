/*
 * Progarm Name: test-conflict-check.hpp
 * Created Time: 2017-03-28 10:04:53
 * Last modified: 2017-03-31 14:42:50
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TEST_CONFLICT_CHECK_HPP_
#define _TEST_CONFLICT_CHECK_HPP_

#include <gtest/gtest.h>
#include "conflict-check.hpp"
#include "common.hpp"

class TesterConflict : public testing::Test{
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    static int  init_scenes(void);
protected:
    static vector<device_t>    devices_set;
    static vector<scene_t>     orig_scenes;
    ConflictCheck             *m_cc = nullptr;
};

#endif //_TEST_CONFLICT_CHECK_HPP_

