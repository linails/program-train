/*
 * Progarm Name: hsb2hsl.c
 * Created Time: 2015-12-05 10:25:48
 * @author: minphone.linails linails@foxmail.com 
 */

#include "hsb2hsl.h"
#include <stdio.h>

/*h[0-360),s[0,1],b[0,1] --> rgb[0,1]*/
static void hsb2rgb(
        double *pr, double *pg, double *pb,
        double h, double  s, double  b);

/*rgb[0,1] --> hsl[0,1]*/
static void rgb2hsl(
        double *h, double *s, double *l,
        double  r, double  g, double  b);

//------------------------------------------------------------

/*hsb[0,255] --> hsl[0,255]*/
void hsb2hsl(
        unsigned char *hsl_h, unsigned char *hsl_s, unsigned char *hsl_l,
        unsigned char  hsb_h, unsigned char  hsb_s, unsigned char  hsb_b)
{
    double r,g,b;
    double h,s,l;

    h = hsb_h * 1.0 / 255 * 360;
    s = hsb_s * 1.0 / 255;
    l = hsb_b * 1.0 / 255;

    hsb2rgb(&r,&g,&b,h,s,l);
    rgb2hsl(&h,&s,&l,r,g,b);
    *hsl_h = h * 254;
    *hsl_s = s * 254;
    *hsl_l = l * 255;
}

//------------------------------------------------------------

/*h[0-360),s[0,1],b[0,1] --> rgb[0,1]*/
void hsb2rgb(
        double *pr, double *pg, double *pb,
        double h, double  s, double  b)
{
    int hi = 0;
    double f = 0;
    double H,S,B;
    double p,q,t;

    H = h;
    S = s;
    B = b;

    hi = H/60;
    f = H/60 - hi;

    p = B * (1 - S);
    q = B * (1 - f * S);
    t = B * (1 - (1 - f) * S);

    switch( hi ){
        case 0: *pr = B , *pg = t , *pb = p ;break;
        case 1: *pr = q , *pg = B , *pb = p ;break;
        case 2: *pr = p , *pg = B , *pb = t ;break;
        case 3: *pr = p , *pg = q , *pb = B ;break;
        case 4: *pr = t , *pg = p , *pb = B ;break;
        case 5: *pr = B , *pg = p , *pb = q ;break;
    }
}

#define max(a,b,c) ((a > ((b > c) ? b : c)) ? a : (b > c) ? b : c)
#define min(a,b,c) ((a < ((b < c) ? b : c)) ? a : (b < c) ? b : c)

/*rgb[0,1] --> hsl[0,1]*/
void rgb2hsl(
        double *h, double *s, double *l,
        double  r, double  g, double  b)
{
    double vmin = min(r , g, b);
    double vmax = max(r , g, b);
    double delta = vmax - vmin;

    double h360;

    *l = (vmax + vmin) / 2;

    if(0 == delta){
        *h = 0;
        *s = 0;
    }else{
        if(*l < 0.5) *s = delta / (vmax + vmin);
        else         *s = delta / (2- vmax - vmin);

        if((r == vmax) && (g >= b)) h360 = 60 * (g - b) / delta;
        else if((r == vmax) && (g < b)) h360 = 60 * (g - b) / delta + 360;
        else if(g == vmax) h360 = 60 * (b - r) / delta + 120;
        else if(b == vmax) h360 = 60 * (r - g) / delta + 240;

        *h = h360 / 360;
    }
}

