/*
 * Progarm Name: format.c
 * Created Time: 2016-08-27 09:00:04
 * Last modified: 2016-08-27 09:01:34
 * @author: minphone.linails linails@foxmail.com 
 */

#include "format.h"
#include <stdio.h>

void format(void)
{
    static unsigned int line = 0;
    
    printf("Line : %.4d ", line++);
}


