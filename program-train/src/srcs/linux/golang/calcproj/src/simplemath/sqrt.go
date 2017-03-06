//
// 参考《go语言编程》
//
package simplemath

import "math"

func Sqrt(i int) int {
    v := math.Sqrt(float64(i))
    return int(v)
}
