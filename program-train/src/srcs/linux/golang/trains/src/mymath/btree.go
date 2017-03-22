
package mymath

import (
    "fmt"
    "github.com/emirpasic/gods/trees/btree"
)

func BTreeExample() {
    fmt.Println("[Function] : BTreeExample() !")
    {
        //
        // reference : github.com/emirpasic/gods/trees/btree
        //
        tree := btree.NewWithIntComparator(3) // empty (keys are of type int)

        fmt.Println(tree)

        tree.Put(1, "x") // 1->x
        tree.Put(2, "b") // 1->x, 2->b (in order)
        tree.Put(1, "a") // 1->a, 2->b (in order, replacement)
        tree.Put(3, "c") // 1->a, 2->b, 3->c (in order)
        tree.Put(4, "d") // 1->a, 2->b, 3->c, 4->d (in order)
        tree.Put(5, "e") // 1->a, 2->b, 3->c, 4->d, 5->e (in order)
        tree.Put(6, "f") // 1->a, 2->b, 3->c, 4->d, 5->e, 6->f (in order)
        tree.Put(7, "g") // 1->a, 2->b, 3->c, 4->d, 5->e, 6->f, 7->g (in order)

        fmt.Println(tree)

        v := tree.Values() // []interface {}{"a", "b", "c", "d", "e", "f", "g"} (in order)
        k := tree.Keys()   // []interface {}{1, 2, 3, 4, 5, 6, 7} (in order)

        fmt.Println("v = ", v)
        fmt.Println("k = ", k)

        tree.Remove(2) // 1->a, 3->c, 4->d, 5->e, 6->f (in order)
        fmt.Println(tree)
        fmt.Println("tree.Size() = ", tree.Size())

        tree.Clear()
        tree.Empty()
        fmt.Println("tree.Size() = ", tree.Size())
    }
    fmt.Println("-----------------------------------------")
    {
        /*
        type MyData_t struct{
            a       string
            b       int
        }

        var md MyData_t

        //tree := btree.NewWith(md)
        fmt.Println(tree)
        fmt.Println(md)
        */
    }
}
