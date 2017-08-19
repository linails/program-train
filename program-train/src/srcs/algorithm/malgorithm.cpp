/*
 * Progarm Name: malgorithm.cpp
 * Created Time: 2016-08-14 10:35:26
 * Last modified: 2017-08-19 18:06:20
 */

#include "malgorithm.hpp"
#include <iostream>
#include "non-mutating-algo.h"
#include "mutating-algo.h"
#include "sorting-algo.h"
#include "data-structure.h"
#include "data-structure.hpp"
#include <cassert>
#include "other-string.hpp"
#include "finder.hpp"
#include "finder-en.hpp"
#include "hue_driver.h"
#include "hsb2hsl.h"
#include <cstdlib>
#include <cstring>

using namespace std;

mAlgorithm::mAlgorithm()
{
}

mAlgorithm::~mAlgorithm()
{
}

int  mAlgorithm::malgo_main(int argc, char **argv)
{
    int ret = 0;

    cout << "----------- algorithm_main -----------" << endl;
    {
        //non_mutating_algo();

        //mutating_algo();

        //sorting_algo();
    }
    cout << "----------- data structure --------------" << endl;
    {
    #if 1
        /* 
         * version C
         * */
        cDataStruct_t *cds = NULL;

        if(0 == (ret = cds_constructor_safety(&cds))){
            if(NULL != cds){
                cout << "cDataStruct_t construct successed !" << endl;

                ret = cds->cdatastruct_main((void *)cds, argc, argv);

                if(0 == cds->destructor(&cds)){
                    cout << "cDataStruct_t destruct successed !" << endl;
                }
            }
        }
    #endif
    }
    cout << "----------- data structure --------------" << endl;
    {
    #if 0
        /* 
         * version C++
         * */
        DataStructure ds;

        ret = ds.datastruct_main(argc, argv); assert(-1 != ret);
    #endif
    }
    cout << "----------- other data structure --------------" << endl;
    {
    #if 0
        OtherString os;

        ret = os.main(argc, argv); assert(-1 != ret);

        #if COMPILE_FLAG_finder
         #if 0
        Finder finder;
        
        ret = finder.main(argc, argv); assert(-1 != ret);
         #else
        FinderEn finder;
        
        ret = finder.main(argc, argv); assert(-1 != ret);
         #endif
        #endif
    #endif
    }
    cout << "------------ algo for hue ---------------------" << endl;
    {
        #if COMPILE_FLAG_hue
        ret = this->algo_for_hue(); assert(-1 != ret);
        #endif
    }

    return ret;
}

int  mAlgorithm::algo_for_hue(void)
{
#if 0
    ColorRGB_t color     = {0,0,0};
    ColorHSL_t color_hsl = {0,0,0};
    ColorHSL_t color_hsb = {0,0,0};
    int h,s,b;
    printf("hsl-driver for zigbee ...\n");

    this->hsl2hundred_percent(&color_hsl, 270, 34, 53);
    hsb2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->rgb)\n", color.r, color.g, color.b);

    this->hsl2hundred_percent(&color_hsb, 270, 34, 53);
    hsb2hsl(&color_hsl.h, &color_hsl.s, &color_hsl.l, color_hsb.h, color_hsb.s, color_hsb.l);
    hsl2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->hsl->rgb)\n", color.r, color.g, color.b);

    printf("\n");

    this->hsl2hundred_percent(&color_hsl, 344, 70, 18);
    hsb2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->rgb)\n", color.r, color.g, color.b);

    this->hsl2hundred_percent(&color_hsb, 344, 70, 18);
    hsb2hsl(&color_hsl.h, &color_hsl.s, &color_hsl.l, color_hsb.h, color_hsb.s, color_hsb.l);
    hsl2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->hsl->rgb)\n", color.r, color.g, color.b);

    printf("\n");

    this->hsl2hundred_percent(&color_hsl, 131, 47, 19);
    hsb2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->rgb)\n", color.r, color.g, color.b);

    this->hsl2hundred_percent(&color_hsb, 131, 47, 19);
    hsb2hsl(&color_hsl.h, &color_hsl.s, &color_hsl.l, color_hsb.h, color_hsb.s, color_hsb.l);
    hsl2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->hsl->rgb)\n", color.r, color.g, color.b);

    printf("\n");

    this->hsl2hundred_percent(&color_hsl, 64, 69, 45);
    hsb2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->rgb)\n", color.r, color.g, color.b);

    this->hsl2hundred_percent(&color_hsb, 64, 69, 45);
    hsb2hsl(&color_hsl.h, &color_hsl.s, &color_hsl.l, color_hsb.h, color_hsb.s, color_hsb.l);
    hsl2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->hsl->rgb)\n", color.r, color.g, color.b);

    printf("\n");

    this->hsl2hundred_percent(&color_hsl, 195, 57, 100);
    hsb2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->rgb)\n", color.r, color.g, color.b);

    this->hsl2hundred_percent(&color_hsb, 195, 57, 100);
    hsb2hsl(&color_hsl.h, &color_hsl.s, &color_hsl.l, color_hsb.h, color_hsb.s, color_hsb.l);
    hsl2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->hsl->rgb)\n", color.r, color.g, color.b);

    printf("\n");

    this->hsl2hundred_percent(&color_hsl, 0, 91, 80);
    hsb2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->rgb)\n", color.r, color.g, color.b);

    this->hsl2hundred_percent(&color_hsb, 0, 91, 80);
    hsb2hsl(&color_hsl.h, &color_hsl.s, &color_hsl.l, color_hsb.h, color_hsb.s, color_hsb.l);
    hsl2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
    printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->hsl->rgb)\n", color.r, color.g, color.b);

    printf("\n");

    while(1){
        printf("please input h ,  s ,  b : (eg . 0, 91, 80)\n");
        scanf("%d, %d, %d", &h, &s, &b);
        this->hsl2hundred_percent(&color_hsb, h, s, b);
        hsb2hsl(&color_hsl.h, &color_hsl.s, &color_hsl.l, color_hsb.h, color_hsb.s, color_hsb.l);
        hsl2rgb(&color, color_hsl.h, color_hsl.s, color_hsl.l);
        printf(" ----> r:%.3d -- g:%.3d -- b:%.3d (hsb->hsl->rgb)\n", color.r, color.g, color.b);
    }
#endif
#if 1
    int ih, is, il;
    unsigned char h, s, l;
    ih = 10;
    is = 11;
    il = 12;
    h  = 10;
    s  = 11;
    l  = 12;
    printf("ih :%.3d is :%.3d ib :%.3d\n", ih, is, il);
    hsb2hsl((unsigned char *)&ih, (unsigned char *)&is, (unsigned char *)&il, ih, is, il);
    printf("ih :%.3d is :%.3d il :%.3d\n", ih, is, il);
    printf("h :%.3d s :%.3d b :%.3d\n", h, s, l);
    hsb2hsl(&h, &s, &l, h, s, l);
    printf("h :%.3d s :%.3d l :%.3d\n", h, s, l);

    h  = 127;
    s  = 141;
    l  = 0xff;
    printf("h :%.3d s :%.3d b :%.3d\n", h, s, l);
    hsb2hsl(&h, &s, &l, h, s, l);
    printf("h :%.3d s :%.3d l :%.3d\n", h, s, l);

    h  = 127;
    s  = 50;
    l  = 0xff;
    printf("h :%.3d s :%.3d b :%.3d\n", h, s, l);
    hsb2hsl(&h, &s, &l, h, s, l);
    printf("h :%.3d s :%.3d l :%.3d\n", h, s, l);
#endif

    return 0;
}

void mAlgorithm::hsl2hundred_percent(ColorHSL_t *colorhsl, int h, int s, int l)
{
    colorhsl->h = (h*1.0)/360 * 255;
    colorhsl->s = (s*1.0)/100 * 255;
    colorhsl->l = (l*1.0)/100 * 255;

    printf("h :(%.3d)[0,360) , s :(%.3d)[0,1] ,b&l :(%.3d)[0,1]", h, s, l);
    printf(" ---->[0,255] h :(%.3d) , s :(%.3d) ,b&l :(%.3d)", colorhsl->h, colorhsl->s, colorhsl->l);
}

