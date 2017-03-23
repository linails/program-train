/*
 * Progarm Name: container.hpp
 * Created Time: 2016-12-20 17:17:22
 * Last modified: 2017-03-23 14:59:03
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_

class Container{
public:
    Container();
    ~Container();
    int  container_main(int argc, char **argv);
private:
    int  vector_t(void);
    int  list_t(void);
    int  map_t(void);
    int  stack_t(void);
private:
    int  container_test(void);
    void string_test(void);
    void vector_test(void);
    void map_test(void);
    void iterator_test(void);
    void bitset_test(void);
    void list_test(void);
    void queue_test(void);
    void deque_test(void);
    void adaptor_stack_test(void);
    void adaptor_queue_test(void);
    void adaptor_priority_queue_test(void);
    void tuple_test(void);
    void complex_test(void);
    void unordered_container(void);
    void sstream_test(void);
};

/* 
 * Note :
 *
 *  1. 缺省情况下应用使用vector . vector 的内部结构最简单，并允许随机存取，所以数据的存取十分方便灵活
 *     数据的处理也够快
 *
 *  2. 如果经常要在序列头部和尾部安插和移除元素，应该采用deque。如果希望元素被移除时，容器能够自动缩进
 *     内存，那么也应该采用deque。此外，由于vector通常采用一个内存区块存放元素，而deque采用多个区块，
 *     所以后者可以内含更多元素
 *
 *  3. 如果需要经常在容器的中段执行元素的安插、移除和移动，可考虑使用list。List提供特殊的成员函数，可
 *     以在常数时间内将元素从A容器转移到B容器。但由于list不支持随机存取，所以如果只知道list的头部却要
 *     造访list的中段元素，性能会大打折扣。
 *     和所有“以节点为基础”的容器相似，只要元素还是容器的一部分，list就不会令指向那些元素的迭代器失效。
 *     vector则不然，一旦超过其容量，它的所有iterators、pointers、references都会失效：执行安插或移除
 *     操作时，也会令一部分iterators、pointers、references失效。至于deque，当它的大小改变时，所有的
 *     iterators、pointers、references都会失效。
 *
 * */

#endif //_CONTAINER_HPP_

