/*
 * Progarm Name: cases.hpp
 * Created Time: 2016-12-15 22:15:13
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CASES_HPP_
#define _CASES_HPP_

#include "manager.hpp"
#include "cfg-loader.hpp"

#define COMPILE_FLAG_exlibCases    1
#define COMPILE_FLAG_case001       0
#define COMPILE_FLAG_case002       0
#define COMPILE_FLAG_case003       0
#define COMPILE_FLAG_case004       0
#define COMPILE_FLAG_case005       0    // TS-parser
#define COMPILE_FLAG_case006       0    // code-formatter
#define COMPILE_FLAG_case_other    0

class Cases{
public:
    Cases();
    ~Cases();
    int  cases_main(int argc, char **argv);
private:
    int  case_for_code_formatter(void);
private:
    CfgLoader      *m_xml_cfg = nullptr;
};

#endif //_CASES_HPP_

