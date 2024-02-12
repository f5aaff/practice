package main

import (
"strings"
)



/*
Go is a typed language, but can also infer type based on the variables contents.
so  var x = "xyz" would be typed as a string.

this covers strings, as well as some notes on variable assignment; including the short hand
for initialising a variable.
*/



func main(){
    var test = "test"
    var length = len(test)


    /*this affectively slices a string, saying
    "test1 is equivalent to test[0] to test[-1]."
    slicing strings works almost exactly the same as in python.
    */
    var test1 = test[:]


    /*
    the strings library holds all the usual tools for case changing, splitting and joining.
    */
    strings.HasPrefix("test","te")


}
