/*
 * Progarm Name: sort.c
 * Created Time: 2017-06-10 15:42:58
 * Last modified: 2017-06-22 23:48:04
 * @author: minphone.linails linails@foxmail.com 
 */

#include "sort.h"
#include <stdio.h>

int sort_bubble(int *data, int cnt)
{
    int ret = 0;

    if(NULL != data){
        for(int i=0; i<cnt; i++){
        }
    }else
        ret = -1;

    return ret;
}

int sort_direct_select(int *data, int cnt)
{
    int ret = 0;

    if(NULL != data){
        for(int i=0; i<cnt; i++){
            for(int j=i; j<cnt; j++){
                if(data[i] > data[j]){
                    int tmp = data[i];
                    data[i] = data[j];
                    data[j] = tmp;
                }
            }
        }
    }else
        ret = -1;

    return ret;
}


