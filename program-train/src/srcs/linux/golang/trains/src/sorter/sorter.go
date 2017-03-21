 
package sorter

import (
    "fmt"
    salgo "sorter/algo/bubblesort"
    "sort"
)

func Sorter(){
    fmt.Println("[Function] : Sorter() !")
    {
        dates := []int {2, 3, 5, 2, 1}
        salgo.BubbleSort(dates)

        fmt.Println("dates : ", dates)
    }
    fmt.Println("-----------------------------------------")
    {
        sort_std()
    }
    fmt.Println("-----------------------------------------")
}

//
// Note :
// sort 包提供了排序切片和用户自定义数据集的函数
//
func sort_std(){
    fmt.Println("[Function] : sort_std() !")
    {
        people := []Person_t {
            {"name1", 28},
            {"name2", 40},
            {"name3", 30},
            {"name4", 18},
            {"name5", 26},
        }

        fmt.Println("people : ", people)

        sort.Sort(Age_t(people))
        fmt.Println("people : ", people)
    }
    fmt.Println("-----------------------------------------")
}

//
// reference : studygolang.com/static/pkgdoc/pkg/sort.htm
//
type Person_t struct{
    name    string
    age     int
}

func (p Person_t)String() string{
    return fmt.Sprintf("%s : %d ", p.name, p.age)
}

type Age_t []Person_t
func (a Age_t) Len() int { return len(a) }
func (a Age_t) Swap(i, j int) { a[i], a[j] = a[j], a[i] }
func (a Age_t) Less(i, j int) bool { return a[i].age < a[j].age }


