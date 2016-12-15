/*
 * Progarm Name: stringTools.h
 * Created Time: 2016-05-26 19:47:33
 * Last modified: 2016-12-15 22:07:42
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _STRINGTOOLS_H_
#define _STRINGTOOLS_H_

#include <string>
#include <vector>

/*
 * stringTools 
 *  pattern 1: usual pattern
 *  pattern 2: {`1`, ,[1-9],`,`[1-9]`}
 * */
class stringTools{
public:
    stringTools(std::string &str);
    stringTools(const char *str);
    ~stringTools();

    /*filter success return 0
     *  pattern 2: {`1`, ,[1-9],`,`[1-9]`}
     * */
    int filter(const char *pattern2, std::string &unit);
    int filter(const char *pattern2, char *unit);
private:
    int get_pattern_mode(const char *pattern);
    int get_subpatterns(const char *pattern);
private:
    std::string              m_str;
    std::string              m_pattern;
    std::vector<std::string> m_subpatterns;
};




#endif //_STRINGTOOLS_H_

