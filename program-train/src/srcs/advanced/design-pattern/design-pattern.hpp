/*
 * Progarm Name: design-pattern.hpp
 * Created Time: 2017-02-14 10:04:10
 * Last modified: 2017-11-14 23:06:07
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DESIGN_PATTERN_HPP_
#define _DESIGN_PATTERN_HPP_

class DesignPattern{
public:
    DesignPattern();
    ~DesignPattern();
    int  do_action(void);
private:
    int  factory(void);
    int  abstract_factory(void);
    int  builder(void);
    int  prototype(void);
};

#endif //_DESIGN_PATTERN_HPP_

