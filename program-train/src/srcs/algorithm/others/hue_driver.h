/*
 * Progarm Name: hue_driver.h
 * Created Time: 2015-12-03 10:57:24
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _HUE_DRIVER_H_
#define _HUE_DRIVER_H_
#ifdef __cplusplus
extern "C" {
#endif

/*define color rgb struct*/
typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}ColorRGB_t;

/*hsl --> rgb ; h,s,l C-[0,255] ; r,g,b C-[0,255]*/
extern void hsl2rgb(ColorRGB_t *color, unsigned char h, unsigned char s, unsigned char l);

/*hsb --> rgb*/
extern void hsb2rgb(ColorRGB_t *color, unsigned char h, unsigned char s, unsigned char b);

#ifdef __cplusplus
}
#endif
#endif //_HUE_DRIVER_H_

