/*
 * Progarm Name: other-string.hpp
 * Created Time: 2017-03-14 23:20:47
 * Last modified: 2017-03-14 23:24:57
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _OTHER_STRING_HPP_
#define _OTHER_STRING_HPP_

#include <string>
#include <vector>

using std::string;
using std::vector;

class OtherString{
public:
    OtherString();
    ~OtherString();
    int  main(int argc, char **argv);
private:
    int  find_reversal(string &result, const char *str = nullptr);
};

#endif //_OTHER_STRING_HPP_

