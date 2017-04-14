/*
 * Progarm Name: lambda.h
 * Created Time: 2016-03-28 20:57:11
 * Last modified: 2016-12-18 11:49:27
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
    int  mlambda_cb(void);
    static int  callback(char *s);
};

#endif //_LAMBDA_H_

