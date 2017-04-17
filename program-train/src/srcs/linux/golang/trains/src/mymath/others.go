
package mymath

import "fmt"

// Note :
// interface 类型定义了一组方法，如果某个对象实现了某个接口的所有方法
//

type Human struct{
    name string
    age int
    phone string
}

type Student struct{
    Human
    school string
    loan float32
}

type Employee struct{
    Human
    company string
    money float32
}

func (h *Human) SayHi(){
    fmt.Printf("Hi, I'm %s you can call me on %s \n", h.name, h.phone)
}

func (h *Human) Sing(lyrics string){
    fmt.Println("La la, la la la, la la la la la ...", lyrics)
}

func (h *Human) Guzzle(beerStein string){
    fmt.Println("Guzzle Guzzle Guzzle ...", beerStein)
}

func (e *Employee)SayHi(){
    fmt.Printf("Hi, I'm %s, my work is %s , phone = %s\n",
               e.name, e.company, e.phone)
}

func (s *Student)BorrowMoney(amount float32){
    s.loan += amount
}

func (e *Employee) SpendSalary(amount float32){
    e.money -= amount
}

// Note :
// interface 可以被任意的对象实现
// 一个对象也可以实现任意多个 interface
// 

type Men interface{
    SayHi()
    Sing(lyrics string)
    Guzzle(beerStein string)
}

type YoungChap interface{
    SayHi()
    Sing(song string)
    BorrowMoney(amount float32)
}

type ElderlyGent interface{
    SayHi()
    Sing(song string)
    SpendSalary(amount string)
}

func Interface_fun(){
    fmt.Println("[Function] : Interface_fun() !")
    {
        mike := Student{Human{"Mike", 25, "978787978"}, "MIT", 0.00}
        //paul := Student{Human{"Paul", 24, "099898989"}, "Harvard", 100}
        //sam := Employee{Human{"Sam", 36, "3338988788"}, "Golang Inc.", 1000}
        Tom := Employee{Human{"Tom", 35, "86768898989"}, "Things Ltd.", 5000}

        var t Men

        // t 可以存储 Student
        t = &mike
        fmt.Println("This is Mike, a Student")
        t.SayHi()
        t.Sing("noverber rain")


        fmt.Println("")

        // t 也可以存储 Employee
        t = &Tom
        fmt.Println("This is Tom, a employee")
        t.SayHi()
        t.Sing("Born to be wild")
    }
    fmt.Println("-----------------------------------------")
    {
        // Note :
        // 空 interface(interface{}) 不包含任何的 method
        // 所以所有的类型都实现了空 interface
        // 空 interface 对于描述起不到任何的作用，但是空 interface 在我们需要存储任意类型的数值时相当有用
        // 因为可以存储任意类型的值，类似 void *
        // 

        var a interface{}   // 定义 a 为空接口, 可以存储任意类型
        var i int = 5

        s := "hello world"

        a = i
        fmt.Println("a =", a)

        a = s
        fmt.Println("a =", a)
    }
    fmt.Println("-----------------------------------------")
    {
        BTreeExample()
    }
    fmt.Println("-----------------------------------------")
    {
        var a, b int = 1 , 2
        var s1, s2 string = "string 1", "string 2"

        typeComparator(a, b)
        typeComparator(s1, s2)
    }
    fmt.Println("-----------------------------------------")
}

func typeComparator(a, b interface{}){
    fmt.Println("[Function] : typeComparator() !")
    {
        switch a.(type) {
            case int:
                s1 := a.(int)
                s2 := b.(int)

                fmt.Println("a.(int) s1 = ", s1)
                fmt.Println("b.(int) s2 = ", s2)
            case string:
                s1 := a.(string)
                s2 := b.(string)

                fmt.Println("a.(string) s1 = ", s1)
                fmt.Println("b.(string) s2 = ", s2)
        }
    }
    fmt.Println("-----------------------------------------")
}

