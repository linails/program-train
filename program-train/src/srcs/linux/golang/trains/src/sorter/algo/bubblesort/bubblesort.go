
//
// reference <<go 语言编程>>
//

package bubblesort

func BubbleSort(dates []int){
    for i := 0; i < len(dates) - 1; i++{
        sorted := true

        for j := 0; j < len(dates) - i - 1; j++{
            if dates[j] > dates[j + 1]{
                dates[j], dates[j + 1] = dates[j + 1], dates[j]
                sorted = false
            }
        }

        if true == sorted{
            break
        }
    }
}
