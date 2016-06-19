/*
 * Progarm Name: regex_cpp11.cpp
 * Created Time: 2016-06-16 11:24:06
 * Last modified: 2016-06-19 14:46:25
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "regex_cpp11.h"

/*gcc-5.3*/
/*c++11 regex*/
#include <regex>
#include <iostream>

using namespace std;

regex_cpp11::regex_cpp11()
{
}

regex_cpp11::~regex_cpp11()
{
}

void regex_cpp11::regex_t4(void)
{
    {
        cout << "---------------------------------------------------------" << endl;
        string pattern("[^c]ei");
        pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";

        regex r(pattern);
        smatch results;

        string test_str("receipt freind theif receive");
        if(regex_search(test_str, results, r)){
            cout << results.str() << endl;
        }
    }
    {
        cout << "---------------------------------------------------------" << endl;
        /*
         * reference : cnblogs.com/zhuyp1015/archive/2012/04/08/2438215.html
         * */

        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

        string email1("marius.bancila@domain.com");
        string email2("mariusbancila@domain.com");
        string email3("marius_b@domain.co.uk");
        string email4("marius@domain");

        cout << email1 << " : " << (regex_match(email1,pattern) ? "valid" : "invalid") << endl;
        cout << email2 << " : " << (regex_match(email2,pattern) ? "valid" : "invalid") << endl;
        cout << email3 << " : " << (regex_match(email3,pattern) ? "valid" : "invalid") << endl;
        cout << email4 << " : " << (regex_match(email4,pattern) ? "valid" : "invalid") << endl;
    }
    {
        cout << "---------------------------------------------------------" << endl;
        string str("亶1	`1`亶1`2`dǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义 [full of grains]<br>亶,多谷也。――《说文》<br>择三有事,亶侯多藏。――《诗·小雅·十月之交》<br>(3)<br>厚道;忠实 [kind and sincere]<br>亶,信也;又,诚也。――《尔雅》<br>不实于亶。――《诗·大雅·板》<br>(4)<br>又如:亶厚(忠厚,淳厚);亶诚(真诚)<br>(5)<br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)<br>(6)<br>姓");

        cout << "string : " << str << endl;

        const regex pattern("`\\d`");
        smatch      result;

        bool regbool = regex_search(str, result, pattern);

        cout << "regex search: " << (regbool ? "true" : "false") << endl;

        if(true == regbool){
            cout << "result : " << result.str() << endl;
        }

        str = "`1`";

        regbool = regex_match(str,pattern);
        cout << "regex match : " << (regbool ? "true" : "false") << endl;
    }
    {
        cout << "---------------------------------------------------------" << endl;
        /*
         * reference : cnblogs.com/zhuyp1015/archive/2012/04/08/2438232.html
         * */
        regex pattern("\\w+day");

        string weekend("Saturday and Sunday, but some Fridays also.");
        sregex_token_iterator end;

        for(sregex_token_iterator i(weekend.begin(), weekend.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
        }
    }
    {
        cout << "---------------------------------------------------------" << endl;
        string str("亶1	`1`亶1`2`dǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义 [full of grains]<br>亶,多谷也。――《说文》<br>择三有事,亶侯多藏。――《诗·小雅·十月之交》<br>(3)<br>厚道;忠实 [kind and sincere]<br>亶,信也;又,诚也。――《尔雅》<br>不实于亶。――《诗·大雅·板》<br>(4)<br>又如:亶厚(忠厚,淳厚);亶诚(真诚)<br>(5)<br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)<br>(6)<br>姓");

        regex pattern("`\\d`\\w{0,3}");
        sregex_token_iterator end;

        for(sregex_token_iterator i(str.begin(), str.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
        }
    }
}


//---------------------------------------------------------


