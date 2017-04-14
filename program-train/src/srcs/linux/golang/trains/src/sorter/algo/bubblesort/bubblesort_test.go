
package bubblesort

import "testing"

func TestBubbleSort1(t *testing.T){
    dates := []int {5, 4, 3, 2, 1}

    BubbleSort(dates)

    if 1 != dates[0] ||
       2 != dates[1] ||
       3 != dates[2] ||
       4 != dates[3] ||
       5 != dates[4] {
           t.Error("BubbleSort() failed . got ", dates, "Expected 1 2 3 4 5")
       }
}
