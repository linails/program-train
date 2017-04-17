
package mymath

import "fmt"

func Plus(a, b int) int {
    return a + b
}

type Rect struct{
    x       float64
    y       float64
    width   float64
    height  float64
}

//
// Note :
// 成员首字母也需要大写，才可以在外部其他包进行调用赋值等使用
//
type Rect1 struct{
    X       float64
    Y       float64
    Width   float64
    Height  float64
}

func (r *Rect) Area() float64{
    return r.width * r.height
}

func (r *Rect1) Area() float64{
    return r.Width * r.Height
}

//
// Note :
// 函数名首字母要大写，才可以被外部其他包调用使用
//
func CalcRectangle(){
    fmt.Println("[Function] : CalcRectangle() !")
    {
        r := &Rect{0, 0, 10, 20}
        fmt.Printf("r.area() = %f \n", r.Area())
    }
    fmt.Println("-----------------------------------------")
    {
        // Note :
        // 由于 go 语言中任何对象实例都满足空接口，interface{}
        // 所以 interface{} 看起来像是可以指向任何对象的 any 类型
        //
        var v1 interface{} = 1
        var v2 interface{} = "abc"
        var v3 interface{} = &v2
        var v4 interface{} = struct{ X int }{1}
        var v5 interface{} = &struct{ X int }{1}

        fmt.Printf("v1 = %d\n", v1)
        fmt.Printf("v2 = %s\n", v2)
        fmt.Printf("v3 = %s\n", v3)
        fmt.Println("v3 =", v3)
        fmt.Printf("v4 = %d\n", v4)
        fmt.Println("v4 =", v4)
        fmt.Printf("v5 = %d\n", v5)
        fmt.Println("v5 =", v5)
    }
}

