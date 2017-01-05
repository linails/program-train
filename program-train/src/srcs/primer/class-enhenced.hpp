/*
 * Progarm Name: class-enhenced.hpp
 * Created Time: 2017-01-05 09:00:11
 * Last modified: 2017-01-05 09:03:22
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CLASS_ENHENCED_HPP_
#define _CLASS_ENHENCED_HPP_

#include <string>
#include <vector>

using std::string;
using std::vector;

class ClassEnhenced{
public:
    ClassEnhenced();
    ~ClassEnhenced();
    int  class_enhenced_main(int argc, char **argv);
private:
    int  copy_ctrl(void);
};

#endif //_CLASS_ENHENCED_HPP_

