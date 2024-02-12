package main

import(
    "fmt"
)

type Person struct {
    Name string
    Age int
}

func(p Person) Speak(){
    fmt.Println("I'm " + p.Name)
}

func(p *Person) PointSpeak(){
    fmt.Println("I'm" + p.Name)
}

type Speaker interface {
    Speak()
}

func SaySomething(s Speaker){
    s.Speak()
}
func main(){

    x := Person{Age:39, Name:"Person"}
    x.Speak()
    x.PointSpeak()
    SaySomething(x)
    SaySomething(&x)
}
