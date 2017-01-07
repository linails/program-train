/*
 * Progarm Name: class-def.hpp
 * Created Time: 2017-01-07 13:19:07
 * Last modified: 2017-01-07 13:22:33
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CLASS_DEF_HPP_
#define _CLASS_DEF_HPP_

class OnlyHpp{
public:
    OnlyHpp(int data = 10);
    OnlyHpp(const OnlyHpp &oh);
    ~OnlyHpp();
    int get_data(void) const;
private:
    int m_data;
};

//-----------------------------------------------------------------------------

OnlyHpp::OnlyHpp(int data)
    :m_data(data)
{
}

OnlyHpp::OnlyHpp(const OnlyHpp &oh)
{
    this->m_data = oh.m_data;
}

OnlyHpp::~OnlyHpp()
{
}

int OnlyHpp::get_data(void) const
{
    return this->m_data;
}

#endif //_CLASS_DEF_HPP_

