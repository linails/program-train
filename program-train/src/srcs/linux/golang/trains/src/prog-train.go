
package main

// Note :
// import 支持的加载方式
// 01. 相对路径
//     import "./model"
//
// 02. 绝对路径
//     import "/home/minphone/model"
//
// ----------------------------------------------
// import 常用的几种方式
// 01. 点操作，导入这个包后，调用就可以省略前缀包名
//     import (
//        . "fmt"
//     )
//     
//     Printf("xxxxx")     
//
// 02. 别名操作
//     import (
//        f "fmt"
//     )
//
//     f.Printf("xxxxx")     
//
// 03. _操作
//     import (
//        _ "xxx/xxx/xxx/xxmodule"
//     )
//     _操作只是进入该包，即只调用了包里面的 init() 函数，不可以使用包里面的函数
//

import "fmt"
import "os"
import "runtime"
import "github.com/op/go-logging"
//import "errors"
import . "mymath"

// Note :
// go 语言里面有两个保留函数 init 函数(所有的 package 都可以应用) 和 main 函数
// go 会自动调用 init() 和 main()

func main() {
    // 可以有局部作用域
    array_fun()

    str_fun()

    array_slice()

    map_fun()

    flow_ctrl()

    function()

    error_func()

    pointer_func()

    defer_func()

    struct_func()

    method_fun()

    goroutine_fun()

    log_fun()

    mine_func()
}

func str_fun() {
    {
        str := "hello world"

        fmt.Println("str = ", str)
        fmt.Printf("str = %s\n", str)	// 同 C/C++ 
    }
    {
        // 在go语言中支持两个字符类型
        // 一个是byte（实际上是uint8的别名）代表utf-8字符串的单个字节的值
        // 另一个是rune,代表单个unicode字符
        str := "nice"
        fmt.Println("str = ", str)

        str1:= "go"
        fmt.Println("str + str1 = ", str + str1)
        fmt.Println("len(str) : ", len(str))

        n := len(str)
        for i := 0; i < n; i++ {
            ch := str[i]    // 依据下标获取字符串中的字符，类型为byte
            fmt.Printf("%c - ", ch)
            fmt.Println(i, ch)
        }
    }
}

func modify(array [5] int) {
    fmt.Println("[Function] : modify() !")
    array[0] = 10
    fmt.Println("array : ", array)
}

func array_fun() {
    // [32] byte
    // [2*N] struct {x, y int32}
    // [1000] * float64
    // [3][5] int
    // [2][2][2] float64
    // 遍历容器可以使用关键字：range 来进行便利，range 返回两个值，一个是元素下标，一个是元素的值
    // go语言中的数组是一个值类型，所以作为参数的时候会进行复制动作

    array := [5] int{1, 2, 3, 4, 5 } // 定义的时候初始化
    fmt.Println("array[32]'s length : ", len(array))

    modify(array)
    fmt.Println("In main(), array : ", array)
    fmt.Println("-----------------------------------------")
}

func array_slice() {
    fmt.Println("[Function] : array_slice() !")


    // 和 python 中的 list 比较接近
    // 操作数组元素的所有方法，都适用于数组切片
    // 数组切片可以动态增减元素

    // 创建数组切片的方法主要有两种：基于数组和直接创建
    // 01. 基于数组 
    //     可以使用整个数组或者数组的一部分进行创建
    // 02. 直接创建
    //     go提供了内置的函数 make() 可以用于灵活创建数组切片

    // 01. 基于数组 
    {
        var myarray [10] int = [10] int{1, 2, 3, 4, 5, 6, 7, 8}
        var myslice []int = myarray[:5]

        fmt.Println("elements of myarray : ")
        for _, v := range myarray {
            fmt.Print(v, " ")
        }
        fmt.Println()

        fmt.Println("elements of myslice : ")
        for _, v := range myslice {
            fmt.Print(v, " ")
        }

        fmt.Println()
    }

    fmt.Println("-----------------------------------------")

    // 02. 直接创建
    {
        // 元素个数为5的数组切片，元素初始值为0
        myslice01 := make([]int, 5)
        fmt.Printf("myslice01 : ")
        for _, v := range myslice01 {
            fmt.Print(v, " ")
        }
        fmt.Println()

        // 元素格式为5的数组切片，元素初始值为0，并预留10个元素的存储空间
        myslice02 := make([]int, 5, 10)
        fmt.Printf("myslice02 : ")
        for _, v := range myslice02 {
            fmt.Print(v, " ")
        }
        fmt.Println()

        // 直接初始化5个元素的数组切片
        myslice03 := []int{1, 2, 3, 4, 5}
        fmt.Printf("myslice03 : ")
        for _, v := range myslice03 {
            fmt.Print(v, " ")
        }
        fmt.Println()
    }

    fmt.Println("-----------------------------------------")
    {
        // cap()函数返回数组切片的空间大小
        // len()返回数组切片中当前存储的元素个数

        myslice := make([]int, 5, 10)
        fmt.Println("cap(myslice) : ", cap(myslice))
        fmt.Println("len(myslice) : ", len(myslice))

        myslice = append(myslice, 1)
        fmt.Println("cap(myslice) : ", cap(myslice))
        fmt.Println("len(myslice) : ", len(myslice))

        myslice = append(myslice, 1, 2, 3, 4, 5, 6, 7)
        fmt.Println("cap(myslice) : ", cap(myslice))
        fmt.Println("len(myslice) : ", len(myslice))

        // 这个需要特别注意：如果 append 的是数组切片，则需要添加 "..."
        myslice01 := []int {3, 4, 5, 6, 7}
        myslice = append(myslice, myslice01...)
        fmt.Printf("myslice : ")
        for _, v := range myslice {
            fmt.Print(v, " ")
        }
        fmt.Println()
    }
    fmt.Println("-----------------------------------------")
    {
        array := [7]int {9, 8, 7, 6, 5, 4, 3}
        myslice := make([]int, 1)

        // 数组不可以直接和数组切片进行连接，会有编译错误
        //myslice = append(myslice, array...)
        myslice = append(myslice, array[:]...)
        //array_slice := array[:]
        //myslice = append(myslice, array_slice...)
        fmt.Printf("myslice : ")
        for _, v := range myslice {
            fmt.Print(v, " ")
        }
        fmt.Println()
    }
    fmt.Println("-----------------------------------------")
    {
        array := [7]int {9, 8, 7, 6, 5, 4, 3}
        myslice := make([]int, 1)

        array_slice := array[:]
        myslice = append(myslice, array_slice...)
        fmt.Printf("myslice : ")
        for _, v := range myslice {
            fmt.Print(v, " ")
        }
        fmt.Println()
    }
    fmt.Println("-----------------------------------------")
    {
        // copy(dst, src)
        myslice01 := []int {1, 2, 3, 4, 5}
        myslice02 := []int {9, 10, 11}

        fmt.Printf("myslice01 : ")
        for _, v := range myslice01 {
            fmt.Print(v, " ")
        }
        fmt.Println()
        fmt.Printf("myslice02 : ")
        for _, v := range myslice02 {
            fmt.Print(v, " ")
        }
        fmt.Println()

        copy(myslice01, myslice02)
        fmt.Printf("myslice01 : ")
        for _, v := range myslice01 {
            fmt.Print(v, " ")
        }
        fmt.Println()

        copy(myslice02, myslice01)
        fmt.Printf("myslice02 : ")
        for _, v := range myslice02 {
            fmt.Print(v, " ")
        }
        fmt.Println()
    }
    fmt.Println("-----------------------------------------")
    {
        var a []int

        fmt.Println("len(a) =", len(a))

        a = append(a, 1)
        fmt.Println("len(a) =", len(a))
    }
    fmt.Println("-----------------------------------------")
}

func map_fun() {

    fmt.Println("[Function] : map_func() !")

    type PersonInfo struct {
        ID string
        Name string
        Address string
    }

    {
        // map 同C++，传说是比C++更方便快捷和简单

        // map 的声明
        // personDB 是声明的 map 变量名
        // map[string] PersonInfo : string 是键名 | PersonInfo 是值类型
        var personDB map[string] PersonInfo

        // 创建 map
        personDB = make(map[string] PersonInfo)

        personDB["1"] = PersonInfo{"1", "Tom", "Room 203"}
        personDB["2"] = PersonInfo{"2", "Jom", "Room 204"}

        person, ok := personDB["1"]
        if ok {
            fmt.Println("Found person ", person.Name, " id = 1")
        } else {
            fmt.Println("Did't find person id = 1")
        }
    }
    fmt.Println("-----------------------------------------")
    {
        // 每次都得带上声明
        var personDB map[string] PersonInfo

        // 创建 map 的时候可以直接进行初始化
        personDB = map[string] PersonInfo {
            "1" : PersonInfo{"1", "Tom", "Room 203"},
            "2" : PersonInfo{"2", "Jom", "Room 204"},
        }

        // 这种用法的模版
        // value, ok := xxmap["xxx"]
        // if ok {
        //      ToDo !
        //}
        person, ok := personDB["1"]
        if ok {
            fmt.Println("Found person ", person.Name, " id = 1")
        } else {
            fmt.Println("Did't find person id = 1")
        }

        delete(personDB, "2")

        person, ok = personDB["2"]
        if ok {
            fmt.Println("Found person ", person.Name, " id = 2")
        } else {
            fmt.Println("Did't find person id = 2")
        }

    }
    fmt.Println("-----------------------------------------")
}

func flow_ctrl() {

    fmt.Println("[Function] : flow_ctrl() !")
    {
        a := 10

        // 在 if 之后，条件语句之前，可以添加变量初始化语句，使用 ; 间隔
        // 在有返回值的函数中，不允许将 "最终的" return 语句包含在 if...else... 结构中
        if a < 5 {
            fmt.Println("a < 5")
        }else{
            fmt.Println("a > 5")
        }
    }
    fmt.Println("-----------------------------------------")
    {
        // go 的 switch 不需要用 break 来进行退出一个 case
        // 而且也只有明确添加 fallthrough 关键字，才会继续执行紧跟着的下一个 case
        i := 3
        switch i {
            case 0:
                fmt.Println("i = 0")
            case 1:
                fmt.Println("i = 1")
            case 2:
                fmt.Println("i = 2")
            case 3, 4, 5, 6:
                fmt.Println("i = 3, 4, 5, 6")
            default :
                fmt.Println("default ")
        }

        num := 12
        // switch 后面没有表达式也是可以的
        switch {
            case 0 <= num && num <= 5:
                fmt.Println("0 <= num && num <= 3")
            case 6 <= num && num <= 15:
                fmt.Println("6 <= num && num <= 15")
                fallthrough
            case 16 <= num && num <= 25:
                fmt.Println("16 <= num && num <= 25")
            case 26 <= num && num <= 35:
                fmt.Println("26 <= num && num <= 35")

            // 没有 default 也是可以的
            default :
                fmt.Println("default ")
        }
    }
    fmt.Println("-----------------------------------------")
    {
        // go 语言只支持 for 循环
        // 同样支持 continue 和 break 来控制循环，不过 break 可以中断哪一个循环，更高级

        sum := 0
        for i := 0; i < 10; i++ {
            sum += i
        }
        fmt.Println("sum = ", sum)

        // for 的无限循环写法
        sum = 0
        for {
            sum++
            if sum > 100 {
                break
            }
        }
        fmt.Println("sum = ", sum)

        a := []int {1, 2, 3, 4, 5}

        fmt.Println("a = ", a)
        for i, j := 0, len(a) - 1; i < j; i , j = i + 1, j - 1 {
            a[i], a[j] = a[j], a[i]
        }
        fmt.Println("a = ", a)
    }
    fmt.Println("-----------------------------------------")
    {
        arr := [2]int {0, 0}

        // break 跳出标签后，不会再进入 for 循环
        // break 的标签需要在 for 的前面
        JLoop :
        for i := 0; i < 10; i++ {
            for j := 0; j < 10; j++{
                if 3 == j && i == 4 {
                    arr[0] = i
                    arr[1] = j
                    break JLoop
                }
            }
        }

        fmt.Printf("i = %d , j = %d \n", arr[0], arr[1])
    }
    fmt.Println("-----------------------------------------")
    {
        // goto 同 C/C++
        sum := 0
        HERE :

        fmt.Println("sum = ", sum)
        sum++
        if sum < 10 {
            goto HERE
        }
    }
    fmt.Println("-----------------------------------------")
    {
        var a int = 10

        for a > 0 {
            fmt.Printf("a = %d\n", a)
            //a = a - 1
            a--
        }
    }
    fmt.Println("-----------------------------------------")
}

func function() {
    {
        a, b := 1, 2
        //c := mymath.Plus(a, b)

        c := function_child_01(a, b)

        fmt.Println("c = a + b : ", c)

        function_child_03(a, b, c)
    }
    fmt.Println("-----------------------------------------")
    {
        var v1 int = 1
        var v2 int64 = 234
        var v3 string = "hello"
        var v4 float32 = 1.234
        function_child_04(v1, v2, v3, v4)
    }
    fmt.Println("-----------------------------------------")
    {
        // 匿名函数类似 javascript 的匿名函数 | 类似 C/C++ lambda 表达式

        f := func(x, y int) int {
            return x * y
        }

        fmt.Println("f(10, 20) = ", f(10, 20))
    }
    fmt.Println("-----------------------------------------")
    {
        var j int = 5
        var n int = 0

        // 这个匿名函数确实像一个类的实例，在第二次调用的时候，i 是增加了之后的值
        a := func()(func(*int)) {
            var i int = 10
            return func(n *int) {
                fmt.Printf("i, j = %d, %d, %d\n", i, j, *n)
                i++
                *n++
            }
        }()

        a(&n)
        j *= 2
        a(&n)
    }
    fmt.Println("-----------------------------------------")
    {
        a := func(val int) int {
            val += 1    // 这一句如果直接写在 return 中会编译出错, ([Error] eg. return val += 1)
            return val
        }

        fmt.Printf("a(2) = %d\n", a(2))
    }
    fmt.Println("-----------------------------------------")
    {
        a := func() (func()){
            return func(){
                fmt.Printf("val = ...\n")
            }
        }()

        a()
        a()
    }
    fmt.Println("-----------------------------------------")
    {
        //a := func(val int) {
        //    fmt.Printf("val = %d\n", val)
        //}(3)

        //a(2);
    }
    fmt.Println("-----------------------------------------")
    {
        // type 可以函数类型，类似C++的functional
        // 还有点类似 typedef 

        type FuncType func(int, int) int

        plus := func(a, b int) int{
            return a + b
        }

        mul := func(a, b int) int{
            return a * b
        }

        minus := func(a, b int) int{
            return a - b
        }

        doMath := func(a int, b int, cb FuncType){
            fmt.Printf("a = %d , b = %d | a O b = %d \n", a, b, cb(a, b))
        }

        doMath(1, 2, plus)
        doMath(1, 2, mul)
        doMath(1, 2, minus)
    }
}

// 如果返回值就一个，可以类似 C++ 的 lambda 表达式的写法
// 返回值被命名后，它们的值在函数开始的时候被自动初始化为空
func function_child_01(a, b int) int {
    return a - b
}

// 如果参数列表中有若干个相邻的参数类型相同，则可以省略前面变量的类型声明
// 返回值如果多个参数类型也相同，也可以进行省略
func function_child_02(a, b int) (ret int, err error) {
    return a + b, nil
}

// 定义不定参数的函数 (参数类型都是一样的)
func function_child_03(args ... int){
    for i, arg := range args {
        fmt.Println("args ", i, " - ", arg)
    }
}

// 如果希望传入任意类型，则可以指定类型为 interface{}
// 用 interface{} 传递任意类型的数据是 go 语言的惯例用法
func function_child_04(args ... interface{}) {
    for i, arg := range args {
        switch arg.(type) {
            case int:
                fmt.Println("i = ", i, " , arg(int) = ", arg)
            case string:
                fmt.Println("i = ", i, " , arg(string) = ", arg)
            case int64:
                fmt.Println("i = ", i, " , arg(int64) = ", arg)
            default:
                fmt.Println("i = ", i, " , arg(default) = ", arg)
        }
    }
}

func error_func() {
    fmt.Println("[Function] : error_func() !")
    {
        // go 语言中引入了一个关于错误处理的标准模式，即 error 接口
        // func Foo(param int) (n int, err error){
        //    // ...
        //}
        //
        // n, err := Foo(0)
        // if err != nil {
        //      错误处理
        // } else {
        //      正常执行
        // }
        //
        //
    }
    fmt.Println("-----------------------------------------")
}

func incr(p *int){
    *p++
}

func pointer_func() {
    fmt.Println("[Function] : pointer_func() !")
    {
        // 任何类型的指针的零值都是 nil
        // 如果 p != nil 测试为真，那么 p 是指向某个有效变量
        var a int = 10
        var c int

        b := &a

        fmt.Printf("*b = %d\n", *b)
        fmt.Printf("addr b = %d\n", b)

        // 指针的比较也是类型一致的才可以进行比较
        // &a == &b 就是错误的
        fmt.Printf("&a == b : ")
        fmt.Println(&a == b)

        fmt.Printf("&a == &c : ")
        fmt.Println(&a == &c)

        // 在 go 语言中，返回函数中局部变量的地址也是安全的
        // 且每次返回的地址还是不一样的
    }
    fmt.Println("-----------------------------------------")
    {
        var a int = 10
        fmt.Println("a = ", a)

        incr(&a)
        fmt.Println("a = ", a)
    }
}

func defer_func_01(){

    var b int = 20

    a := func(){
        fmt.Printf("b = %d\n", b)
    }

    defer a()

    fmt.Println("Line = 600")

    fmt.Println("Line = 600+")

    // 这里返回的话，则打印的 b = 20
    return

    b++

    fmt.Println("Line = 600++")

    // 这里返回的话，则打印的 b = 21
}

func defer_func(){
    fmt.Println("[Function] : defer_func() !")
    {
        // defer 表示延迟执行，函数在结束前统一运行 defer 语句
        // 然后遵守先进后出的原则进行调用，即最后一个定义的 defer 语
        // 句最先执行
        //
        // eg-01.
        // defer srcFile.Close()
        // 
        // eg-02.
        // defer func(){
        //   ToDo
        // }()
        //
        // Note :
        // 一个函数中可以定义多个 defer 函数
    }
    fmt.Println("-----------------------------------------")
    {
        defer_func_01()
    }
}

func struct_func(){
    fmt.Println("[Function] : struct_func() !")
    {
        // 用 type 定义 struct 的时候，就类似于 typedef
        type person struct{
            name string
            age int
        }

        var p person

        p.name = "alex"
        p.age  = 25

        fmt.Printf("name = %s - age = %d \n", p.name, p.age)

        // 快捷定义方式
        a := person{"Lin", 24}
        fmt.Printf("name = %s - age = %d \n", a.name, a.age)

        b := person{age:26, name:"min"}
        fmt.Printf("name = %s - age = %d \n", b.name, b.age)
    }
    fmt.Println("-----------------------------------------")
    {
        // struct 的匿名字段
        // 当匿名字段是一个 struct 是时候，那么这个 struct 所拥有
        // 是全部字段都被隐士地引入了当前定义的这个 struct

        type Human struct{
            name string
            age int
        }

        // 所有的内置类型和自定义类型都可以作为匿名字段
        type Student struct{
            Human
            class string
            weight string
        }

        a := Student{Human{"axx", 20}, "class-01", "30kg"}

        fmt.Printf("a.name = %s - age = %d - class = %s\n", a.name, a.age, a.class)
    }
    fmt.Println("-----------------------------------------")
    {
    }
}

//
// Note :
// go 语言的面向对象非常简单，没有任何私有、公有关键字
// 通过大小写来实现（大写开头的为公有，小写开头的为私有）
// 
type Rectangle struct{
    width, height float64
}

func(r Rectangle) area() float64{
    return r.width * r.height
}

func method_fun(){
    fmt.Println("[Function] : method_fun() !")
    log_init()
    {
        // method 的语法
        // func (r ReceiverType) funcName(parameters) (results)
        //
        // Note :
        // 一个数据类型定义了很多的 method 后，就像类似C++的 class 定义了很多的成员函数

        r1 := Rectangle{12, 2}
        fmt.Printf("area of r1 is: %f\n", r1.area())
        log.Warning("area of r1 is: ", r1.area())
    }
    fmt.Println("-----------------------------------------")
    {
    }
}

//
// Note :
// goruntine 运行在相同的地址空间，因此访问共享内存必须做好同步
// go 语言提供一个很好的通信机制 channel , 类似 Unix 中的 shell 管道
//
func say(s string){
    for i:=0; i<5; i++{
        // runtime.Gosched() 表示让CPU把时间片让给别人
        // 下次某个时候继续恢复执行该 goruntine
        runtime.Gosched()
        fmt.Printf("s = %s \n", s)
    }
}

//
// 默认情况下，channel 接收和发送数据都是阻塞的
// 默认的情况下 channel 是无缓冲的
//
// Note :
// ch := make(chan type, value)
// value == 0 ! 默认的无缓冲模式（阻塞）
// value > 0  ! 缓冲（非阻塞，直到 value 个元素）
//
func sum(a []int, c chan int){
    sum := 0
    for _, v := range a{
        sum += v
    }

    c <- sum    // send sum to c
}

func fibonacci(n int, c chan int){
    x, y := 1, 1
    for i := 0; i < n; i++{
        c <- x
        x, y = y, x + y
    }
    close(c)
}

func goroutine_fun(){
    fmt.Println("[Function] : goroutine_fun() !")
    log_init()
    {
        go say("hello");    // 开启一个新的 goruntines 执行
        say("world");       // 当前 goruntines 执行
    }
    fmt.Println("-----------------------------------------")
    {
        a := []int {7, 2, 8, -9, 4, 0}

        c := make(chan int)

        go sum(a[ : len(a)/2], c)
        go sum(a[len(a)/2 : ], c)

        x, y := <-c, <-c // receive from c
        fmt.Printf("x = %d ; y = %d ; x+y = %d \n", x, y, x+y)
    }
    fmt.Println("-----------------------------------------")
    {
        f := func(c chan int){
            a := 1000
            for a > 0{
                a--
            }

            for a < 3{
                fmt.Printf("inner c = %d \n", <-c )
                a++
            }
        }
        c := make(chan int, 1)

        go f(c)
        go f(c)
        c <- 1
        c <- 2
        c <- 3
        c <- 4
        c <- 5
        fmt.Printf("outer c = %d \n", <-c )
        fmt.Printf("end ...\n")

        // 显示关闭 channel
        // 应该在生产者的地方关闭 channel ，否则容易出错
        close(c)
    }
    fmt.Println("-----------------------------------------")
    {
        c := make(chan int, 10)
        go fibonacci(10, c)

        // range c 可以不断读取 channel 里面的数据，直到 channel 被显式关闭
        for i := range c{
            //fmt.Printf("i = %d\n", i)
            log.Info("i = ", i)
        }
    }
    fmt.Println("-----------------------------------------")
    {
        // Note :
        // 当存在多个 channel 的时候，可以通过 select 进行监听 channel 上的数据流
        // select 默认是阻塞的
        // 只有当监听的 channel 中发送或接收可以进行时才会运行，当多个
        // channel 都准备好的时候， select 是随机选择一个执行的
        //
        //
        // select 里面还有 default 语法，select 其实就是类似 switch 的功能
        // default 就是当监听的 channel 都没有准备好的时候，默认执行，则不再
        // 进行阻塞等待 channel
        // 
    }
}

var log = logging.MustGetLogger("example")

var format = logging.MustStringFormatter(
    `%{color} %{time} %{shortfunc} > %{level:.4s} %{id:5d} %{color:reset} %{message}`,
    //`%{time} %{shortfunc} > %{level:.4s} %{id:5d} %{message}`,
)

type Password string

func (p Password)Redacted() interface{} {
    return logging.Redact(string(p))
}

func log_init(){
    backend2 := logging.NewLogBackend(os.Stdout, "", 0)
    backend2Formatter := logging.NewBackendFormatter(backend2, format)
    logging.SetBackend(backend2Formatter)
}

func log_fun(){
    fmt.Println("[Function] : log_fun() !")
    {
        /*
        logFile, err := os.OpenFile("log.txt", os.O_WRONLY, 0666)
        if err != nil{
            fmt.Println(err)
        }
        */

        //backend1 := logging.NewLogBackend(logFile, "", 0)
        //backend2 := logging.NewLogBackend(os.Stderr, "", 0)
        backend2 := logging.NewLogBackend(os.Stdout, "", 0)
        //backend2 := logging.NewLogBackend(logFile, "", 0)

        backend2Formatter := logging.NewBackendFormatter(backend2, format)
        //backend1Leveled := logging.AddModuleLevel(backend1)
        //backend1Leveled.SetLevel(logging.INFO, "")

        //logging.SetBackend(backend1Leveled, backend2Formatter)
        logging.SetBackend(backend2Formatter)

        log.Debug("debug %s", Password("secret"))
        log.Info("info")
        log.Notice("notice")

        /*
        a := 2000
        for a > 0{
            a--
            log.Notice("a = ", a)
        } 
        */
        //log.Warning("Warning")
        //log.Error("error ....")
        //log.Critical("critical ...")

        //log.Debug("debug %s", Password("secret"))
        //log.Info("info")
        //log.Notice("notice")
        //log.Warning("Warning")
        //log.Error("error ....")
        //log.Critical("critical ...")
    }
    fmt.Println("-----------------------------------------")
    {
        log.Notice("notice")
        log.Warning("Warning")
        log.Error("error ....")
    }
    fmt.Println("-----------------------------------------")
}

func mine_func(){
    fmt.Println("[Function] : log_fun() !")
    {
        fmt.Printf("mymath.Plus(2, 2) = %d\n", Plus(2, 2));
    }
    fmt.Println("-----------------------------------------")
    {
        r := &Rect1{0, 0, 10, 20}
        fmt.Printf("r.area() = %f \n", r.Area())
        CalcRectangle()
    }
    fmt.Println("-----------------------------------------")
    {
        Interface_fun()
    }
}

// Note :
// 其他文件中的函数调用也非常简单：只要事先导入了该函数所在的包
//
// 内建常量：true false iota nil

