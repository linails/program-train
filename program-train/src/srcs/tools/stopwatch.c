/*
 * Progarm Name: stopwatch.c
 * Created Time: 2017-07-25 10:21:24
 * Last modified: 2017-07-26 18:35:20
 * @author: minphone.linails linails@foxmail.com 
 */

#include "stopwatch.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   //for gettimeofday()
#include <string.h>

#define NAME_LENGTH 256

typedef struct swNode_{
    struct swNode_ *pforward;
    struct swNode_ *pnext;
    struct timeval  stamp;
}swNode_t;

typedef struct swRoot_{
    char            name[NAME_LENGTH];
    struct swRoot_ *pright;
    struct swNode_ *pstamp;
    struct timeval  stamp;
}swRoot_t;

/* 
 * map structure:
 *
 *   next  |  next
 *-----------------------------------------------
 *  swRoot -> root -> root -> root -> root -> ...
 *    |        |       |       |       |    
 *  stamp    stamp   stamp   stamp   stamp
 *    |        |       |       |       |    
 *  stamp    stamp   stamp   stamp   stamp
 *    |        |       |       |       |    
 *  stamp    stamp   stamp   stamp   stamp
 *
 * */
static swRoot_t swRoot =  {{0, }, NULL, NULL, };

/**************************** stopwatch MGR *********************************/

static
swRoot_t *new_root(void)
{
    swRoot_t *root = (swRoot_t *)malloc(sizeof(swRoot_t));
    if(NULL == root){
        printf("[Error] : malloc swRoot_t failed !\n");
        root = NULL;
    }else{
        memset(root->name, 0, NAME_LENGTH);
        root->pright = NULL;
        root->pstamp = NULL;
        memset((char *)&root->stamp, 0, sizeof(struct timeval));
    }

    return root;
}

static
swNode_t *new_node(void)
{
    swNode_t *node = (swNode_t *)malloc(sizeof(swNode_t));
    if(NULL == node){
        printf("[Error] : malloc swNode_t failed !\n");
        node = NULL;
    }else{
        node->pforward = NULL;
        node->pnext    = NULL;
        memset((char *)&node->stamp, 0, sizeof(struct timeval));
    }

    return node;
}

static
swRoot_t *seek_for_root(const char *name, swRoot_t **pforward)
{
    swRoot_t *root = &swRoot;

    if(NULL != pforward) *pforward = NULL;

    do{
        if(0 == strcmp(name, root->name)){
            break;
        }else{
            if(NULL != pforward) *pforward = root;
            root = root->pright;
        }
    }while(NULL != root);

    return root;
}

static
int  add_root(const char *name)
{
    int ret = 0;
    char tmp[NAME_LENGTH] = {0, };
    swRoot_t *root = &swRoot;

    /* 
     * 1. swRoot is empty
     * */
    if(0 == strcmp(root->name, tmp)){
        root->pright = NULL;
        root->pstamp = NULL;
        gettimeofday(&root->stamp, NULL);
        memcpy(root->name, name, strlen(name));
    }else{

        while(1){
            if(NULL == root->pright){
                swRoot_t *r = new_root();
                if(NULL != r){
                    root->pright = r;
                    gettimeofday(&r->stamp, NULL);
                    memcpy(r->name, name, strlen(name));
                }else{
                    ret = -1;
                }
                break;
            }else{
                root = root->pright;
            }
        }
    }

    return ret;
}

static
int  del_root(const char *name)
{
    int ret = 0;
    swRoot_t *forward = NULL;
    swRoot_t *root = seek_for_root(name, &forward);

    if(NULL != root){
        do{
            swNode_t *pstamp = root->pstamp;
            root->pstamp = root->pstamp->pnext;

            if(NULL != pstamp) free(pstamp);

        }while(NULL != root->pstamp);

        if(root == &swRoot){
            swRoot_t *pright = root->pright;

            if(NULL != pright){
                root->pright = pright->pright;
                root->pstamp = pright->pstamp;
                memcpy(root->name, pright->name, strlen(pright->name));
                memcpy((char *)&root->stamp, (char *)&pright->stamp, sizeof(struct timeval));
                free(pright);
            }else{
                memset(root->name, 0, NAME_LENGTH);
                memset((char *)&root->stamp, 0, sizeof(struct timeval));
            }
            
        }else{
            forward->pright = root->pright;
            free(root);
        }
    }else
        ret = -1;
 
    return ret;
}

static 
char *calc_timing(char *buf, struct timeval *pstart, struct timeval *pstop)
{
    unsigned sec, msec, usec;
    unsigned hour, min;

    unsigned usec_start = pstart->tv_sec * 1000 * 1000 + pstart->tv_usec;
    unsigned usec_stop  = pstop->tv_sec * 1000 * 1000 + pstop->tv_usec;

    usec = usec_stop - usec_start;

    msec = usec/1000;
    usec -= msec * 1000;

    sec  = msec / 1000;
    msec -= sec * 1000;
    min = sec/60;
    sec -= min*60;
    hour = min/60;
    min -= hour*60;

    sprintf(buf,"[H:M:S:ms:us] %.2d:%.2d:%.2d:%.3d:%.3d"
            ,hour,min,sec,msec,usec);

    return buf;
}

/**************************** stopwatch operator *********************************/

/* 
 * used like this:
 *
 * sw_start(__FILE__);
 * sw_start(__FUNCTION__);
 * */
int  sw_start(const char *name)
{
    int ret = 0;
    swRoot_t *root = seek_for_root(name, NULL);

    if(NULL != root){
        if(0 != del_root(name)){
            printf("[Error] sw_start failed !\n");
            ret = -1;
        }
        if(0 != add_root(name)){
            printf("[Error] sw_start failed !\n");
            ret = -1;
        }
    }else{
        if(0 != add_root(name)){
            printf("[Error] sw_start failed !\n");
            ret = -1;
        }
    }

    return ret;
}

/* 
 * used like this:
 *
 * | start           stamp   stop
 * +---^---+---+---+---^---+---^--
 * |      -3  -2  -1   0
 *
 * sw_stamp(__FUNCTION__, -1, __LINE__, ""); | [H:M:S:ms:us] 00:00:00:100:000
 * sw_stamp(__FUNCTION__, -2, __LINE__, ""); | [H:M:S:ms:us] 00:00:00:200:000
 * sw_stamp(__FUNCTION__, -3, __LINE__, ""); | [H:M:S:ms:us] 00:00:00:300:000
 *
 * 1. Default forward = -1
 * 2. if forward = 0, stamp() print out [H:M:S:ms:us] 00:00:00:000:000
 * */
int  sw_stamp(const char *name, int forward, int line, const char *tag)
{
    int ret = 0;
    swRoot_t *root = seek_for_root(name, NULL);

    if(NULL != root){
        swNode_t *tail = root->pstamp;

        if(NULL != tail){
            while(NULL != tail->pnext){
                tail = tail->pnext;
            };

            tail->pnext = new_node();

            if(NULL != tail->pnext){
                tail->pnext->pforward = tail;
                tail->pnext->pnext    = NULL;
                gettimeofday(&tail->pnext->stamp, NULL);

                swNode_t *stop = tail->pnext;
                swNode_t *start= stop;

                while(forward++){
                    if(NULL != start) start = start->pforward;
                    else              break;
                }

                char buf[NAME_LENGTH] = {0, };
                if(NULL == start){
                    printf("Timing stamp ! : %s  -- [Fn:%s | Line:%d | Tag:%s] \n",
                            calc_timing(buf, &root->stamp, &stop->stamp),
                            name, line, tag);
                }else{
                    printf("Timing stamp ! : %s  -- [Fn:%s | Line:%d | Tag:%s] \n",
                            calc_timing(buf, &start->stamp, &stop->stamp),
                            name, line, tag);
                }
            }else{
                printf("[Error] sw_stamp new_node() failed !\n");
                ret = -1;
            }

        }else{
            /* 
             * for first node
             * */
            root->pstamp = new_node();
            if(NULL != root->pstamp){
                gettimeofday(&root->pstamp->stamp, NULL);

                swNode_t *stop = root->pstamp;
                swNode_t *start= stop;

                while(forward++){
                    if(NULL != start) start = start->pforward;
                    else              break;
                }

                char buf[NAME_LENGTH] = {0, };
                if(NULL == start){
                    printf("Timing stamp ! : %s  -- [Fn:%s | Line:%d | Tag:%s] \n",
                            calc_timing(buf, &root->stamp, &stop->stamp),
                            name, line, tag);
                }else{
                    printf("Timing stamp ! : %s  -- [Fn:%s | Line:%d | Tag:%s] \n",
                            calc_timing(buf, &start->stamp, &stop->stamp),
                            name, line, tag);
                }
            }else{
                printf("[Error] sw_stamp new_node() failed !\n");
                ret = -1;
            }
        }

    }else{
        printf("[Error] sw_stamp failed - [Fn:%s]!\n", name);
        ret = -1;
    }

    return ret;
}

/*
 * stop timing and release list
 *
 * used like this:
 *
 * sw_stop(__FILE__);
 * sw_stop(__FUNCTION__);
 * */
int  sw_stop(const char *name)
{
    int ret = 0;
    swRoot_t *root = seek_for_root(name, NULL);

    if(NULL != root){
        if(0 != del_root(name)){
            printf("[Error] sw_stop failed !\n");
            ret = -1;
        }
    }

    return ret;
}


