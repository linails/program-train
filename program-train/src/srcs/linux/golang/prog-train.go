
package main

import "fmt"

func main() {
    {
        str := "hello world"

        fmt.Println("str = ", str)
        fmt.Printf("str = %s\n", str)	// 同 C/C++ 
    }
    // 可以有局部作用域
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
    {
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
    }
}

func modify(array [5] int) {
    array[0] = 10
    fmt.Println("In modify(), array : ", array)
}

