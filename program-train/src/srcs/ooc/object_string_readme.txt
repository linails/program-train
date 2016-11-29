object_string.h还可以另外一种定义方式
不在object_string.h 的ObjectString_t;中暴露数据
直接在object_string.c内部进行内存分配（数据块分配可以独立出一个单独的数据块分配功能函数）
然后主要点就集中在如果对一个objectstring 对象从数据块中区分出自己的数据
void *cthis是由外部传递进来的对象指针，可以作为区分本对象和其他对象
因此，内部数据块的定义可以如下所示：

/*对象内部使用的数据块定义-可以实现私有数据*/
typedef struct ObjectData{
	ObjectString_t *cthis;
	char data;
}ObjectData_t;

公有数据可以直接实现在头文件的对象定义中，来实现数据允许外部访问
