/*
 * Progarm Name: exlibCases.hpp
 * Created Time: 2016-12-21 10:06:04
 * Last modified: 2017-03-31 13:49:02
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _EXLIBCASES_HPP_
#define _EXLIBCASES_HPP_

#define COMPILE_FLAG_exlib_json     0
#define COMPILE_FLAG_exlib_gtest    0
#define COMPILE_FLAG_exlib_xml      0

class exlibCases{
public:
    exlibCases();
    ~exlibCases();
    int  exlibcases_main(int argc, char **argv);
private:
};

#endif //_EXLIBCASES_HPP_

