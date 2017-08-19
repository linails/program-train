/*
 * Progarm Name: malgorithm.hpp
 * Created Time: 2016-08-14 10:35:30
 */

#ifndef _MALGORITHM_HPP_
#define _MALGORITHM_HPP_

#define COMPILE_FLAG_finder         0
#define COMPILE_FLAG_hue            0

typedef struct{
    unsigned char h;
    unsigned char s;
    unsigned char l;
}ColorHSL_t;

class mAlgorithm{
public:
    mAlgorithm();
    ~mAlgorithm();
    int  malgo_main(int argc, char **argv);
private:
    int  algo_for_hue(void);
    void hsl2hundred_percent(ColorHSL_t *colorhsl, int h, int s, int l);
};

#endif //_MALGORITHM_HPP_

