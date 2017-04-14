/*
 * Progarm Name: kernel-module-hw.c
 * Created Time: 2016-12-19 23:26:55
 * Last modified: 2016-12-21 10:15:15
 * @author: minphone.linails linails@foxmail.com 
 */

#include <linux/init.h>
#include <linux/module.h>

static
int hello_init(void)
{
    printk("init hello!\n");
    return 0;
}

static
void hello_exit(void)
{
    printk("exit hello ...\n");
}

/* 
 * 安装模块时，被系统自动调用的函数，需要通过 module_init 宏来指定
 * */
module_init(hello_init);

/* 
 * 卸载模块时，被系统自动调用的函数，需要通过 module_exit 宏来指定
 * */
module_exit(hello_exit);

/* 
 * 字符设备驱动：
 *
 *  *> file_operations 结构体中成员函数是字符设备驱动与内核的接口，是用户空间对Linux进行系统
 *     调用最终的落实者
 *
 * */

