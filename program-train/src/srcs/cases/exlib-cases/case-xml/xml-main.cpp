/*
 * Progarm Name: xml-main.cpp
 * Created Time: 2017-03-09 14:02:40
 * Last modified: 2017-03-09 15:27:08
 * @author: minphone.linails linails@foxmail.com 
 */

#include "xml-main.hpp"
#include <iostream>
#include "xml-parser.hpp"
#include <cassert>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

xmlMain::xmlMain()
{
}

xmlMain::~xmlMain()
{
}

int  xmlMain::main(int argc, char **argv)
{
    int ret = 0;

    cout << "xmlMain ... " << endl;
    {
        string file;
        if(1 != argc){
            cout << "argv[1] : " << argv[1] << endl;
            file = argv[1];
        }

        cout << "file = " << file << endl;


        xmlParser *xml = nullptr;

        xml = new xmlParser(file);

        sleep(5);
        xml->test();

        while(1){
            sleep(5);
            xml->test();
        }

        delete xml;
        xml = nullptr;
    }

    return ret;
}

