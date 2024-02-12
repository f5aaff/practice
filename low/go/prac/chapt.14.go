package main

import(
    "fmt"
)

/*
maps are go's equivalent to dictionaries or associative arrays.
*/

func main(){
    /*
    map assignments work much like they do in python, however, the use of make
    helps bridge the gap between python's ease of writing and go's more
    strict declarations.
    */

    /*
    here a map is initialised as taking string keys, and integer values.
    then, a key is added with a value of 100.
    */
    map1 := make(map[string]int)
    map1["a"] = 100
    val := map1["a"]
    fmt.Printf("%d",val)
    /*
    maps can be initialised with values as well, using the syntax below.
    */
    map2 := map[string]int{"b":200}
    fmt.Printf("%d",map2["b"])
    /*
    much like in C, printing anything other than straight up characters/strings
    is a miserable experience. afaik, the substitutes are the same as C.
    */
    fmt.Printf("%d",map1["a"])

    /*
    deleting from a map is done with the provided function "delete"
    */
    delete(map1,"a")
}
