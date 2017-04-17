/*
 * Progarm Name: char-driver-template.c
 * Created Time: 2016-12-21 14:07:51
 * Last modified: 2016-12-21 14:37:08
 * @author: minphone.linails linails@foxmail.com 
 */

/* 
 * 1> 在字符设备驱动模块加载函数中应该实现设备号的申请和 cdev 的注册，
 *    而在卸载函数中应实现设备号的释放和 cdev 的注销
 * */



/* 
 *  字符设备驱动模块加载与卸载函数模版
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */

/* 设备结构体 */
struct xxx_dev_t{
    struct cdev cdev;
    ...
} xxx_dev;

/* 设备驱动模块加载函数 */
static int __init xxx_init(void)
{
    ...

    cdev_init(&xxx_dev.cdev, &xxx_fops);    // init cdev
    
    xxx_dev.cdev.owner = THIS_MODULE;

    /* 获取字符设备号 */
    if(xxx_major){
        register_chrdev_region(xxx_dev_no, 1, DEV_NAME);
    }else{
        alloc_chrdev_region(&xxx_dev_no, 0, 1, DEV_NAME);
    }

    ret = cdev_add(&xxx_dev.cdev, xxx_dev_no, 1);   // register device

    ...
}

/* 设备驱动模块卸载函数 */
static void __exit xxx_exit(void)
{
    unregister_chrdev_region(xxx_dev_no, 1);    // 释放占用的设备号
    cdev_del(&xxx_dev.cdev);                    // 注销设备
    ...
}


/* 
 *  字符设备驱动 读、写、I/O 控制函数模版
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */

ssize_t xxx_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    ...

    copy_to_user(buf, ..., ...);

    ...
}

ssize_t xxx_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    ...

    copy_from_user(..., buf, ...);

    ...
}

int xxx_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
    ...

    switch(cmd){
        case xxx_CMD1:
            ...
            break;
        case xxx_CMD2:
            ...
            break;
        case xxx_CMD3:
            ...
        default :
            return -ENOTTY;     // 不能支持的命令
    }
    return 0;
}

/* 
 *  字符设备驱动文件操作结构体模版
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */

struct file_operations xxx_fops = {
    .owner  = THIS_MODULE,
    .read   = xxx_read,
    .write  = xxx_write,
    .ioctl  = xxx_ioctl,
    ...
};


