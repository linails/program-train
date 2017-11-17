/*
 * Progarm Name: c-primer.c
 * Created Time: 2016-12-09 23:18:58
 * Last modified: 2017-11-16 16:53:17
 * @author: minphone.linails linails@foxmail.com 
 */

#include "c-primer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctest.h"
#include <stdarg.h>
#include "jump.h"
#include "clib-eg-linux.h"
#include "dbgprint.h"
#include "malloc.h"

static
int  cprimer_main(cPrimer_t *cthis, int argc, char **argv)
{
    printf(" cprimer_main ...\n");

    int ret = 0;

    if(NULL != cthis){

        ret = cthis->other_test();

        ret = cthis->process_token();

        ret = cthis->para_uncertainty(cthis);

        ret = cthis->gnu_c();

        ret = cthis->bit_field();

        ret = cthis->endian_check();

        {
            cJumper_t *cjumper = NULL;

            if(0 == cjumper_constructor_safety(&cjumper)){

                if(NULL != cjumper){
                    printf("cjumper constructor successed !\n");

                    if(0 != (ret = cjumper->cjumper_main((void *)cjumper, 0, NULL))){
                        printf("[Error] : cjumper->cjumper_main() failed \n");
                    }

                    if(0 == cjumper->destructor(&cjumper)){
                        printf("cjumper destructor successed !\n");
                    }
                }
            }
        }

        ret = cthis->clibegLinux();

        ret = cthis->cstatic_assert();

        ret = cthis->malloc_test();

    }else{
        ret = -1;
        printf("[Warning] cthis is NULL !\n");
    }
    return ret;
}

static
int  other_test(void)
{
    printf(" --- other-test ---\n");
    {
        typedef union {
            int     a;
            char    b[5];
        }iso_u;

        printf("sizeof(iso_u) : %d\n", (int)sizeof(iso_u));

        /* 
         * Note : union 虽然不常直接定义变量，不过直接定义变量的时候，初始化只能初始化第一个成员的类型
         * */
        iso_u iso = {8};

        printf("iso.a = %d\n", iso.a);

    }
    printf("-------------------\n");
    {
        int array[3] = {1, 2, 3};

        printf("%x, %x\n", (unsigned int)(long)(array+1), (unsigned int)(long)(&array+1));
        printf(" - %x \n", (unsigned int)(long)(&array+1) - (unsigned int)(long)(array+1));
    }
    printf("-------------------\n");
    {
        /* 
         * 总线错误示例， 在 RISC 架构的CPU上容易出现
         * */
        union {
            char a[10];
            int  b;
        }u;

        int *p = (int *)&(u.a[1]);

        *p = 12;
        printf("*p = %d\n", *p);
    }

    printf("\n");

    return 0;
}

static
int  process_token(void)
{
    printf("process_token ...\n");

    /* 
     * "##" 运算符在宏定义中是构造特定的 "预处理单词" 的用途
     *
     *  #define XY x##y             : 被展开成 xy
     *  #define HASH_HASH # ## #    : 被展开成 ##, 两边的空格是必须的
     *  #define S(a,b) a##b         : S(1,2) -> 12 ; S(x,y) -> xy
     * */

    #define S(x,y) x##y

    printf("S(1,2) : %d\n", S(1,2));

    return 0;
}

static
int  para_uncertainty(cPrimer_t *cthis)
{
    /* 
     * 可变参数类型
     *  eg. #include <stdio.h>
     *      int printf(const char*, ...);
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     *  "..." 这个标点符号只用于函数声明和定义(此处还用于宏)
     *        它的作用是让编译器对出现在这部分的实参与形参不做类型与个数的检查
     *
     *  [注意：如果有其他参数，则 ... 只能用于指定最后面的参数]
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     *  为了保证不确定参数函数代码的可移植性，C语言标准库提供了一套宏
     *
     *  #include <stdarg.h>
     *  1> va_list ap   : 这个 ap 用于遍历各个"..."中的参数
     *  2> va_start(ap, 最后一个确定参数的类型) : 这是让 ap 获得初始值，即指向第一个可变参数
     *  3> va_arg(ap, 可变参数类型) : 求取当前可变参数的值，并把 ap 移至下一个可变参数
     *  4> va_copy(dst, src)    : C99内容，可以复制一个 ap 的副本，在src被改变的情况下，还可以重新从前面读取参数
     *  5> va_end(ap)   : 清理工作
     * */
    int ret = 0;

    printf("para_uncertainty ...\n");

    ret = cthis->pu_fun(1, 10);

    ret = cthis->pu_fun(2, 10, 20);

    return ret;
}

static
int  pu_fun(int n, ...)
{
    printf("call ... function \n");

    int ret = 0;

    printf("\nva_start ... \n");
    {
        int para = 0;

        va_list ap;
        va_start(ap, n);
        for(int i=0; i<n; i++){
            para = va_arg(ap, int);
            printf("para[%d] = %d\n", i, para);
        }
        va_end(ap);
    }
    printf("\nva_end ... \n");

    return ret;
}

static
int  gnu_c(void)
{
    int ret = 0;

    printf("-----------GNU-C-----------\n");

    /*  
     *  GNU C : 零长度和变量长度数组
     *  */
    {
        /* 
         * 1> int data[0] 仅仅意味着程序中通过 var_data 结构体实例的 data[index] 成员可以访问 len 之后的第
         *    index 个地址，它并没有为 data[] 数组分配内存
         * 2> 因此，sizeof(struct var_data) = sizeof(int)
         * */
        struct var_data{
            int len;
            int data[0];
        };

        printf("sizeof(var_data) : %d\n", (int)sizeof(struct var_data));
    }
    printf("---------------------------\n");
    {
        int  index = 10;
        char data[index];
        /* 
         *  错误用法
         *
         *  char data[index] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; -> Error
         *  char data[10]    = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; -> OK
         * */

        printf("sizeof(data) : %d\n", (int)sizeof(data));
    }
    printf("---------------------------\n");
    {
        /* 
         * case x ... y 语法, 表示满足区间 [x, y] 的 case
         * */
        int index = 13;

        switch(index){
            case 1 ... 10 :
                printf("index : %d -> case 1 ... 10 \n", index);
                break;
            case 11 ... 20 :
                printf("index : %d -> case 11 ... 20 \n", index);
                break;
            default:
                break;
        }

        char ch = 'f';

        switch(ch){
            case '0' ... '9':
                printf("ch : %c --> case '0' ... '9' \n", ch);
                break;
            case 'a' ... 'z':
                printf("ch : %c --> case 'a' ... 'z' \n", ch);
                break;
            case 'A' ... 'Z':
                printf("ch : %c --> case 'A' ... 'Z' \n", ch);
                break;
            default:
                break;
        }
    }
    printf("---------------------------\n");
    {
        /* 
         * 指定数组索引号的方法来初始化
         * */

        int data[30] = {[0 ... 20] = 99};

        printf("data : ");
        for(int i=0; i<30; i++){
            printf("%.2d ", data[i]);
        }
        printf("\n");

        int dat[30] = {[20] = 99};

        printf("dat : ");
        for(int i=0; i<30; i++){
            printf("%.2d ", dat[i]);
        }
        printf("\n");
    }
    printf("---------------------------\n");
    {
        #pragma pack(1)
        typedef struct {
            int  a;
            char b;
        }Data_t;

        printf("#pragma pack(1) sizeof(Data_t) = %d\n", (int)sizeof(Data_t));
        #pragma pack()

        /* 
         * packed 使用该属性可以使得变量或结构体成员使用最小的对齐方式，即对变量是一字节对齐，对域是位对齐
         * */
        typedef struct{
            int  a;
            char b;
        }__attribute__((packed))
        Data_attr_t;

        printf("__attribute__((packed)) sizeof(Data_attr_t) = %d\n", (int)sizeof(Data_attr_t));
    }
    printf("---------------------------\n");
    {
        #pragma pack()
        typedef struct {
            int  a;
            char b;
        }Data_t;

        printf("#pragma pack() sizeof(Data_t) = %d\n", (int)sizeof(Data_t));
        #pragma pack()

        typedef struct{
            int  a;
            char b;
        }__attribute__((aligned(1)))
        Data_attr_t;

        printf("__attribute__((aligned(1))) sizeof(Data_attr_t) = %d\n", (int)sizeof(Data_attr_t));
    }
    printf("---------------------------\n");
    {
        #pragma pack(2)
        typedef struct {
            int  a;
            char b;
        }Data_t;

        printf("#pragma pack(2) sizeof(Data_t) = %d\n", (int)sizeof(Data_t));
        #pragma pack()
    }

    return ret;
}

static
int  bit_field(void)
{
    int ret = 0;

    {
        printf("c-primer::bit_field ...\n");
    }
    printf("---------------------------\n");
    {
        /* 
         * 这个跟大小端有直接关系
         * */
        typedef struct{
            char a:1,
                 b:1,
                 c:1,
                 d:1,
                 e:4;
        }Data_t;

        Data_t data;

        data.a = 0;
        data.b = 0;
        data.c = 0;
        data.d = 0;
        data.e = 1;

        char x = *(char *)&data;
        printf("x = 0x%.2x\n", x);
    }
    printf("---------------------------\n");
    {
        printf("bit_field section 2 \n");

        typedef struct{
            unsigned char a:7;
            unsigned char b:1;
        }Data_t;

        unsigned char x = 0x80;

        Data_t d = *(Data_t *)&x;

        printf("x = 0x%.2x\n", x);
        printf("d.a = 0x%.2x\n", d.a);
        printf("d.b = 0x%.2x\n\n", d.b);

        Data_t d0;
        d0.b = 1;

        unsigned char x0 = *(unsigned char *)&d0;
        printf("d0.b = 0x%.2x\n", d0.b);
        printf("x0 = 0x%.2x\n\n", x0);

        Data_t d1;

        d1.a = x & ~0x80;
        d1.b = (x & 0x80) >> 7;     // Note ! b 这个时候属于高位，需要移动对于基位的偏移 7
        printf("x = 0x%.2x\n", x);
        printf("x & 0x80 = 0x%.2x\n", x & 0x80);
        printf("d1.a = 0x%.2x\n", d1.a);
        printf("d1.b = 0x%.2x\n", d1.b);
    }
    printf("---------------------------\n");
    return ret;
}

static
int  endian_check(void)
{
    int ret = 0;

    unsigned int data = 1;

    if(0x01 == (*(char *)&data)){
        printf("c-primer::endian_check : Little endian\n");
    }else{
        printf("c-primer::endian_check : Big endian\n");
    }
    printf("---------------------------\n");

    return ret;
}

static
int  clibegLinux(void)
{
    cLibEgLinux_t *clibeg_linux = NULL;

    if(0 == cLibEg_linux_constructor_safety(&clibeg_linux)){
        if(NULL != clibeg_linux){
            clibeg_linux->clibegLinux_main(clibeg_linux, 0, NULL);

            clibeg_linux->destructor(&clibeg_linux);
        }
    }

    return 0;
}

static
int  cstatic_assert(void)
{
    /*
     * 静态断言，用于编译期运算检测出代码错误
     * 不需要在运行时才检测出错误，因为运行的时候，有些 assert() 可能不会运行到
     * */
    assert_static(1 != 2); // 这句就可以正常编译

    //assert_static(1 == 2); // 这句会在编译期检测出来错误

    return 0;
}

static
int  malloc_test(void)
{
    printf("---------------------------\n");

    /* 
     * malloc_usable_size(); 返回实际可以使用的内存
     * */
    printf("Fn: %s\n", __func__);
    {
        char *pbufa = malloc(60);
        if(NULL != pbufa){
            /*
             * 输出的大小是 72 字节 | 时间的内存管理相关的东西，malloc 会实际分配大于申请的大小
             * */
            printf("pbufa size = %ld\n", malloc_usable_size(pbufa));

            free(pbufa);
        }

        char *pbufb = malloc(32);
        if(NULL != pbufb){
            /*
             * 输出的大小是 40 字节
             * */
            printf("pbufb size = %ld\n", malloc_usable_size(pbufb));

            free(pbufb);
        }

    }
    printf("---------------------------\n");
    return 0;
}

//----------------------------------------------------------------------------------------------

static
int  destructor(cPrimer_t **pobj)
{
    if(NULL != *pobj){
        free(*pobj);
        *pobj = NULL;
        return 0;
    }else{
        printf("[Error] destructor is failed , because *pobj is null\n");
        return -1;
    }
}

cPrimer_t *cprimer_constructor(void)
{
    cPrimer_t *cprimer = (cPrimer_t *)malloc(sizeof(cPrimer_t));
    if(NULL == cprimer){
        printf("[Error] malloc failed\n");
        return NULL;
    }else{

        /* 
         * Loading all functions here !
         * */

        cprimer->other_test         = other_test;
        cprimer->destructor         = destructor;
        cprimer->process_token      = process_token;
        cprimer->para_uncertainty   = para_uncertainty;
        cprimer->pu_fun             = pu_fun;
        cprimer->gnu_c              = gnu_c;
        cprimer->bit_field          = bit_field;
        cprimer->endian_check       = endian_check;
        cprimer->cstatic_assert     = cstatic_assert;
        cprimer->cprimer_main       = cprimer_main;
        cprimer->malloc_test        = malloc_test;

        return cprimer;
    }
}

int  cprimer_constructor_safety(cPrimer_t **pobj)
{
    int ret = 0;

    if(NULL == *pobj){
        *pobj = (cPrimer_t *)malloc(sizeof(cPrimer_t));

        if(NULL == *pobj){
            printf("[Error] constructor -> malloc failed\n");
            ret = -1;
        }else{

            /* 
             * Loading all functions here !
             * */

            (*pobj)->other_test         = other_test;
            (*pobj)->destructor         = destructor;
            (*pobj)->process_token      = process_token;
            (*pobj)->para_uncertainty   = para_uncertainty;
            (*pobj)->pu_fun             = pu_fun;
            (*pobj)->gnu_c              = gnu_c;
            (*pobj)->bit_field          = bit_field;
            (*pobj)->endian_check       = endian_check;
            (*pobj)->clibegLinux        = clibegLinux;
            (*pobj)->cstatic_assert     = cstatic_assert;
            (*pobj)->cprimer_main       = cprimer_main;
            (*pobj)->malloc_test        = malloc_test;

        }
    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}

