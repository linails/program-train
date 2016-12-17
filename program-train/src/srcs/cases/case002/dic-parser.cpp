/*
 * Progarm Name: dic-parser.cpp
 * Created Time: 2016-12-15 22:09:28
 * Last modified: 2016-12-17 19:31:11
 * @author: minphone.linails linails@foxmail.com 
 */

#include "dic-parser.hpp"
#include <iostream>
#include "rfileoprt.h"
#include "rwfileoprt.h"
#include "formatParsing.h"
#include "timer.h"
#include <string>

using std::cout;
using std::endl;
using std::string;

DicParser::DicParser()
{
}

DicParser::~DicParser()
{
}

int  DicParser::dicparser_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->parser_xhzd(argc, argv);

    return ret;
}
    
int  DicParser::parser_xhzd(int argc, char **argv)
{
    cout << "parser_xhzd ..." << endl;

    int ret = 0;

    string fn = "/home/minphone/space_sdc/workspace/"
                "dic_parse/dicparse/src/dic/xhzd.txt";

    string dline;

    if(1 != argc){
        fn = string(argv[1]);
    }
    cout << "fn : " << fn << endl;


    Timer timer;
    timer.timing();
    rFileOprt fo(fn);
    timer.timing();


    auto print_line = [](string line) ->void{
        static unsigned int index = 0;
        cout << endl;
        cout << "Line " << ++index << " : " << line << endl;
        cout << endl;
    };

    //ret = fo.read_linebyline(print_line);

    ret = fo.read_index_line(10000, dline, print_line);

    ret = formatPrint(fn, dline);

    return ret;
}


