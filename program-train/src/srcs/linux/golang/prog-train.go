
package main

import "fmt"
//import "errors"
//import "mymath"

func main() {
    // 可以有局部作用域
    array_fun()

    str_fun()

    array_slice()

    map_fun()

    flow_ctrl()

    function()

    error_func()
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
    // 便利容器可以使用关键字：range 来进行便利，range 返回两个值，一个是元素下标，一个是元素的值
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
                fmt.Printf("val = \n")
            }
        }()

        a()
    }
    fmt.Println("-----------------------------------------")
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

// Note :
// 其他文件中的函数调用也非常简单：只要事先导入了该函数所在的包

