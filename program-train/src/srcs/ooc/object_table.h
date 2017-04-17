/*
 * Progarm Name: object_table.h
 * Created Time: 2015/7/21
 * Last modified: 2016-11-27 18:44:47
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _OBJECT_TABLE_H_
#define _OBJECT_TABLE_H_
#ifdef __cplusplus
extern "C" {
#endif

/* 定义表信息 */
typedef struct{
    size_t unit_counts;                 //单元项数
    size_t unit_size;                   //单元大小
    size_t start_locate;                //单元起始地址
    const char * forward_cluster_name;  //前关联簇名
    const char * next_cluster_name;     //后关联簇名
}TableInfo_t;

/* 定义表对象 */
typedef struct _object_table{
    struct _object_table *_this;

    /* 重新构造 */
    void (*ReConstructor)(void *cthis, const char *table_name);

    int (*Open)(void *cthis);

    int (*Close)(void *cthis);

    int (*Backup)(void *cthis);

    TableInfo_t *(*GetTableInfo)(void *cthis);

    void (*GetTableInfoCopy)(void *cthis, TableInfo_t *pti);

    size_t (*GetTableUnitCounts)(void *cthis);

    int (*SetTableBackupPath)(void *cthis, const char *string);

    int (*RenameTable)(void *cthis, const char *table_name);

    int (*IsExistence)(void *cthis);

    const char *(*GetTableRelationClusterHead)(void *cthis);

    int (*GetTableRelationClusterHeadCopy)(void *cthis, char *dname);

    const char *(*GetTableRelationClusterForward)(void *cthis);

    int (*GetTableRelationClusterForwardCopy)(void *cthis, char *dname);

    const char *(*GetTableRelationClusterNext)(void *cthis);

    int (*GetTableRelationClusterNextCopy)(void *cthis, char *dname);

    const char *(*GetTableRelationClusterTail)(void *cthis);

    int (*GetTableRelationClusterTailCopy)(void *cthis, char *dname);


    //增



    //删



    //查



    //改



    /* 析构-释放内存，并将返回的地址清零 */
    void (*Destructor)(struct _object_table **pot);
}ObjectTable_t;

extern ObjectTable_t *ObjectTableConstructor(const char *table_name);

#ifdef __cplusplus
}
#endif
#endif //_OBJECT_TABLE_H_

