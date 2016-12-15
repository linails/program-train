/*
 * Progarm Name: dic-parser.hpp
 * Created Time: 2016-12-15 22:09:32
 * Last modified: 2016-12-15 22:31:46
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DIC_PARSER_HPP_
#define _DIC_PARSER_HPP_

class DicParser{
public:
    DicParser();
    ~DicParser();
    int  dicparser_main(int argc, char **argv);
private:
    int  parser_xhzd(int argc, char **argv);
};

#endif //_DIC_PARSER_HPP_

