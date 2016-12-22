# readme.txt
# Created Time: 2016-12-19 22:19:25
# Last modified: 2016-12-21 13:07:42
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
  *> lsmod      : 查看      =  cat /proc/modules
  *> modprobe   : 加载 modprobe hello


obj-$(CONFIG_XXX_DRV)  += xxxx.o
    : 当 XXX_DRV 的配置选项被选择为 Y / M ，即 obj-$(CONFIG_XXX_DRV) 等同于 obj-y / obj-m


[Kconfig]
  (1)config
      1> 每个配置选项都必须指定类型，类型包括：bool , tristate , string , hex , int
         tristate , string 是两个基本类型，其他类型都是基于这两个基本类型
         tristate(三态：内建、模块、移除)
      2> bool 类型的只能选中或者不选中，显示为[]; tristate 类型的菜单项多了编译成内核模块的选项，显示为<>
         假如选择编译成内核模块，则会在 .config 中生成一个 CONFIG_XXX_MODULE=m 的配置，假如选择内建，就是
         直接编译进内核镜像，就会在 .config 中生成一个 CONFIG_XXX_MODULE=y 的配置，hex 十六进制显示为 ( )
  (2)目录层次迭代
      1> 在 Kconfig 中有类似语句：source "drivers/usb/Kconfig"
         用来包含（或嵌套）新的 Kconfig 文件

[linux下的专门文件系统]
  1> devfs
     devfs 是在 2.4 内核出现，用来解决Linux中设备管理混乱的问题
  2> sysfs
     sysfs 是 Linux 2.6 所提供的一种虚拟文件系统，也是用来对系统的设备进行管理的，
     它把实际连接到系统上的设备和总线组织成一个分级的文件，用户空间的程序同样可以
     利用这些信息以实现和内核的交互


