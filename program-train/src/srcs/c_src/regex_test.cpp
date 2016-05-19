/*
 * Progarm Name: regex_test.cpp
 * Created Time: 2016-05-16 10:55:53
 * Last modified: 2016-05-19 14:14:23
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "regex_test.h"
#include <sys/types.h>
#include <regex.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

/*regex test func*/
void regex_test(void)
{
    cout << "-------------regex test--------------" << endl;

    //void regex_t1(void);
    //regex_t1();
    //

    void regex_t3(void);
    regex_t3();

#if 0
    void regex_t4(void);
    regex_t4();
#endif

#if 0
    /*eg. c++ boost xpressive*/
    void regex_t5(void);
    regex_t5();
#endif

    cout << "-------------------------------------" << endl;
}

void regex_t1(void)
{
    char *pattern = (char *)"regex[a-z]*";
    unsigned int  x;
    int  z;
    int  lno = 0;
    int  cflags = 0;
    char ebuf[128];
    char *lbuf;
    regex_t reg;
    regmatch_t pm[10];

    const char *data[] = {
        "rege",
        "nlj regexb djo",
        "nlkjregexcd,dnijgregexdddnojg",
        "hlojlnregexccccd",
        "joiuregexabc",
        "gccsderegexdddd,doijgregexxx",
        "doingregrx",
        "doij recex joi",
        "regexojhogijregjoiregxjoijregexddoij",
        "redex",
        "noijregexln",
        "regexddi"
    };

    const size_t nmatch = 10;

    z = regcomp(&reg,pattern,cflags);
    if(z != 0){
        regerror(z,&reg,ebuf,sizeof(ebuf));
        printf("%s : pattern '%s'\n",ebuf,pattern);
        return;
    }

#if 1
    for(int i=0; i<12; i++){
        lbuf = (char *)data[i];
        ++lno;

        z = regexec(&reg,lbuf,nmatch,pm,0);
        if(z == REG_NOMATCH) continue;
        else if(z != 0){
            regerror(z,&reg,ebuf,sizeof(ebuf));
            printf("%s : pattern '%s'\n",ebuf,pattern);
            return;
        }

        for(x = 0; x<nmatch&&pm[x].rm_so != -1; ++x){
            if(!x)
                printf("%04d: %s\n",lno,lbuf);

            string s(lbuf);
            printf(" $%d='%s'\n",x,s.substr(pm[x].rm_so,pm[x].rm_eo).c_str());
        }
    }
#endif
}

void regex_t2(void)
{
    /* 1. (<br>)?\(\d\)
     * 2. */
    char *pattern = (char *)"(<br>)?\\(\\d\\)";
    printf("pattern : %s\n",pattern);

    //char *pattern = (char *)"<br>";
    unsigned int  x;
    int  z;
    int  cflags = REG_EXTENDED;
    char ebuf[128];
    char *lbuf;
    regex_t reg;
    regmatch_t pm[10];

    const char *data[] = {
         "亶1	`1`亶1`2`dǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义 [full of grains]<br>亶,多谷也。――《说文》<br>择三有事,亶侯多藏。――《诗·小雅·十月之交》<br>(3)<br>厚道;忠实 [kind and sincere]<br>亶,信也;又,诚也。――《尔雅》<br>不实于亶。――《诗·大雅·板》<br>(4)<br>又如:亶厚(忠厚,淳厚);亶诚(真诚)<br>(5)<br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)<br>(6)<br>姓"

    };

    const size_t nmatch = 10;

    /*
     * pattern : 指向正则表达式
     * cflags  : 有4个值
     *  {
     *   REG_EXTENDED  :以功能更加强大的扩展正则表达式进行匹配
     *   REG_ICASE     :匹配字母时忽略大小写
     *   REG_NOSUB     :不用存储匹配后的结果
     *   REG_NEWLINE   :识别换行符,这样'$'就可以从行尾开始匹配，'^'就可以从行头匹配
     *  }
     * */
    z = regcomp(&reg,pattern,0);
    if(z != 0){
        regerror(z,&reg,ebuf,sizeof(ebuf));
        printf("%s : pattern '%s'\n",ebuf,pattern);
        return;
    }else{
        cout << "regcomp success " << endl;
    }

    lbuf = (char *)data[0];

    z = regexec(&reg,lbuf,nmatch,pm,0);
    if(z == REG_NOMATCH){
        cout << "reg nomatch : " << z << endl;
        regerror(z,&reg,ebuf,sizeof(ebuf));
        printf("%s : pattern '%s'\n",ebuf,pattern);
    }else{
        for(x = 0; x< nmatch&&pm[x].rm_so != -1; ++x){
            //printf(" $%d='%s'\n",x,s.substr(pm[x].rm_so,pm[x].rm_eo).c_str());

            void print_substr(char *str,int begin,int end);
            print_substr(lbuf,pm[x].rm_so,pm[x].rm_eo);
        }
    }
}

void print_substr(char *str,int begin,int end)
{
    while(begin <= end){
        printf("%c",str[begin++]);
    }
}

/*eg. from IBM knowledge center*/
void regex_t3(void)
{
    regex_t     preg;
#if 0
    //char        *string = "a very simple simple simple string";
    //char        *pattern = "\\(sim[a-z]le\\) \\1";
    char        *string = "averysimple<si>simple<sd>4stringdǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义";
    //char        *pattern = "<s[id]>";
    char        *pattern = "<br>\\(";
#else
#if 1
    char        *pattern = (char *)"([1-9])<br>";
    char        *string = "亶1	`1`亶1`2`dǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义 [full of grains]<br>亶,多谷也。――《说文》<br>择三有事,亶侯多藏。――《诗·小雅·十月之交》<br>(3)<br>厚道;忠实 [kind and sincere]<br>亶,信也;又,诚也。――《尔雅》<br>不实于亶。――《诗·大雅·板》<br>(4)<br>又如:亶厚(忠厚,淳厚);亶诚(真诚)<br>(5)<br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)<br>(6)<br>姓";
#endif
#endif
    int         rc;
    size_t      nmatch = 2;
    regmatch_t  pmatch[2] = {0,};

    if(0 != (rc = regcomp(&preg, pattern, 0))){
        printf("regcomp() failed, returning nonzero (%d)\n", rc);
        return;
    }

    int pos = 0;
    while(1){
        if(0 != (rc = regexec(&preg, &string[pos], nmatch, pmatch, 0))){
            printf("Failed to match '%s' with '%s',returnning %d.\n",
                    string, pattern, rc);
            break;
        }else{
            static int times = 0;
            printf("match %d : ",times++);
            print_substr(&string[pos], pmatch[0].rm_so, pmatch[0].rm_eo - 1);
            cout << endl;

#if 0
            printf("With the whole expression, "
                   "a matched substring \"%.*s\" is found at position %d to %d.\n",
                   pmatch[0].rm_eo - pmatch[0].rm_so, &string[pmatch[0].rm_so],
                   pmatch[0].rm_so, pmatch[0].rm_eo - 1);
            printf("With the sub-expression, "
                   "a matched substring \"%.*s\" is found at position %d to %d.\n",
                   pmatch[1].rm_eo - pmatch[1].rm_so, &string[pmatch[1].rm_so],
                   pmatch[1].rm_so, pmatch[1].rm_eo - 1);
#endif

            pos += pmatch[0].rm_eo - 1;
        }
    }

    regfree(&preg);
    return;
}

#include <regex>

void regex_t4(void)
{
    //const std::regex pattern("(<br>)?\\(\\d\\)");
    //const std::regex pattern("<br>\\(");
    const std::regex pattern("\\d?\\d");

    std::match_results<std::string::const_iterator> result;

    string s = " 8979 878 666 567 565778";

    //string  s = "亶1	`1`亶1`2`dǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义 [full of grains]<br>亶,多谷也。――《说文》<br>择三有事,亶侯多藏。――《诗·小雅·十月之交》<br>(3)<br>厚道;忠实 [kind and sincere]<br>亶,信也;又,诚也。――《尔雅》<br>不实于亶。――《诗·大雅·板》<br>(4)<br>又如:亶厚(忠厚,淳厚);亶诚(真诚)<br>(5)<br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)<br>(6)<br>姓";

    bool valid = std::regex_match(s,result,pattern);
    if(valid == true){
        if(result.empty() != true)
            cout << "reg00 : " << result[0] << endl;
    }
}


//---------------------------------------------------------

#if 0
#include <xpressive/xpressive.hpp>

/*eg. c++ boost xpressive*/
void regex_t5(void)
{
    using namespace boost::xpressive;

    cregex reg = cregex::compile("a.c");

    assert(regex_match("abc", reg));
    assert(regex_match("a+c", reg));

    assert(regex_match("ac", reg));
    assert(regex_match("abd", reg));
}

#endif


