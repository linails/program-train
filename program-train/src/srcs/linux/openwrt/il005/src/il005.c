/*
 * Progarm Name: il005.c
 * Created Time: 2016-12-20 13:37:12
 * Last modified: 2016-12-20 16:30:51
 * @author: minphone.linails linails@foxmail.com 
 */

#include <linux/init.h>
#include <linux/module.h>

static 
int il005_init(void)
{
    printk("init il005 !\n");
    return 0;
}

static 
void il005_exit(void)
{
    printk("exit il005 !\n");
}

module_init(il005_init);
module_exit(il005_exit);

