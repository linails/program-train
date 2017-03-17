/*
 * Progarm Name: other-string.hpp
 * Created Time: 2017-03-14 23:20:47
 * Last modified: 2017-03-16 09:44:27
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
    int  find_reversal(char *result, const char *str = nullptr);
};

#endif //_OTHER_STRING_HPP_

