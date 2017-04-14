
# Note :
# test-go.sh sorter/algo/bubblesort

{
    {
        var v1 int
        var v2 string
        var v3 [10] int
        var v4 []int
        var v5 struct {
            f int
        }

        var v6 * int
        var v7 map[string] int
        var v8 func(a int) int
    }

    {
        // var 关键字还可以将若干个变量放置在一起进行声明
        var (
            v1 int
            v2 string
        )
    }

    {
        // 以下都是正确用法，编译器可以自动推导出变量类型
        var v1 int = 10
        var v2 = 10
        v3 := 10	// := 用于明确表示同时进行变量声明和初始化的工作

        i := 10
        j := 12

        i, j = j, i	// 多重赋值，这里实现了 i 和 j 的交换

        func GetName() (firstName, lastName, nickName string) {
            return "May", "Chan", "Chibi Maruko"
        }

        // 若只想获取nickName，
        _, _, nickName := GetName()
    }

    {
        const Pi float64 = 3.14159265358979323846
        const zero = 0.0	// 无类型浮点常量
        const (
                size int64 = 1024
                eof = -1		// 无类型整形常量
              )
        const u, v float32 = 0, 3
        const a, b, c = 3, 4, "foo"

        // Go 预定义了3个常量：true , false , iota
        // iota 比较特殊，可以被认为是一个可被编译器修改的常量
        // 在每一个const 关键字出现时被重置为0，然后在下一个 const 出现之前，
        // 每出现一次 iota ，其所代表的数字会自动+1

        const (			// iota 被重置为0
            c0 = iota	// c0 == 0
            c1 = iota	// c1 == 1 
            c2 = iota	// c2 == 2
        )

        const (
            a = 1 << iota	// a == 1 (iota 在每个 cosnt 开头被重设为0)
            b = 1 << iota	// b == 2
            c = 1 << iota	// c == 4
        )

        const (
            u 			= iota * 42	// u = 0
            v flaot64 	= iota * 42 // v = 42.0
            w			= iota * 42 // w = 84
        )
    }

    {
        const x = iota		// x == 0
        const y = iota		// y == 0

        // 如果两个 const 赋值语句的表达式是一样的，那么可以省略后一个赋值表达式
        // 例如前面的可以省略写如下 : 
        const (             // iota 被重置为0
            c0 = iota       // c0 == 0
            c1              // c1 == 1
            c2              // c2 == 2
        )

        // Go 语言中，以大写字母开头的常量在包外可见
        const (
            Sunday = iota
            Monday
            Tuesday
            Wednesday
            Thursday
            Friday
            Saturday
            numberOfDays	// 这个常量没有导出
        )

        // Go 内置的基础类型
        // bool
        // int8 / byte / int16 / int / uint / uintptr
        // float32 / float64
        // complex64 / complex128	复数类型
        // string	字符串
        // rune	字符类型
        // error 错误类型

        // Go 支持的复合类型
        // pointer 指针
        // array
        // slice 切片
        // map
        // chan 通道
        // struct
        // interface 接口

        // Go 还有几种类型
        // int
        // uint
        // uintptr
    }

    {
        var b bool 
        b = (1 != 0)
        fmt.Println("Result: ", b)
    }
}

