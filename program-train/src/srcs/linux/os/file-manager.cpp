/*
 * Progarm Name: file-manager.cpp
 * Created Time: 2017-10-27 21:15:24
 * Last modified: 2017-10-28 00:24:18
 * @author: minphone.linails linails@foxmail.com 
 */

#include "file-manager.hpp"
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

FileManager::FileManager(const char *filename)
    :m_fn(filename)
{
    //this->test_for_fstream();

    this->test_for_iofstream();
}

FileManager::~FileManager()
{
}

int  FileManager::test_for_fstream(void)
{
    //this->m_fs.open(this->m_fn, std::ios::out | std::ios::in);
    this->m_fs.open(this->m_fn, std::ios::out);

    //cout << "Fn = " << __func__ << endl;
    //std::ofstream file(this->m_fn);

    this->m_fs << "hello";

    //this->m_fs.close();
    //this->m_fs.open(this->m_fn, std::ios::out | std::ios::in);

    this->m_fs << "nice to meet you" << endl;
    this->m_fs.close();

    this->m_fs.open(this->m_fn, std::ios::in);
    string s;

    this->m_fs >> s;
    cout << "s = " << s << endl;


    if(this->m_fs.is_open()){
        cout << "m_fs is open() ; now is close()..." << endl;
        this->m_fs.close();
    }

    cout << "---------------------------" << endl;
    return 0;
}

int  FileManager::test_for_iofstream(void)
{
    this->m_fs_in.open(this->m_fn, std::ios::in | std::ios::app);
    this->m_fs_out.open(this->m_fn, std::ios::out | std::ios::app);

    string o("write to file");
    char buf[1024] = {0, };
    this->m_fs_in.read(buf, 100);
    cout << "buf = " << buf << endl;

    this->m_fs_out.write(o.c_str(), o.length());

    this->m_fs_in.seekg(0, std::ios::beg);
    memset(buf, 0, sizeof(buf));
    this->m_fs_in.read(buf, 100);
    cout << "buf = " << buf << endl;

    if(this->m_fs_in.is_open()){
        cout << "m_fs_in is open , now close() ..." << endl;
        this->m_fs_in.close();
    }

    if(this->m_fs_out.is_open()){
        cout << "m_fs_out is open , now close() ..." << endl;
        this->m_fs_out.close();
    }

    return 0;
}


