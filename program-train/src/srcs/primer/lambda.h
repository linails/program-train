/*
 * Progarm Name: lambda.h
 * Created Time: 2016-03-28 20:57:11
 * Last modified: 2017-11-02 10:23:46
 */

#ifndef _LAMBDA_H_
#define _LAMBDA_H_

class mLambda{
public:
    mLambda();
    ~mLambda();
    int  mlambda_main(int argc, char **argv);
private:
    int  mlambda_test(void);

    /*
     * vector 中 push 进 lambda 表达式
     * */
    int  mlambda_test_(void);

    int  mlambda_cb(void);
    static int  callback(char *s);
};

#endif //_LAMBDA_H_

