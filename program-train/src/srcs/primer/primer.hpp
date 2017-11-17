/*
 * Progarm Name: primer.hpp
 * Created Time: 2016-10-28 16:17:04
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _PRIMER_HPP_
#define _PRIMER_HPP_

#define COMPILE_FLAG_cprimer        0
#define COMPILE_FLAG_reference      0
#define COMPILE_FLAG_jumper         0
#define COMPILE_FLAG_cast           0
#define COMPILE_FLAG_exception      0
#define COMPILE_FLAG_exception_ex   0
#define COMPILE_FLAG_overload       0
#define COMPILE_FLAG_chrono         0
#define COMPILE_FLAG_class          0
#define COMPILE_FLAG_class_enhenced 0
#define COMPILE_FLAG_drived         0
#define COMPILE_FLAG_boost          0
#define COMPILE_FLAG_regex          0
#define COMPILE_FLAG_regex_cpp11    0
#define COMPILE_FLAG_smartpointer   0
#define COMPILE_FLAG_thread_cpp11   0
#define COMPILE_FLAG_lambda         0
#define COMPILE_FLAG_other          1

class Primer{
public:
    Primer();
    ~Primer();
    int  primer_main(int argc, char **argv);
};

#endif //_PRIMER_HPP_

