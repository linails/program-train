/*
 * Progarm Name: insertion_sort.c
 * Created Time: 2016-04-27 23:00:51
 * Last modified: 2016-04-29 23:10:50
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "insertion_sort.h"
#include <stdio.h>
#include "timing.h"

/*test insertion-soft*/
void insertion_sort_test(void)
{
    int it[] = {23,33,54,23,11,89,2,34,43,31,65};

    ctiming();

    printf("it[] : ");
    for(int i=0; i<sizeof(it)/sizeof(int); i++) printf(" - %d" ,it[i]);
    printf("\n");

    insertion_sort(it,sizeof(it)/sizeof(int));
    printf("it[] : ");
    for(int i=0; i<sizeof(it)/sizeof(int); i++) printf(" - %d" ,it[i]);
    printf("\n");

    ctiming();
}

/*insertion-sort*/
void insertion_sort(int *p,unsigned int length)
{
    for(unsigned int j=1; j<length; j++){
        int key = p[j];

        int i = j - 1;
        while( i >= 0 && p[i] > key){
            p[i+1] = p[i];
            i--;
        }
        p[i+1] = key;
    }
}


