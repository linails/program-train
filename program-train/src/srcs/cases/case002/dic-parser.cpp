/*
 * Progarm Name: dic-parser.cpp
 * Created Time: 2016-12-15 22:09:28
 * Last modified: 2017-02-27 17:53:53
 * @author: minphone.linails linails@foxmail.com 
 */

#include "dic-parser.hpp"
#include <iostream>
#include "rfileoprt.h"
#include "rwfileoprt.h"
#include "formatParsing.h"
#include "timer.h"
#include <string>
#include <algorithm>
#include "stringTools.h"
#include <cassert>
#include "format-parser.hpp"
#include "disk-dic.hpp"

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

    ret = this->parser_xhzd(argc, argv); assert(-1 != ret);

    //ret = this->parser_xdhycd(argc, argv); assert(-1 != ret);

    //ret = this->parser_cycd(argc, argv); assert(-1 != ret);

    //ret = this->parser_hycddq(argc, argv); assert(-1 != ret);

    //ret = this->parser_hytycfyccd(argc, argv); assert(-1 != ret);

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


    /* 
     *
     * */
    auto print_line = [](string line) ->void{
        static unsigned int index = 0;
        cout << endl;
        cout << "Line " << ++index << " : " << line << endl;
        cout << endl;
    };

    //ret = fo.read_linebyline(print_line);

    ret = fo.read_index_line(10000, dline, print_line);

    //ret = formatPrint(fn, dline);



    /* 
     *
     * */
    auto parser = [](string line) -> void{

        WordCell_t wc;
        string fn = "/home/minphone/space_sdc/workspace/"
                    "dic_parse/dicparse/src/dic/xhzd.txt";

        formatTool ftool(fn,line);

        ftool.get_wordcell(wc);

        /* Print */
        #if 0
        cout << "line : " << line << endl;
        cout << "wc.word : " << wc.word << endl;
        for(auto &u : wc.attr){
            cout << "wc.attr : " << u << endl;
        }

        int index = 0;
        for(auto &uv : wc.contents){
            index++;
            for(auto &u : uv){
                printf("[%d]cout : %s\n", index, u.c_str());
            }
        }
        cout << endl;
        #endif
    };

    //ret = fo.read_index_line(10000, dline, parser);
    ret = fo.read_linebyline(parser);
    //ret = fo.read_index_line(2, dline, parser);

    return ret;
}

int  DicParser::parser_xdhycd(int argc, char **argv)
{
    cout << "parser_xdhycd ..." << endl;

    int ret = 0;

    string fn = "/home/minphone/space_sdc/workspace/"
                "dic_parse/dicparse/src/dic/xdhycd.txt";

    string dline;

    if(1 != argc){
        fn = string(argv[1]);
    }
    cout << "fn : " << fn << endl;


    Timer timer;
    timer.timing();
    rFileOprt fo(fn);
    timer.timing();


#if 0
    /* 
     *
     * */
    auto print_line = [](string line) ->void{
        static unsigned int index = 0;
        cout << endl;
        cout << "Line " << ++index << " : " << line << endl;
        cout << endl;
    };

    //ret = fo.read_linebyline(print_line);

    //ret = fo.read_index_line(10000, dline, print_line);
#endif

#if 0
    auto filter = [](string line) -> void{
        #if 0
        static size_t index = 0;
        static size_t maxlen = 0;

        index++;

        # if 1
        if(line.size() > maxlen){
            maxlen = line.size();

            cout << endl;
            cout << "Line " << index << " : " << line << endl;
            cout << endl;
        }
        # else
        int cnt = count(line.begin(), line.end(), '<');
        if(cnt > maxlen){
            maxlen = cnt;

            cout << endl;
            cout << "Line " << index << " : " << line << endl;
            cout << endl;
        }
        # endif
        #else
        static size_t max = 0;

        WordCell_t wc;
        string fn = "/home/minphone/space_sdc/workspace/"
                    "dic_parse/dicparse/src/dic/xdhycd.txt";

        formatTool ftool(fn,line);

        ftool.get_wordcell(wc);

        if(wc.attr.size() > max){
            //cout << "line : " << line << endl;
            cout << "wc.word : " << wc.word << endl;
            for(auto &u : wc.attr){
                cout << "wc.attr : " << u << endl;
            }

            int index = 0;
            for(auto &uv : wc.contents){
                index++;
                for(auto &u : uv){
                    printf("[%d]cout : %s\n", index, u.c_str());
                }
            }
            cout << endl;
            max = wc.attr.size();
        }

        #endif
    };

    ret = fo.read_linebyline(filter);
#endif

    /* 
     *
     * */
    auto parser = [](string line) -> void{

        WordCell_t wc;
        string fn = "/home/minphone/space_sdc/workspace/"
                    "dic_parse/dicparse/src/dic/xdhycd.txt";

        formatTool ftool(fn,line);

        ftool.get_wordcell(wc);

        //cout << "line : " << line << endl;
        cout << "wc.word : " << wc.word << endl;
        cout << "wc.spel : " << wc.spell << " - " << wc.spell.length();

#if 0
        for(int i=0; i<wc.spell.length(); i++){
            unsigned char c = wc.spell[i];
            printf("%d-%c ", c, c);
        }
#endif
        cout << endl;

        for(auto &u : wc.attr){
            cout << "wc.attr : " << u << endl;
        }

        int index = 0;
        for(auto &uv : wc.contents){
            index++;
            for(auto &u : uv){
                printf("[%d]cout : %s\n", index, u.c_str());
            }
        }
        cout << endl;
    };


#if 1
    #if 0
    timer.timing();
    ret = fo.read_index_line(41779, dline, parser);
    timer.timing();

    timer.timing();
    ret = fo.read_index_line(26347, dline, parser);
    timer.timing();

    timer.timing();
    ret = fo.read_index_line(17078, dline, parser);
    timer.timing();
    #else

    int index = 18000;
    for(int i=0 + index; i<10 + index; i++){
        timer.timing();
        ret = fo.read_index_line(i, dline, parser);
        timer.timing();
    }
    #endif
#else

    timer.timing();
    ret = fo.read_linebyline(parser);
    timer.timing();
#endif

    return ret;
}

int  DicParser::parser_cycd(int argc, char **argv)
{
    cout << "parser_cycd ..." << endl;

    int ret = 0;

    string fn = "/home/minphone/space_sdc/workspace/"
                "dic_parse/dicparse/src/dic/cycd.txt";

    string dline;

    if(1 != argc){
        fn = string(argv[1]);
    }
    cout << "fn : " << fn << endl;


    Timer timer;
    timer.timing();
    rFileOprt fo(fn);
    timer.timing();

    /* 
     *
     * */
    auto parser = [](string line) -> void{

        WordCell_t wc;
        string fn = "/home/minphone/space_sdc/workspace/"
                    "dic_parse/dicparse/src/dic/cycd.txt";

        formatTool ftool(fn,line);

        ftool.get_wordcell(wc);

        cout << "wc.word : " << wc.word << " - size : " << wc.word.size() << endl;
        for(auto &u : wc.attr){
            cout << "wc.attr : " << u << endl;
        }

        int index = 0;
        for(auto &uv : wc.contents){
            index++;
            for(auto &u : uv){
                printf("[%d]cout : %s\n", index, u.c_str());
            }
        }
        cout << endl;
    };


    timer.timing();
    ret = fo.read_index_line(1779, dline, parser);
    timer.timing();

#if 0
    timer.timing();
    ret = fo.read_index_line(6347, dline, parser);
    timer.timing();

    timer.timing();
    ret = fo.read_index_line(7078, dline, parser);
    timer.timing();
#endif

    timer.timing();
    //ret = fo.read_linebyline(parser);
    timer.timing();

    FormatParser fp;

    return ret;
}

int  DicParser::parser_hycddq(int argc, char **argv)
{
    int ret = 0;

    return ret;
}

int  DicParser::parser_hytycfyccd(int argc, char **argv)
{
    int ret = 0;

    return ret;
}

