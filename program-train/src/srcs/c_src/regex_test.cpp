/*
 * Progarm Name: regex_test.cpp
 * Created Time: 2016-05-16 10:55:53
 * Last modified: 2016-05-17 22:05:40
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

    void regex_t1(void);
    regex_t1();
    cout << "-------------------------------------" << endl;
}

void regex_t1(void)
{
    char *pattern = "regex[a-z]*";
    int  x;
    int  z;
    int  lno = 0;
    int  cflags = 0;
    char ebuf[128];
    char *lbuf;
    regex_t reg;
    regmatch_t pm[10];

    char *data[] = {
        "rege",
        "nljregexb",
        "nlkjregexcd,dnijgregexdddnojg",
        "hlojlnregexccccd",
        "joiuregexabc",
        "gccsderegexdddd,doijgregexxx",
        "doingregrx",
        "recex",
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
        lbuf = data[i];
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




