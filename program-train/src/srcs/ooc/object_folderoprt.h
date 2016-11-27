/*
 * Progarm Name: object_folderoprt.h
 * Created Time: 2015/7/14
 * Last modified: 2016-11-27 18:34:44
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _OBJECT_FOLDEROPRT_H_
#define _OBJECT_FOLDEROPRT_H_
#ifdef __cplusplus
extern "C" {
#endif

/* 文件夹对象数据定义 */
typedef struct _object_folder{

    /* 获得文件夹当前路径 */
    const char *(*GetCurrentPath)(void *cthis);
    /* 获得文件夹当前路径，并复制到dstr中 */
    void (*GetCurrentPathCopy)(void *cthis, char *dstr);

    /* 析构-释放内存，并将返回的地址清零 */
    void (*Destructor)(struct _object_folder **pof);
}ObjectFolder_t;

extern ObjectFolder_t *ObjectFolderConstructor(const char *str);

#ifdef __cplusplus
}
#endif
#endif //_OBJECT_FOLDEROPRT_H_

