/*
 * Progarm Name: dic-parser.cpp
 * Created Time: 2016-12-15 22:09:28
 * Last modified: 2017-03-07 15:29:25
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
#include "alpha-bet.hpp"
#include <tuple>
#include <cstring>
#include <cstdio>
#include "format-later-stage.hpp"

using std::cout;
using std::endl;
using std::string;

DicParser *DicParser::instance = nullptr;

DicParser *DicParser::get_instance(DicParser *ptr)
{
    if(nullptr != ptr) instance = ptr; return instance;
}

DicParser::DicParser()
{
}

DicParser::~DicParser()
{
    this->uninit();
}

int  DicParser::dicparser_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->init(argc, argv); assert(-1 != ret);

    //ret = this->parser_xhzd(argc, argv); assert(-1 != ret);

    //ret = this->parser_xdhycd(argc, argv); assert(-1 != ret);

    //ret = this->parser_cycd(argc, argv); assert(-1 != ret);

    //ret = this->parser_hycddq(argc, argv); assert(-1 != ret);

    //ret = this->parser_hytycfyccd(argc, argv); assert(-1 != ret);

    //ret = this->spell_statistic(argc, argv); assert(-1 != ret);

    ret = this->later_stage_spell(argc, argv); assert(-1 != ret);

    return ret;
}

int  DicParser::init(int argc, char **argv)
{
    if(3 == argc){
        this->m_db = string(argv[2]);
        cout << "this->m_db : " << this->m_db << endl;
    }
    if(nullptr == this->m_disk){
        this->m_disk = new DiskDic(this->m_db);
    }
    return 0;
}

int  DicParser::uninit(void)
{
    if(nullptr != this->m_disk){
        delete this->m_disk;
        this->m_disk = nullptr;
    }
    return 0;
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
    auto print_line = [this](string line) ->void{
        static unsigned int index = 0;
        cout << endl;
        cout << "Line " << ++index << " : " << line << endl;
        cout << endl;
    };

    //ret = fo.read_linebyline(print_line);

    ret = fo.read_index_line(10000, dline, print_line);


    if(nullptr != this->m_disk){
        this->m_disk->init_tables();
    }

    /* 
     * used For bulk into database
     * */
    vector<pair<string, string> > word_spells;
    vector<string>                words;

    /* 
     *
     * */
    auto parser = [this, &word_spells, &words, &fn](string line) -> void{

        WordCell_t wc;

        formatTool ftool(fn,line);

        ftool.get_wordcell(wc);

        /* add in database */
        {
            #if 0
            if((nullptr != this->m_disk) && (wc.attr.size() == 2)){
                if(-1 != this->m_disk->insert_ws_word_spell(wc.word, wc.attr[1])){
                    cout << "insert ... succeed !" << endl;
                }
            }
            #else
            if(wc.attr.size() == 2){
                word_spells.push_back(make_pair(wc.word, wc.attr[1]));
            }else{
                words.push_back(wc.word);
                //word_spells.push_back(make_pair(wc.word, ""));
            }
            #endif
        }

        /* Print */
        #if 1
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
    //ret = fo.read_linebyline(parser);
    //ret = fo.read_index_line(1, dline, parser);

#if 0
    #if 1
    int index = 0;
    for(int i=0 + index; i<10 + index; i++){
        timer.timing();
        ret = fo.read_index_line(i, dline, parser);
        timer.timing();
    }
    #else
    ret = fo.read_index_line(1, dline, parser);
    #endif

#endif
    #if 0
    if(-1 != this->m_disk->insert_ws_word_spell(word_spells)){
        cout << "bulk insert succeed | <word, spell>" << endl;
    }
    #endif
    #if 0
    cout << "words.size() : " << words.size() << endl;
    if(-1 != this->m_disk->insert_ws_word(words)){
        cout << "bulk insert succeed | only word" << endl;
    }
    #endif

#if 1
    word_spells.clear();
    cout << "word_spells.size() : " << word_spells.size() << endl;
    this->m_disk->get_word_spell(word_spells);
    cout << "word_spells.size() : " << word_spells.size() << endl;

    vector<string> spells;
    this->m_disk->get_spell(spells, word_spells[0].first);

    words.clear();
    this->m_disk->get_words(words, 1);
    cout << "words.size() : " << words.size() << endl;

    spells.clear();
    this->m_disk->get_all_spells(spells);
    cout << "spells.size() : " << spells.size() << endl;

    #if 0
    stringTools st;
    for(auto spell : spells){
        cout << "spell : " << spell << endl;
        vector<string> alphas;
        st.split_utf_code(alphas, spell);
        //this->m_disk->insert_alphabet(alphas);
    }
    #endif

    AlphaBet abet;

    words.clear();
    this->m_disk->get_all_words_ws(words);
    abet.add_words(words);
    abet.add_spell(spells);

    vector<string> alphas;
    abet.get_alplas(alphas);
    cout << "alphas : "; for(auto &u : alphas) cout << u ; cout << "|" << endl;
    //this->m_disk->insert_alphabet(alphas, 0);

#endif
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

    if(nullptr != this->m_disk){
        this->m_disk->init_tables();
    }

    /* 
     *
     * */
    auto parser = [this, &fn](string line) -> void{

        WordCell_t wc;

        formatTool ftool(fn,line);

        ftool.get_wordcell(wc);

        cout << "line : " << line << endl;
        cout << "wc.word : " << wc.word << endl;
        cout << "wc.spel : " << wc.spell << endl;

        for(auto &u : wc.attr_xdhycd){
            cout << "wc.<char_|attr> : " << std::get<0>(u) << "|" << std::get<1>(u) << endl;
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

    int index = 41000;
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
    auto parser = [&fn](string line) -> void{

        WordCell_t wc;

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

int  DicParser::later_stage_xhzd(int argc, char **argv)
{
    return 0;
}

int  DicParser::later_stage_xdhycd(int argc, char **argv)
{
    return 0;
}

int  DicParser::later_stage_cycd(int argc, char **argv)
{
    return 0;
}

int  DicParser::later_stage_hytycfyccd(int argc, char **argv)
{
    return 0;
}

int  DicParser::spell_statistic(int argc, char **argv)
{
    int ret = 0;

    cout << "spell_statistic ..." << endl;

    string fn = "/home/minphone/share/exOrigin/log-spell-2";

    if(1 != argc){
        fn = string(argv[1]);
    }
    cout << "fn : " << fn << endl;

    Timer timer;
    timer.timing();
    rFileOprt fo(fn);
    timer.timing();

    Statistics statis;

    auto parser = [&statis](string line){
        stringTools     st;
        vector<string>  result;
        int             pos = -1;

        if((int)string::npos != (pos = line.find("spel : "))){

            string sline(line, pos + strlen("spel : "), string::npos);
            if(false == sline.empty()){
                st.split_utf_code(result, sline);

                for(auto &s : result){
                    cout << "s = " << s << endl;
                    statis.increase(s);
                }

                cout << "sline : " << line << endl;
            }
        }
    };

    string dline;
    ret = fo.read_linebyline(parser);
    //ret = fo.read_index_line(1000, dline, parser);

    map<string, float>  ret_statis;    // <'p', 0.243>,<'a', 0.534> ...
    statis.get_statis(ret_statis);

    for(auto &u : ret_statis){
        printf("(%s - %f)\n", u.first.c_str(), u.second);
    }

    return ret;
}

int  DicParser::later_stage_spell(int argc, char **argv)
{
    cout << "later - stage For spell !" << endl;

    int ret = 0;
    string fn = "/home/minphone/share/exOrigin/log-spell-2";

    if(1 != argc){
        fn = string(argv[1]);
    }
    cout << "fn : " << fn << endl;

    Timer timer;
    timer.timing();
    rFileOprt fo(fn);
    timer.timing();

    auto parser = [](string line){
        cout << "line = " << line << endl;
    };

    string dline;
    //ret = fo.read_linebyline(parser);
    ret = fo.read_index_line(1000, dline, parser);

    return ret;
}

DiskDic         *DicParser::get_disk(void){ return this->m_disk; }
Statistics      *DicParser::get_statistics(void){ return this->m_stati; }

