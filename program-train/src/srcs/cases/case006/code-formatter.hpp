/*
 * Progarm Name: code-formatter.hpp
 * Created Time: 2017-08-09 18:48:55
 * Last modified: 2017-08-09 19:07:07
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CODE_FORMATTER_HPP_
#define _CODE_FORMATTER_HPP_

#include <string>

using std::string;

class CodeFormatter{
public:
    CodeFormatter(string cfg);
    ~CodeFormatter();
private:
    string      m_cfg;  // 配置文件
};

#endif //_CODE_FORMATTER_HPP_

