package main

import(
    "fmt"
)


/*
functions in go can accept unlimited numbers of parameters using variadic
functions. in this case, any number of integers can be accepted, then iterated
over.
they can also return multiple things, by just comma seperating the desired
returns and including them in the return in the initialisation.
*/
func biggestNumber(nums ...int) (int,int) {
    start:=0
    for _, num := range nums {
        start += num
    }
    return start, start-start-start
}

func varInCollection(a int, list []int) bool {
    for _, b := range list {
        if b == a {
            return true
        }
    }
    return false
}

func main(){

    /*
    loops work similarly to C, in that, you can instance the iterator in the
    statement. so, for i(int i = 0) i<10, i+1 at the end of each loop.
    generally for statements go as follows:
    for <variable> <conditional> <thing to do on loop end>
    in this case, the variable is i, the conditional is i < 10, so while that
    returns true, keep going. then i++ is the function to perform each loop.
    */
    for i := 0; i < 10; i++ {
        fmt.Println(i)
    }

    /*
    this uses the syntax '_'. this tells the compiler to ignore the index,
    this is used when you don't need it; like in this instance, where
    the array is of finite length, so the conditional returns false and exits
    on it's own.
    */
    numbers := []int{1,2,3}
    for _, num := range numbers {

        fmt.Printf("%d\n",num)
    }

    /*
    if else statements work exactly as intended, can chain them and do whatever
    */

    num := 4
    if varInCollection(num,numbers){
        fmt.Printf("it's in there\n")
    } else if varInCollection(num+1,numbers) || varInCollection(num-1,numbers){
        fmt.Printf("almost\n")
    }else{
        fmt.Printf("no where near\n")
    }

    total,negative_total := biggestNumber(1,2,3,4,5,6,7,8,9,10)
    fmt.Printf("%d %d\n",total,negative_total)
}
