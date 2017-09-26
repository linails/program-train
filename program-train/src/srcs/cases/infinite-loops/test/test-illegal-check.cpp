/*
 * Progarm Name: test-illegal-check.cpp
 * Created Time: 2017-04-14 15:14:39
 * Last modified: 2017-04-14 15:26:49
 * @author: minphone.linails linails@foxmail.com 
 */

#include "test-illegal-check.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include "illegal-check.hpp"

using std::cout;
using std::endl;

vector<device_t>    TesterIllegalCheck::devices_set;
vector<scene_t>     TesterIllegalCheck::orig_scenes;

void TesterIllegalCheck::SetUpTestCase(void)
{
    for(int i=0; i<1000; i++){
        device_t dev = {
            i,
            "myhome : 009029876758893798759832",
            "status 0"
        };

        devices_set.push_back(dev);
    }

    init_scenes();

    cout << "[gtest] devies_set.size() : " << devices_set.size() << endl;
    cout << "[gtest] orig_scenes.size() : " << orig_scenes.size() << endl;
}

void TesterIllegalCheck::TearDownTestCase(void)
{
}

int  TesterIllegalCheck::init_scenes(void)
{
    vector<device_t> &vdev = devices_set;

    {
        scene_t scene;

        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 1;
        scene.time              = 100;
        scene.timetype          = 1;

        cdevs.push_back(vdev[2]);

        rdevs.push_back(vdev[3]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[5]);
        rdevs.push_back(vdev[6]);
        rdevs.push_back(vdev[7]);
        rdevs.push_back(vdev[8]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        //orig_scenes.push_back(scene);
    }

    return 0;
}

TEST_F(TesterIllegalCheck, IllegalCheck_1_)
{
    vector<device_t> &vdev = devices_set;

    //vdev[2].status = "status 1";

    scene_t scene;

    vector<device_t>    cdevs;
    vector<int>         cscenes;
    vector<device_t>    rdevs;
    vector<int>         rscenes;
    vector<device_t>    rcdevs;
    vector<int>         rcscenes;


    scene.id                = 9;
    scene.time              = 10;
    scene.timetype          = 1;

    cdevs.push_back(vdev[35]);

    vdev[35].status = "status 1";

    rdevs.push_back(vdev[29]);
    rdevs.push_back(vdev[35]);

    //--------------------------------
    scene.condition_devs    = cdevs;
    scene.condition_scenes  = cscenes;
    scene.result_devs       = rdevs;
    scene.result_scenes     = rscenes;
    scene.recover_devs      = rcdevs;
    scene.recover_scenes    = rcscenes;

    IllegalCheck illegal;

    int ret = illegal.check(scene);
    cout << "[gtest] illegal.check() : " << ret << endl;
    EXPECT_EQ(0, ret);
}

