/*
 * Progarm Name: code-formatter.hpp
 * Created Time: 2017-08-09 18:48:55
 * Last modified: 2017-08-10 09:23:30
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CODE_FORMATTER_HPP_
#define _CODE_FORMATTER_HPP_

#include <string>
#include "rfileoprt.h"

using std::string;

class CodeFormatter{
public:
    CodeFormatter(string cfg, string dir);
    ~CodeFormatter();
private:
private:
    string          m_cfg;  // 配置文件
    string          m_dir;
    rFileOprt      *m_rfo = nullptr;
};

#endif //_CODE_FORMATTER_HPP_

