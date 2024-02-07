package main

import(
    "fmt"
)


func main(){

/*
go also has pointers, just like C, and the syntax is effectively identical.
*/

/* & is used to get the address from a var, and *<pointer> is used to *point*
to the value at the address


the function below accepts an integer pointer as input, so it manipulates
whatever value is at that address; in this case, the value of x.
so this edits the value of x without reassigning x.
*/
x := 20
xptr := &x
xval := *xptr
increment(&x)

fmt.Printf("%d %p %d\n",x, xptr, xval)

}


func increment(a *int){
    *a = *a +1
}
