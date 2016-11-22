/*
 * Progarm Name: test_main.cpp
 * Created Time: 2016-08-01 14:33:20
 * Last modified: 2016-11-17 12:30:59
 * @author: minphone.linails linails@foxmail.com 
 */

#include "test_main.h"
#include "infinite_loops_v2.h"
#include <iostream>
#include <string>
#include <vector>
#include "common.h"
#include "timer.h"
#include <thread>
#include "v3_test.hpp"

using namespace std;

static vector<device_t> vdev;
static vector<scene_t> vscene;

static void get_scene_vector(vector<scene_t> &r_vscene);

void test_main(void)
{
    cout << "......TEST-MAIN......" << endl;

    for(int i=0; i<1000; i++){
        device_t dev = {
            i,
            "myhome : 009029876758893798759832",
            "json ctrl cmd"
        };

        vdev.push_back(dev);
    }

    get_scene_vector(vscene);

    SceneSetv2  ss(vdev, vscene);

    ss.print_all_set();

    cout << "----------------------------------------------------------------" << endl;

    void eg01(SceneSetv2 &ss);
    eg01(ss);

    void eg02(SceneSetv2 &ss);
    eg02(ss);

    void eg03(SceneSetv2 &ss);
    eg03(ss);

    void eg04(SceneSetv2 &ss);
    eg04(ss);

    void eg05(SceneSetv2 &ss);
    eg05(ss);

    cout << "----------------------------------------------------------------" << endl;

    ss.print_all_set();

#if 0
    ss.del_scene(19);

    ss.print_all_set();
#endif


    /*
     * For v3-test 
     * */
    //v3_test();
}

static void get_scene_vector(vector<scene_t> &r_vscene)
{
    /* 
     * int     id;
     * string  name;
     * int     time;
     * int     timetype; // 1 timing;  2 delay 
     * int     onoff;
     * vector<device_t>    condition_devs;
     * vector<int>         condition_scenes;
     * vector<device_t>    result_devs;
     * vector<int>         result_scenes;
     * vector<device_t>    recover_devs;
     * vector<int>         recover_scenes;
     * */

    {
        scene_t scene;

        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 1;
        scene.time              = 10;
        scene.timetype          = 2;

        cdevs.push_back(vdev[0]);

        rdevs.push_back(vdev[23]);
        rdevs.push_back(vdev[32]);
        rdevs.push_back(vdev[2]);
        rdevs.push_back(vdev[89]);
        rdevs.push_back(vdev[332]);
        rdevs.push_back(vdev[24]);
        rdevs.push_back(vdev[234]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        r_vscene.push_back(scene);
    }
    //------------------------------------------------------------
    {
    }
}

void eg01(SceneSetv2 &ss)
{
    scene_t scene;
    {
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 2;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[2]);

        rdevs.push_back(vdev[43]);
        rdevs.push_back(vdev[37]);
        rdevs.push_back(vdev[29]);
        rdevs.push_back(vdev[0]);
        rdevs.push_back(vdev[322]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[214]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;
    }

    cout << "----------------------------------------------------------------" << endl;
    Timer timer;
    timer.timing();
    int ret = ss.infinite_loops_check(scene);    // aim 
 
    if(0 == ret){
        cout << "infinite loop ? : YES" << endl;
    }else if(1 == ret){
        cout << "timing error !" << endl;
    }else{
        cout << "infinite loop ? : NO" << endl;
    }
    timer.timing();
    cout << "----------------------------------------------------------------" << endl;
}

void eg02(SceneSetv2 &ss)
{
    scene_t scene;
    {
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 2;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[3]);

        rdevs.push_back(vdev[43]);
        rdevs.push_back(vdev[37]);
        rdevs.push_back(vdev[29]);
        rdevs.push_back(vdev[0]);
        rdevs.push_back(vdev[322]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[214]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;
    }

    cout << "----------------------------------------------------------------" << endl;
    Timer timer;
    timer.timing();
    int ret = ss.infinite_loops_check(scene);    // aim 
 
    if(0 == ret){
        cout << "infinite loop ? : YES" << endl;
    }else if(1 == ret){
        cout << "timing error !" << endl;
    }else{
        cout << "infinite loop ? : NO" << endl;
    }
    timer.timing();
    cout << "----------------------------------------------------------------" << endl;
}

void eg03(SceneSetv2 &ss)
{
    scene_t scene;
    {
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 3;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[4]);

        rdevs.push_back(vdev[43]);
        rdevs.push_back(vdev[37]);
        rdevs.push_back(vdev[29]);
        rdevs.push_back(vdev[3]);
        rdevs.push_back(vdev[322]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[214]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;
    }

    cout << "----------------------------------------------------------------" << endl;
    Timer timer;
    timer.timing();
    int ret = ss.infinite_loops_check(scene);    // aim 
 
    if(0 == ret){
        cout << "infinite loop ? : YES" << endl;
    }else if(1 == ret){
        cout << "timing error !" << endl;
    }else{
        cout << "infinite loop ? : NO" << endl;
    }
    timer.timing();
    cout << "----------------------------------------------------------------" << endl;
}

void eg04(SceneSetv2 &ss)
{
    scene_t scene;
    {
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 4;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[332]);

        rdevs.push_back(vdev[13]);
        rdevs.push_back(vdev[57]);
        rdevs.push_back(vdev[89]);
        rdevs.push_back(vdev[3]);
        rdevs.push_back(vdev[22]);
        rdevs.push_back(vdev[28]);
        rdevs.push_back(vdev[114]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;
    }

    cout << "----------------------------------------------------------------" << endl;
    Timer timer;
    timer.timing();
    int ret = ss.infinite_loops_check(scene);    // aim 
 
    if(0 == ret){
        cout << "infinite loop ? : YES" << endl;
    }else if(1 == ret){
        cout << "timing error !" << endl;
    }else{
        cout << "infinite loop ? : NO" << endl;
    }
    timer.timing();
    cout << "----------------------------------------------------------------" << endl;
}

void eg05(SceneSetv2 &ss)
{
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 5;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[4]);
        cdevs.push_back(vdev[14]);

        rdevs.push_back(vdev[49]);
        rdevs.push_back(vdev[38]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[33]);
        rdevs.push_back(vdev[32]);
        rdevs.push_back(vdev[22]);
        rdevs.push_back(vdev[254]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 6;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[20]);
        //cscenes.push_back(3);

        rdevs.push_back(vdev[419]);
        rdevs.push_back(vdev[398]);
        rdevs.push_back(vdev[220]);
        rdevs.push_back(vdev[383]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[27]);
        rdevs.push_back(vdev[154]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 7;
        scene.time              = 6 * 3600; // 6:00:00
        scene.timetype          = 1;

        cdevs.push_back(vdev[21]);

        rdevs.push_back(vdev[414]);
        rdevs.push_back(vdev[898]);
        rdevs.push_back(vdev[220]);
        rdevs.push_back(vdev[380]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[87]);
        rdevs.push_back(vdev[104]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 8;
        scene.time              = 7 * 3600; // 6:00:00
        scene.timetype          = 1;

        cdevs.push_back(vdev[23]);

        rdevs.push_back(vdev[429]);
        rdevs.push_back(vdev[388]);
        rdevs.push_back(vdev[22]);
        rdevs.push_back(vdev[83]);
        rdevs.push_back(vdev[9]);
        rdevs.push_back(vdev[21]);
        rdevs.push_back(vdev[114]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 9;
        scene.time              = 7 * 3600; // 6:00:00
        scene.timetype          = 2;

        cdevs.push_back(vdev[27]);

        rdevs.push_back(vdev[49]);
        rdevs.push_back(vdev[88]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[0]);
        rdevs.push_back(vdev[231]);
        rdevs.push_back(vdev[11]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 10;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 1;

        //cdevs.push_back(vdev[34]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/
        cscenes.push_back(1);
        cscenes.push_back(9);

        rdevs.push_back(vdev[499]);
        rdevs.push_back(vdev[888]);
        rdevs.push_back(vdev[200]);
        rdevs.push_back(vdev[43]);
        rdevs.push_back(vdev[10]);
        rdevs.push_back(vdev[31]);
        rdevs.push_back(vdev[111]);

        //rscenes.push_back(5);
        rscenes.push_back(3);
        rscenes.push_back(2);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
#if 1
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 11;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        cdevs.push_back(vdev[38]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/
        //cscenes.push_back(1);

        rdevs.push_back(vdev[409]);
        rdevs.push_back(vdev[880]);
        rdevs.push_back(vdev[260]);
        rdevs.push_back(vdev[60]);
        rdevs.push_back(vdev[19]);
        rdevs.push_back(vdev[32]);
        rdevs.push_back(vdev[141]);

        //rscenes.push_back(5);
        //rscenes.push_back(3);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 12;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        cdevs.push_back(vdev[60]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/
        //cscenes.push_back(1);

        rdevs.push_back(vdev[509]);
        rdevs.push_back(vdev[881]);
        rdevs.push_back(vdev[261]);
        rdevs.push_back(vdev[61]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[33]);
        rdevs.push_back(vdev[142]);
        rdevs.push_back(vdev[38]);

        //rscenes.push_back(5);
        //rscenes.push_back(3);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 13;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        //cdevs.push_back(vdev[60]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/
        cscenes.push_back(1);

        rdevs.push_back(vdev[510]);
        rdevs.push_back(vdev[882]);
        rdevs.push_back(vdev[262]);
        rdevs.push_back(vdev[62]);
        rdevs.push_back(vdev[5]);
        rdevs.push_back(vdev[210]);
        rdevs.push_back(vdev[34]);
        rdevs.push_back(vdev[143]);
        rdevs.push_back(vdev[39]);

        rscenes.push_back(11);
        rscenes.push_back(5);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
#endif
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 14;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        cdevs.push_back(vdev[60]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/
        cscenes.push_back(1);
        cscenes.push_back(13);

        rdevs.push_back(vdev[511]);
        rdevs.push_back(vdev[883]);
        rdevs.push_back(vdev[263]);
        rdevs.push_back(vdev[63]);
        rdevs.push_back(vdev[6]);
        rdevs.push_back(vdev[211]);
        rdevs.push_back(vdev[35]);
        rdevs.push_back(vdev[144]);
        rdevs.push_back(vdev[40]);

        rscenes.push_back(5);
        rscenes.push_back(11);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 17;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        cdevs.push_back(vdev[60]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        rdevs.push_back(vdev[513]);
        rdevs.push_back(vdev[885]);
        rdevs.push_back(vdev[265]);
        rdevs.push_back(vdev[64]);
        rdevs.push_back(vdev[8]);
        rdevs.push_back(vdev[213]);
        rdevs.push_back(vdev[37]);
        rdevs.push_back(vdev[146]);
        rdevs.push_back(vdev[42]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 18;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        cdevs.push_back(vdev[60]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        rdevs.push_back(vdev[514]);
        rdevs.push_back(vdev[886]);
        rdevs.push_back(vdev[266]);
        rdevs.push_back(vdev[65]);
        rdevs.push_back(vdev[9]);
        rdevs.push_back(vdev[214]);
        rdevs.push_back(vdev[39]);
        rdevs.push_back(vdev[147]);
        rdevs.push_back(vdev[43]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 19;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/
        cscenes.push_back(18);

        rdevs.push_back(vdev[515]);
        rdevs.push_back(vdev[887]);
        rdevs.push_back(vdev[267]);
        rdevs.push_back(vdev[66]);
        rdevs.push_back(vdev[10]);
        rdevs.push_back(vdev[215]);
        rdevs.push_back(vdev[40]);
        rdevs.push_back(vdev[148]);
        rdevs.push_back(vdev[44]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 19;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/
        cdevs.push_back(vdev[1]);

        rdevs.push_back(vdev[1]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;
        cout << "Tang sir request !" << endl;
        Timer timer;
        timer.timing();
        int ret = ss.infinite_loops_check(scene);    // aim 
        cout << "ret : " << ret << endl;
     
        if(0 == ret){
            cout << "infinite loop ? : YES" << endl;
        }else if(1 == ret){
            cout << "timing error !" << endl;
        }else{
            cout << "infinite loop ? : NO" << endl;
        }
        timer.timing();
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        cout << "------------------ for filter test ------------------ " << endl;
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;

        scene.id                = 9;
        scene.time              = 7 * 3600; // 6:00:00
        scene.timetype          = 2;

        cdevs.push_back(vdev[27]);

        rdevs.push_back(vdev[49]);
        rdevs.push_back(vdev[88]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[4]);
        rdevs.push_back(vdev[0]);
        rdevs.push_back(vdev[231]);
        rdevs.push_back(vdev[11]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;

        Timer timer;
        timer.timing();
        int ret = ss.filter(scene);    // aim 
        timer.timing();
     
        if(0 == ret){
            cout << "filter success !" << endl;
        }else{
            cout << "filter fail !" << endl;
        }

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        cout << "------------------ for filter test ------------------ " << endl;
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 3;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[4]);

        rdevs.push_back(vdev[43]);
        rdevs.push_back(vdev[37]);
        rdevs.push_back(vdev[29]);
        rdevs.push_back(vdev[3]);
        rdevs.push_back(vdev[322]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[214]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;

        Timer timer;
        timer.timing();
        int ret = ss.filter(scene);    // aim 
        timer.timing();
     
        if(0 == ret){
            cout << "filter success !" << endl;
        }else{
            cout << "filter fail !" << endl;
        }

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        cout << "------------------ for filter test ------------------ " << endl;
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 2;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[2]);

        rdevs.push_back(vdev[43]);
        rdevs.push_back(vdev[37]);
        rdevs.push_back(vdev[29]);
        rdevs.push_back(vdev[0]);
        rdevs.push_back(vdev[322]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[214]);

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;

        Timer timer;
        timer.timing();
        int ret = ss.filter(scene);    // aim 
        timer.timing();
     
        if(0 == ret){
            cout << "filter success !" << endl;
        }else{
            cout << "filter fail !" << endl;
        }

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        cout << "------------------ for filter test ------------------ " << endl;
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 5;
        scene.time              = 20;
        scene.timetype          = 2;

        cdevs.push_back(vdev[4]);
        cdevs.push_back(vdev[14]);

        rdevs.push_back(vdev[49]);
        rdevs.push_back(vdev[38]);
        rdevs.push_back(vdev[20]);
        rdevs.push_back(vdev[33]);
        rdevs.push_back(vdev[32]);
        rdevs.push_back(vdev[22]);
        rdevs.push_back(vdev[254]);


        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;

        Timer timer;
        timer.timing();
        int ret = ss.filter(scene);    // aim 
        timer.timing();
     
        if(0 == ret){
            cout << "filter success !" << endl;
        }else{
            cout << "filter fail !" << endl;
        }

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        cout << "------------------ for filter test ------------------ " << endl;
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 19;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        rdevs.push_back(vdev[515]);
        rdevs.push_back(vdev[887]);
        rdevs.push_back(vdev[267]);
        rdevs.push_back(vdev[66]);
        rdevs.push_back(vdev[10]);
        rdevs.push_back(vdev[215]);
        rdevs.push_back(vdev[40]);
        rdevs.push_back(vdev[148]);
        rdevs.push_back(vdev[44]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;

        Timer timer;
        timer.timing();
        int ret = ss.filter(scene);    // aim 
        timer.timing();
     
        if(0 == ret){
            cout << "filter success !" << endl;
        }else{
            cout << "filter fail !" << endl;
        }

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
    {
        cout << "------------------ for filter test ------------------ " << endl;
        scene_t scene;
        vector<device_t>    cdevs;
        vector<int>         cscenes;
        vector<device_t>    rdevs;
        vector<int>         rscenes;
        vector<device_t>    rcdevs;
        vector<int>         rcscenes;


        scene.id                = 19;
        scene.time              = 8 * 3600; // 6:00:00
        scene.timetype          = 2;

        /* bug record :
         * 1.action map>  scene_pos
         * 2.action trig> scene_pos
         **/

        rdevs.push_back(vdev[515]);
        rdevs.push_back(vdev[887]);
        rdevs.push_back(vdev[267]);
        rdevs.push_back(vdev[66]);
        rdevs.push_back(vdev[10]);
        rdevs.push_back(vdev[215]);
        rdevs.push_back(vdev[40]);
        rdevs.push_back(vdev[148]);
        rdevs.push_back(vdev[44]);

        //--------------------------------
        scene.condition_devs    = cdevs;
        scene.condition_scenes  = cscenes;
        scene.result_devs       = rdevs;
        scene.result_scenes     = rscenes;
        scene.recover_devs      = rcdevs;
        scene.recover_scenes    = rcscenes;

        cout << "----------------------------------------------------------------" << endl;

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;

        Timer timer;
        timer.timing();
        int ret = ss.filter(scene);    // aim 
        timer.timing();
     
        if(0 == ret){
            cout << "filter success !" << endl;
        }else{
            cout << "filter fail !" << endl;
        }

        cout << "scene.result_devs : " ;
        for(auto &unit : scene.result_devs){
            cout << unit.id << " ";
        }
        cout << endl;
        cout << "----------------------------------------------------------------" << endl;
    }
}


