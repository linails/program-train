/*
 * Progarm Name: class-def.hpp
 * Created Time: 2017-01-07 13:19:07
 * Last modified: 2017-02-17 16:14:27
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CLASS_DEF_HPP_
#define _CLASS_DEF_HPP_

/* 
 * Note :
 *
 *  这种定义方法是不可取的 ！
 *  
 *  本头文件在被多个文件包含的时候，会发生重复定义的问题
 *  实现如果也定义在头文件中，则采用定义在类内部
 * */
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

