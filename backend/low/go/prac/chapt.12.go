package.main






func main(){
/*
Slices & arrays are similar, both function similarlu to python arrays in both
declaration and function.
*/

//arrays
var arr = [3]string{"a","b","c"}
arr2 := arr
arr[2] = "d"

//Slices

/*
Arrays in go are fixed length, although iterable. slices are variable in size.
under the hood they are effectively an array with some abstraction on top.
think linked lists in C.
*/
var slice []string

//or with values

slice := []string{"1","2","3"}

/*
of a specific length using make, producing a slice of 3 empty strings in
this case.
*/
slice := make([]string,3)

/*
from an existing slice
note: append requires a new slice as it's assigned variable, as the original
is unmodified, it returns a new slice with the contents of the inputs.
*/
newslice := append(slice,"1","2")

/*
copy can be used to make a duplicate a slice, producing an independent
copy of the original in memory.
this requires a slice to be declared first, and if the slice that is copied to
is too short, the slice will be copied to until it runs out of space.
*/
copy(newslice,myslice)

/*
slices can be initialised from arrays, using the same slicing used in strings
copying from one position to another.
*/

slice = arr[:]
fmt.println(slice[2],arr[2])
slice = arr[0:1]
fmt.println(slice)

/*
make has a 3rd parameter, for capacity. so a slice can be initalised with empty
values, and consistent of a certain capacity.
*/

slice := make([]string,0,10)
//this would be an empty slice, of length 0, with a *capacity* of 10.



}
