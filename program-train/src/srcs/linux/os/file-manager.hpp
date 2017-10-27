/*
 * Progarm Name: file-manager.hpp
 * Created Time: 2017-10-27 21:15:21
 * Last modified: 2017-10-28 00:06:06
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FILE_MANAGER_HPP_
#define _FILE_MANAGER_HPP_

/* 
 * C++ 中的 3 个文件流
 *  1> ofstream 用于写文件  ofs("filename", mode)
 *  2> ifstream 用于读文件  ifs("filename", mode)
 *  3> fstream  用于读写文件 fs("filename", mode)
 *
 * mode : 
 *  1> ios::out     : 输出数据覆盖现有文件
 *  2> ios::app     : 输出数据添加到现有文件末尾
 *  3> ios::ate     : 打开文件并移动文件指针到末尾
 *  4> ios::in      : 打开文件以输入
 *  5> ios::trunc   : 输出文件中现有内容
 *  6> ios::binary  : 二进制打开供读写
 * */


#include <fstream>
#include <string>

using std::fstream;
using std::string;
using std::ifstream;
using std::ofstream;

class FileManager{
public:
    FileManager(const char *filename);
    ~FileManager();
private:
    int  test_for_fstream(void);
    int  test_for_iofstream(void);
private:
    string      m_fn;
    fstream     m_fs;
    ifstream    m_fs_in;
    ofstream    m_fs_out;
};

#endif //_FILE_MANAGER_HPP_

