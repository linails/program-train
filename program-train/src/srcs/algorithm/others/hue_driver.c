/*
 * Progarm Name: hue_driver.c
 * Created Time: 2015-12-03 10:57:19
 * @author: minphone.linails linails@foxmail.com 
 */

#include "hue_driver.h"
#include <stdio.h>


/*hue --> rgb*/
double hue2rgb(double v1, double v2, double vh)
{
    if(vh < 0) vh += 1;
    if(vh > 1) vh -= 1;
    if(6.0 * vh < 1) return v1 + (v2 - v1) * 6.0 * vh;
    if(2.0 * vh < 1) return v2;
    if(3.0 * vh < 2) return v1 + (v2 - v1) * ((2.0 / 3.0) - vh) * 6.0;
    return v1;
}

/*hsl --> rgb*/
void hsl2rgb(ColorRGB_t *color, unsigned char h, unsigned char s, unsigned char l)
{
    double H = (h * 1.0) / 255;
    double S = (s * 1.0) / 255;
    double L = (l * 1.0) / 255;
    double q,p;
    double tr,tg,tb;
    double r,g,b;
    int i;
    double *p_trgb;
    double *p_rgb;

    if(L < 0.5) q = L * (1 + S);
    else q = L + S - (L * S);
    
    p = 2 * L - q;

    tr = H + 1.0 / 3.0;
    tg = H;
    tb = H - 1.0 / 3.0;

    if(tr < 0) tr += 1.0;
    else if(tr > 1) tr -= 1.0;
    if(tg < 0) tg += 1.0;
    else if(tg > 1) tg -= 1.0;
    if(tb < 0) tb += 1.0;
    else if(tb > 1) tb -= 1.0;

    for(i = 0 ; i < 3 ; i++){
        if(i == 0){p_trgb = &tr; p_rgb = &r;}
        else if(i == 1){p_trgb = &tg; p_rgb = &g;}
        else if(i == 2){p_trgb = &tb; p_rgb = &b;}

        if(*p_trgb < (1.0 / 6.0)) *p_rgb = p + ((q - p) * 6 * (*p_trgb));
        else if((*p_trgb > (1.0 / 6.0)) && (*p_trgb < 0.5)) *p_rgb = q;
        else if((*p_trgb > 0.5) && (*p_trgb < 2.0 / 3.0)) *p_rgb = p + ((q - p) * 6 * (2.0 / 3.0 - (*p_trgb)));
        else *p_rgb = p;
    }

    color->r = r * 255;
    color->g = g * 255;
    color->b = b * 255;
}

/*hsb --> rgb*/
void hsb2rgb(ColorRGB_t *color, unsigned char h, unsigned char s, unsigned char b)
{
    double cr,cg,cb;
    int hi = 0;
    double f = 0;
    double H,S,B;
    double p,q,t;

    H = (h*1.0)/255 * 360;
    S = (s*1.0)/255;
    B = (b*1.0)/255;

    hi = H/60;
    f = H/60 - hi;

    p = B * (1 - S);
    q = B * (1 - f * S);
    t = B * (1 - (1 - f) * S);

    switch( hi ){
        case 0: cr = B , cg = t , cb = p ;break;
        case 1: cr = q , cg = B , cb = p ;break;
        case 2: cr = p , cg = B , cb = t ;break;
        case 3: cr = p , cg = q , cb = B ;break;
        case 4: cr = t , cg = p , cb = B ;break;
        case 5: cr = B , cg = p , cb = q ;break;
    }

    cr *= 255;
    cg *= 255;
    cb *= 255;

    color->r = cr;
    color->g = cg;
    color->b = cb;
}


