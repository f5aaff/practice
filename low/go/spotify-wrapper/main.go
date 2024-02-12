package main

import(
    "encoding/json"
    "fmt"
    "io/ioutil"
    "log"
    "net/http"
    //"os"
    //"strconv"
)

//type caller interface{
//    PostReq(*reqStruc)
//    GetReq(*reqStruc)
//}

type reqStruct struct {
    targetUrl string
    info string
}
func PostReq(reqStruc *reqStruct){

    target := reqStruc.targetUrl

    response, err := http.Get(target)

    if err!=nil{
        fmt.Print(err.Error())
    }

    responseData, err := ioutil.ReadAll(response.Body)
    if err != nil {
        log.Fatal(err)
        return
    }

    json.Unmarshal(responseData,reqStruc.info)
    //reqStruc.info = responseData
}

func main() {
    reqStruc :=  reqStruct{
        targetUrl:"http://pokeapi.co/api/v2/pokedex/kanto/",
        info: ""}
    PostReq(&reqStruc)
    fmt.Println(reqStruc.info)
    //var s string;
    //json.Unmarshal(reqStruc.info,s)
    //fmt.Println(s)
}
