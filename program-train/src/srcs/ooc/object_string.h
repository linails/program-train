/*
 * Progarm Name: object_string.h
 * Created Time: 2015-07-14
 * Last modified: 2016-11-27 18:38:47
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _OBJECT_STRING_H_
#define _OBJECT_STRING_H_
#ifdef __cplusplus
extern "C" {
#endif

/* 字符串类型-包含字符串长度 */
typedef struct _ObjectString{

    char public_data;

    char private_data;

    void (*ReConstructor)(void *cthis, const char *str);

    const char *(*GetString)(void *cthis);

    void (*GetStringCopy)(void *cthis, char *dstr);

    unsigned short int (*GetLength)(void *cthis);

    /* 添加字符串到对象中-从原字符串后面添加 */
    const char *(*CatString)(void *cthis, const char *str);
    /* 添加字符串到对象中-从原字符串前面添加 */
    const char *(*CatOppoString)(void *cthis, const char *str);

    /* 字符串逆序调整 */
    const char *(*Invert)(void *cthis);
    /* 字符串逆序调整，并复制到dstr中 */
    void (*InvertCopy)(void *cthis, char *dstr);

    /* 字符字面值转换为十六进制,'4'-->0x04;'D'-->0x0d */
    const char *(*CharLiteralToHex)(void *cthis);
    /* 字符字面值转换为十六进制,'4'-->0x04;'D'-->0x0d，并复制到dstr中 */
    void (*CharLiteralToHexCopy)(void *cthis, char *dstr);

    /* 字符串字面值转换为十六进制,"78DC0A"-->0x78dc0a,只处理偶数个数 */
    const char *(*StrLiteralToHex)(void *cthis);
    /* 字符串字面值转换为十六进制,"78DC0A"-->0x78dc0a,只处理偶数个数，并复制到dstr中 */
    void (*StrLiteralToHexCopy)(void *cthis, char *dstr);

    /* 十进制字符串字面值转换为十进制整型-"12"->12 */
    const char *(*StrLiteralToInt)(void *cthis);
    /* 十进制字符串字面值转换为十进制整型-"12"->12，并复制到dstr中 */
    void (*StrLiteralToIntCopy)(void *cthis, char *dstr);

    /* 字符串比较，需带'\0'结束标志，如果相同返回0，不同返回-1 */
    int (*CmpString)(void *cthis, const char *str);
    /* 字符串比较，如果相同返回0，不同返回-1 */
    int (*CmpSizeString)(void *cthis, const char *str, unsigned short int size);
    /* 忽略大小写的字母字符串比较，需带'\0'结束标志，如果相同返回0，不同返回-1 */
    int (*CmpLetterStringIgnoreSensitive)(void *cthis, const char *str);
    /* 忽略大小写的字母字符串比较，如果相同返回0，不同返回-1 */
    int (*CmpSizeLetterStringIgnoreSensitive)(void *cthis, const char *str, unsigned short int size);

    /* 析构-释放内存，并将返回的地址清零 */
    void (*Destructor)(struct _ObjectString **pos);
}ObjectString_t;

/* 构造函数 */
extern ObjectString_t *ObjectStringConstructor(const char *str);

/* object string test function */
extern void ObjectStringTest(void);

#ifdef __cplusplus
}
#endif
#endif //_OBJECT_STRING_H_

