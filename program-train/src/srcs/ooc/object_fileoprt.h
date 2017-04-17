/*
 * Progarm Name: object_fileoprt.h
 * Created Time: 2015/7/14
 * Last modified: 2016-11-27 18:24:34
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _OBJECT_FILEOPRT_H_
#define _OBJECT_FILEOPRT_H_
#ifdef __cplusplus
extern "C" {
#endif

/*文件对象数据定义*/
typedef struct _object_file{
    int open_close_state;

    int (*Open)(void *cthis);

    int (*Close)(void *cthis);

    size_t (*GetFileSize)(void *cthis);

    size_t (*GetFileLines)(void *cthis);

    int (*GetOpenCloseState)(void *cthis);

    int (*DelFile)(void *cthis);

    int (*IsExistence)(void *cthis);

    int (*ChangePath)(void *cthis, const char *str);

    const char *(*GetCurrentPath)(void *cthis);

    void (*GetCurrentPathCopy)(void *cthis, char *dstr);

    /* 文件尾部添加内容 */
    int (*AddFileContents_tail)(void *cthis, const char *str);
    /* 文件尾部添加内容，不需带'\0'结束标志 */
    int (*AddFileSizeContents_tail)(void *cthis, const char *str, unsigned int size);
    /* 文件头部添加内容 */
    int (*AddFileContents_top)(void *cthis, const char *str);
    /* 文件头部添加内容，不需带'\0'结束标志 */
    int (*AddFileSizeContents_top)(void *cthis, const char *str, unsigned int size);
    /* 文件指定部位添加内容 */
    int (*AddFileContents_insert)(void *cthis, const char *str, unsigned int insert_locate);
    /* 文件指定部位添加内容，不需带'\0'结束标志 */
    int (*AddFileSizeContents_insert)(void *cthis, const char *str, unsigned int size, unsigned int insert_locate);
    /* 文件指定行添加内容，添加一整行 */
    int (*AddFileLineContents_insert)(void *cthis, const char *str, unsigned int insert_line);
    /* 文件指定行添加size长度的内容，添加一整行，不需带'\0'结束标志 */
    int (*AddFileLineSizeContents)(void *cthis, const char *str, unsigned int size, unsigned int insert_line);
    
    /* 文件尾部删除size大小的内容 */
    int (*DelFileSizeContents_tail)(void *cthis, unsigned int size);
    /* 文件头部删除size大小的内容 */
    int (*DelFileSizeContents_top)(void *cthis, unsigned int size);
    /* 文件指定部位删除size大小的内容 */
    int (*DelFileSizeContents_locate)(void *cthis, unsigned int size, unsigned int locate);
    /* 文件全文删除指定符号对及符号对间的内容 */
    int (*DelFileContentsMatchSymbolPairing_all)(void *cthis, const char *symbol_pairing_str);
    /* 文件全文删除指定字符串的内容 */
    int (*DelFileContentsMatchString_all)(void *cthis, const char *str);
    /* 文件删除指定index(0-n)行内容 */
    int (*DelFileLineContents_index)(void *cthis, unsigned int index);

    /* 文件查找size大小的内容的个数-查找结束返回个数-没有则返回0 */
    size_t (*SearchFileContents_all)(void *cthis, const char *str);
    /* 文件查找size大小的内容的个数-查找第index(0-n)个相同内容，成功返回非0 locate值 */
    size_t (*SearchFileContentsGetLocate_index)(void *cthis, const char *str, unsigned int index);
    /* 文件查找size大小的内容的个数-查找第index(0-n)个相同内容，成功返回非0 line值 */
    size_t (*SearchFileContentsGetLine_index)(void *cthis, const char *str, unsigned int index);
    /* 文件读取指定位置开始的size长度的内容，返回读取的内容的指针 */
    const char *(*ReadFileSizeContents_locate)(void *cthis, unsigned int locate, unsigned int size);
    /* 文件读取指定位置开始的size长度的内容，并复制到dstr中 */
    void (*ReadFileSizeContentsCopy_locate)(void *cthis, unsigned int locate, unsigned int size, char *dstr);
    /* 文件读取指定位置开始，直到指定字符，返回读取的内容的指针 */
    const char *(*ReadFileContentsUntilSpecifySymbolchar_locate)(void *cthis, unsigned int locate, char symbol);
    /* 文件读取指定位置开始，直到指定字符，并复制到dstr中 */
    void (*ReadFileContentsUntilSpecifySymbolcharCopy_locate)(void *cthis, unsigned int locate, char symbol, char *dstr);
    /* 读取文件指定index(0-n)行的内容，返回读取的内容的指针 */
    const char *(*ReadFileContentsIndexLine)(void *cthis, unsigned int index);
    /* 读取文件指定index(0-n)行的内容，并复制到dstr中 */
    void (*ReadFileContentsIndexLineCopy)(void *cthis, unsigned int index, char *dstr);

    /* 更新文件内容，从指定位置开始更新str内容长度 */
    int (*UpdateFileContents_locate)(void *cthis, unsigned int locate, const char *str);
    /* 更新文件内容，从指定位置开始更新size长度的内容为str长度的数据 */
    int (*UpdateFileSizeContents_locate)(void *cthis, unsigned int locate, unsigned int size, const char *str);
    /* 更新文件内容，从指定行开始更新str内容 */
    int (*UpdateFileContents_line)(void *cthis, unsigned int index, const char *str);
    /* 更新文件内容，全文更新匹配符号对间的内容为str内容 */
    int (*UpdateFileContentsSymbolParing_all)(void *cthis, const char *symbol_paring_str, const char *str);

    /* 析构-释放内存，并将返回的地址清零 */
    void (*Destructor)(struct _object_file **pof);
}ObjectFile_t;

extern ObjectFile_t *ObjectFileConstructor(const char *str);

/*文件对象测试函数*/
extern ObjectFileOprtTest(void);

#ifdef __cplusplus
}
#endif
#endif //_OBJECT_FILEOPRT_H_

