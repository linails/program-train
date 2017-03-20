 
package sorter

import (
    "fmt"
    salgo "sorter/algo/bubblesort"
)

func Sorter(){
    fmt.Println("[Function] : Sorter() !")
    {
        dates := []int {2, 3, 5, 2, 1}
        salgo.BubbleSort(dates)

        fmt.Println("dates : ", dates)
    }
    fmt.Println("-----------------------------------------")
}
