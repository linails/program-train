/*
 * Progarm Name: tester-case001.hpp
 * Created Time: 2017-03-23 17:10:49
 * Last modified: 2017-04-11 17:25:44
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TESTER_CASE001_HPP_
#define _TESTER_CASE001_HPP_

#include <vector>
#include <string>
#include "dev-avl-tree.hpp"
#include "dev-child-sibling-tree.hpp"

using std::vector;
using std::string;

class TesterCase001{
public:
    TesterCase001();
    ~TesterCase001();
    int  main(int argc, char **argv);
private:
    int  infinite_loops(void);
    int  child_sibling(void);
    int  avl(void);
    int  convert(void);
    int  convert_case01(void);
    int  convert_case02(void);
    int  convert_cs2avl_tree(DevAVLTree *avltree, DevChildSiblingTree *cstree);
    void print_tree(DevChildSiblingTree *tree);
    static int  visit(avlNode *node);
private:
    int             m_argc;
    vector<string>  m_argvs;
};

#endif //_TESTER_CASE001_HPP_

