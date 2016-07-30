/*
 * Progarm Name: drived_test.h
 * Created Time: 2015-12-05 22:57:35
 * Last modified: 2016-07-28 17:46:33
 */

#ifndef _DRIVED_TEST_H_
#define _DRIVED_TEST_H_

extern void drived_test(void);

class ObjBase{
public:
    ObjBase();
    virtual ~ObjBase();
    void func01(void);
    void func02(void);
    virtual void func03(void);
    virtual void display(void);
protected:
    int var_base;
private:
};

class ObjDrived : public ObjBase {
public:
    ObjDrived();
    void func02(void);
    /*如果定义了纯虚函数，则为抽象基类，不能够定义此类对象
     * ObjDrived drived 则是错误的*/
//    virtual void func03(void) =0;
    virtual ~ObjDrived();
    virtual void display(void);
protected:
    int var_drived;
private:
    int flag;
};

#endif //_DRIVED_TEST_H_

