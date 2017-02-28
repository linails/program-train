/*
 * Progarm Name: formatParsing.cpp
 * Created Time: 2016-05-15 12:14:11
 * Last modified: 2017-02-28 11:06:48
 * @author: minphone.linails linails@foxmail.com 
 */

#include "formatParsing.h"
#include <iostream>
#include <map>
#include <cstdio>
#include <cstdlib>
#include "regex_common.h"
#include "stringTools.h"
#include <cstring>
#include <cassert>
#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"
#include "segmentation.hpp"

using std::map;
using std::cout;
using std::endl;

/*format parsing for xinhuazidian*/
void formatTool::formatParsing_xhzd(string &s)
{
    #if 0
    /* 
     * Only For debug
     * */
    auto print_units = [](vector<string> &us){
        cout << "us.size() : " << us.size() << endl;
        for(auto &u : us){
            cout << "us : " << u << endl;
        }
    };
    #endif

    /* get wc.word */
    {
        regex_common_c0x("^[\\w\\W][^`<\\s]+", s, this->m_wc.word);

        stringTools st;

        char   buf[512] = {0, };
        sprintf(buf, "[ *1234567890·]");
        st.filter(buf, this->m_wc.word);
    }


    /* get wc.attr */
    {
        vector<string> units;

        regex_common_c0x("`\\d`[\\W\\w][^\\(]*", s, units);
        assert(units.size() == 1);

        regex_common_c0x("`\\d`[\\W\\w][^`<]*", units[0], this->m_wc.attr);

        stringTools st;
        char   buf[512] = {0, };
        sprintf(buf, "[ `*1234567890·]");
        for(size_t i=0; i<this->m_wc.attr.size(); i++){
            st.filter(buf, this->m_wc.attr[i]);
        }
    }


    /* get units */
    {
        vector<string> units;

        vector<string> patterns;
        patterns.push_back("(\\(\\d\\)).+?(?=\\(\\d\\))");
        patterns.push_back("(\\(\\d\\)).+$");
        this->regex_split(patterns, s, units);

        //print_units(units);

        /*
         * 针对 (10) 及以上的条目进行处理
         * */
        {
            auto filter_ = [](vector<string> &units){
                stringTools st;
                for(auto &u : units){
                    vector<string> result;
                    st.split_utf_code(result, u);
                    if("(" == result[result.size()-2]){
                        result.pop_back();
                        result.pop_back();
                    }
                    st.utf_code2string(u, result);
                }
            };

            if(9 <= units.size()){
                vector<string> subunits;

                vector<string> subpatterns;
                subpatterns.push_back("(\\d\\)).+?(?=\\d\\))");
                subpatterns.push_back("(\\d\\)).+$");
                this->regex_split(subpatterns, units[8], subunits);
                {
                    if(false == subunits.empty()){
                        cout << "subunits.size() = " << subunits.size() << endl;
                        filter_(subunits);
                        
                        for(size_t i=0; i<subunits.size(); i++){
                            if(0 == i) units[8] = subunits[i];
                            else       units.push_back(subunits[i]);
                        }
                    }
                }
            }
        }

        vector<string> subunits;
        for(auto iter = units.begin();
                 iter!= units.end(); iter++){

            regex_common_c0x("<br>[^<]+", *iter, subunits);
            if(false == subunits.empty()){
                for(auto iiter = subunits.begin();
                         iiter!= subunits.end(); iiter++){
                    iiter->erase(0, iiter->find_first_not_of("<br>"));
                }
                this->m_wc.contents.push_back(subunits);
            }

            subunits.clear();
        }


        /*
         * filter this->m_wc.contents 
         * */
        {
            stringTools st;
            for(auto &vu : this->m_wc.contents){
                for(auto &u : vu){
                    st.filter("∶ -", u);

                    vector<string> result; 
                    vector<string> remain; 
                    st.split_utf_code(result, u);
                    do{
                        remain.clear();
                        auto end   = find(result.begin(), result.end(), "]");
                        auto begin = find(result.begin(), result.end(), "[");

                        if(begin > end){ end = find(begin, result.end(), "]"); }
                        if((begin != result.end()) && (end != result.end())){
                            for(auto iter = result.begin();
                                     iter!= result.end(); iter++){
                                if((iter < begin) || (iter >end)){
                                    remain.push_back(*iter);
                                }
                            }
                            st.utf_code2string(u, remain);
                        }else{
                            st.utf_code2string(u, result);
                        }

                        result = remain;
                        //print_units(result);
                    }while(remain.end() != find(remain.begin(), remain.end(), "["));
                }
            }
        }

    }
}

/*format parsing for xiandaihanyucidian*/
void formatTool::formatParsing_xdhycd(string &s)
{
    stringTools st;
    st.filter("[<]-[>]", s);

    /* get wc.word 
     * 1> "^.[^*<\\s]+" */
    regex_common_c0x("^.[^*<\\s]+", s, this->m_wc.word);

    char   buf[512] = {0, };
    string bref(s, 0, s.find("①"));

    sprintf(buf, "[ *1234567890·%s]", this->m_wc.word.c_str());
    st.filter(buf, bref);
    this->m_wc.spell = bref;

    if(1 < st.utf_count(this->m_wc.word)){
        this->m_wc.spell = string(bref, bref.find("]") + 1, string::npos);

        #if 0
        vector<string> words;
        jieba.Cut(this->m_wc.spell, words, true);
        cout << "words : "; for(auto &s : words) cout << s << " / "; cout << endl;
        #endif
    }

    /* get wc.attr */
    {
        vector<string> units;

        stringTools st(s);
        st.match("[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮○]-[^①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮○]", units);
        for(auto &u : units) st.filter("[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮○1234567890]", u);
        this->m_wc.attr = units;

        #if 0
        for(auto &us : units){
            vector<string> words;
            jieba.Cut(us, words, true);
            cout << "word- : "; for(auto &s : words) cout << s << " / "; cout << endl;
        }
        #endif
    }

}

/*format parsing for chengyucidian*/
void formatTool::formatParsing_cycd(string &s)
{
    /* get wc.word */
    {
        regex_common_c0x("^[\\w\\W][^<\\s]+", s, this->m_wc.word);
        stringTools st;
        st.filter("\"", this->m_wc.word);
    }

    /* get wc.attr */
    {
    }
}

/*format parsing for chengyucidiandaquan*/
void formatTool::formatParsing_hycddq(string &s)
{
}

/*format parsing for hanyutongyicifanyicicidian*/
void formatTool::formatParsing_hytycfyccd(string &s)
{
}

//---------------------------------------------------------

const char *formatTool::property_words[]  = {
    "名",
    "〈方〉",
    "副",
    "数",
    "形",
    "动",
    ""
};

const char *formatTool::fnameList[] = {
    "cycd.txt",
    "hycddq.txt",
    "hytycfyccd.txt",
    "xdhycd.txt",
    "xhzd.txt"
};

void (formatTool::* formatTool::formatParsingList[])(string &) = {
    &formatTool::formatParsing_cycd,
    &formatTool::formatParsing_hycddq,
    &formatTool::formatParsing_hytycfyccd,
    &formatTool::formatParsing_xdhycd,
    &formatTool::formatParsing_xhzd
};

/* 
 * For jieba dics
 * */
const char *const formatTool::DICT_PATH      = "../src/libs/cppjieba/dict/jieba.dict.utf8";
const char *const formatTool::HMM_PATH       = "../src/libs/cppjieba/dict/hmm_model.utf8";
const char *const formatTool::USER_DICT_PATH = "../src/libs/cppjieba/dict/user.dict.utf8";
const char *const formatTool::IDF_PATH       = "../src/libs/cppjieba/dict/idf.utf8";
const char *const formatTool::STOP_WORD_PATH = "../src/libs/cppjieba/dict/stop_words.utf8";

//Jieba formatTool::jieba(formatTool::DICT_PATH, formatTool::HMM_PATH, formatTool::USER_DICT_PATH);

formatTool::formatTool(std::string fname,std::string line)
    :m_fname(&fname[fname.rfind('/') + 1])
    ,m_line(line)
{
    for(int i = 0; i < (int)(sizeof(fnameList)/sizeof(*fnameList)); i++){
        if(0 == this->m_fname.compare(fnameList[i])){
            (this->*formatParsingList[i])(this->m_line);
            break;
        }
    }
}

formatTool::~formatTool()
{
}

int  formatTool::regex_split(vector<string> &patterns, string &s, vector<string> &units)
{
    int ret = 0;

    char *ptr = new char[s.size() + 1];

    if(nullptr != ptr){

        size_t len = 0;
        vector<string> last;

        regex_common_c0x(patterns[0].c_str(), s, units);
        if(0 != units.size()){

            memcpy(ptr, s.c_str(), s.size());
            ptr[s.size()] = '\0';

            for(auto &u : units) len += u.size();

            if(len < s.size()){
                string sptr = &ptr[len];
                regex_common_c0x(patterns[1].c_str(), sptr, last);

                if(last.size() > 0){
                    units.push_back(last[0]);
                }
            }
        }else{
            units.push_back(s);
        }

        delete [] ptr;
    }else{
        ret = -1;
        cout << "[Error] new failed !" << endl;
    }

    return ret;
}

int  formatTool::get_wordcell(WordCell_t &wc)
{
    wc = this->m_wc;

    return 0;
}

