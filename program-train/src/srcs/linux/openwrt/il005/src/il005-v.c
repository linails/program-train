/*
 * Progarm Name: il005.c
 * Created Time: 2016-12-20 13:37:12
 * Last modified: 2016-12-29 17:27:30
 * @author: minphone.linails linails@foxmail.com 
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mman.h>
#include <linux/random.h>
#include <linux/raw.h>
#include <linux/tty.h>
#include <linux/capability.h>
#include <linux/ptrace.h>
#include <linux/device.h>
#include <linux/highmem.h>
#include <linux/crash_dump.h>
#include <linux/backing-dev.h>
#include <linux/bootmem.h>
#include <linux/splice.h>
#include <linux/pfn.h>
#include <linux/export.h>
#include <linux/aio.h>
#include <linux/time.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include "lib-gpio.h"
#include "i2c_sw.h"
#include "il005define.h"
#include "il005hal_i2c.h"
#include "il005communication.h"
#include "il005test.h"

static struct class *il005_class;

static char buf0[PLAIN_ENCRYPT_DATA_LENGTH] = "";
static char buf1[PLAIN_ENCRYPT_DATA_LENGTH] = "";

//-------------------------------------------------------------------

static
int clear_buffer(void)
{
    memset(buf0, 0x00, PLAIN_ENCRYPT_DATA_LENGTH);
    memset(buf1, 0x00, PLAIN_ENCRYPT_DATA_LENGTH);
    return 0;
}


static 
int il005_open(struct inode *inode, struct file *file)
{
    set_gpio_dir(il005bus.sda,GPIO_OUTPUT);
    set_gpio_dir(il005bus.scl,GPIO_OUTPUT);

    write_gpio(il005bus.sda,1);
    write_gpio(il005bus.scl,1);

    return 0;
}

/* 
 * il005 addr : 0xc8
 *
 * write : bit 0th = 0
 * read  : bit 0th = 1
 * */
static 
ssize_t il005_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
    /*
     * void kfree(const void *x);
     *
     * unsigned long copy_from_user(void *to, const void __user *from, unsigned long count);
     * unsigned long copy_to_user(void __user *to, const void *from, unsigned long count);
     * */

    size_t ret = 0;
    size_t len = 0;

    char *pt = NULL;
    Data_t data = {buf0, buf1};

    if(0 != copy_from_user(data.plain,
                           (const void __user *)(((Data_t *)buf)->plain),
                           size)){
        clear_buffer();
        return -1;
    }

    /* 
     * get len and check 
     * */
    {
        pt = data.plain;

        while(*pt++ != '\0') len++;

        if(len != size){
            clear_buffer();
            return -1;
        }
    }


    /* 
     * encrypt data throuth il005
     * */
    if(0 != encrypt_by_il005(&data, size)){
        clear_buffer();
        return -1;
    }else{
        ret = size + 8;
    }


    if(0 != copy_to_user((void __user *)(((Data_t *)buf)->encrypt),
                         data.encrypt,
                         ret)){
        clear_buffer();
        return -1;
    }


    clear_buffer();

    /* 
     * ret = strlen(data.encrypt)
     * */
    return ret;
}

static 
ssize_t il005_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
    size_t ret = 0;

    Data_t data = {buf0, buf1};


    if(0 != copy_from_user(data.encrypt,
                           (const void __user *)(((Data_t *)buf)->encrypt),
                           size)){
        clear_buffer();
        return -1;
    }


    /* 
     * decrypt data throuth il005
     * */
    if(0 != decrypt_by_il005(&data, size)){
        clear_buffer();
        return -1;
    }else{
        ret = size - 8;
    }


    if(0 != copy_to_user((void __user *)(((Data_t *)buf)->plain),
                         data.plain,
                         ret)){
        clear_buffer();
        return -1;
    }


    clear_buffer();


    /* 
     * ret = strlen(data.encrypt)
     * */
    return ret;
}

static 
long il005_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    return 0;
}

static struct file_operations il005_fops = {
    .owner   			= THIS_MODULE,
    .open    			= il005_open,
    .read    			= il005_read,
    .write    			= il005_write,
    .unlocked_ioctl	= il005_unlocked_ioctl,
};

int major;
static int __init il005_init(void)
{
    major = register_chrdev(0, "il005-ctrl", &il005_fops);

    il005_class = class_create(THIS_MODULE, "il005-ctrl");
    device_create(il005_class, NULL, MKDEV(major, 0), NULL, "il005-ctrl");

    init_gpio(1<<0); // 1<<0 is set the gpio1 gpio2 as the gpio.

    set_gpio_dir(il005bus.sda,GPIO_OUTPUT);
    set_gpio_dir(il005bus.scl,GPIO_OUTPUT);

    return 0;
}

static void __exit il005_exit(void)
{
    unregister_chrdev(major, "il005-ctrl");
    device_destroy(il005_class, MKDEV(major, 0));
    class_destroy(il005_class);
    uninit_gpio();
}

module_init(il005_init);
module_exit(il005_exit);

MODULE_LICENSE("GPL");

