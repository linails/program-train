# readme.txt
# Created Time: 2016-12-19 22:19:25
# Last modified: 2016-12-19 23:51:39
#

make clean      : remove most generated files but keep the config
make mrproper   : remove all generated files + config files
make distclean  : mrproper + remove editor backup and patch files

make config     : 基于文本模式的交互式配置
make menuconfig : 基于文本模式的菜单型配置(常用)
make oldconfig  : 类似 config , 只是有些配置项具有了默认值

[*] --> *.o  --> image  : 有编译，有链接
[M] --> *.o             : 有编译
[ ] --> null            : 无编译


# 在X86上以下两个命令有差别
make zImage     : zimage 只能用于小于512k的内核
make bzImage    :

make zImage V=1 : 编译的时候显示详细编译信息
make bzImage V=1:

** 编译好的内核位于 arch/<cpu>/boot/目录下

make modules         : 编译模块
make modules_install : 安装内核模块


mkinitrd initrd-$version $version   : 制作 init ramdisk
    eg. mkinitrd initrd-2.6.38 2.6.38


[install kernel]
  1> cp arch/x86/boot/bzImage /boot/vmlinuz-$version    : $version 为编译内核版本号
  2> cp $initrd /boot/
  3> 修改/etc/grub.conf 或 /etc/lilo.conf


[install kernel modules]
  *> insmod     : 加载 insmod hello.ko
  *> rmmod      : 卸载 rmmod hello
  *> lsmod      : 查看
  *> modprobe   : 加载 modprobe hello

