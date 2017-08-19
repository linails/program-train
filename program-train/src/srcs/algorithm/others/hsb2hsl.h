/*
 * Progarm Name: hsb2hsl.h
 * Created Time: 2015-12-05 10:25:54
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _HSB2HSL_H_
#define _HSB2HSL_H_
#ifdef __cplusplus
extern "C" {
#endif

/*hsb[0,255] --> hsl[0,255]*/
extern void hsb2hsl(
        unsigned char *hsl_h, unsigned char *hsl_s, unsigned char *hsl_l,
        unsigned char  hsb_h, unsigned char  hsb_s, unsigned char  hsb_b
);

#ifdef __cplusplus
}
#endif
#endif //_HSB2HSL_H_

