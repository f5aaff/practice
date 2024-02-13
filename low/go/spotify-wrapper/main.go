package main

import(
//  "encoding/json"
    "fmt"
//  "io/ioutil"
    "log"
    "net/http"
//  "os"
//  "strconv"
)

const  accessToken string = "Bearer dd8f644ef4074f7f82daca80487818b6"


type getRequest struct {
    authorisation string `json:"Authorisation"`
    targetEndPoint string
    variable string
    value any
}

type fetchRequest struct {
    authorisation string `json:"Authorisation"`
    targetEndPoint string
    body string

}

func sendGetRequest(req *getRequest,client http.Client)(*http.Response){
    endPoint := req.targetEndPoint
    body := fmt.Sprintf("%s/%s",req.variable,req.value)
    call := fmt.Sprintf("%s/%s",endPoint,body)

    request, err := http.NewRequest("GET",call,nil)
    request.Header = http.Header{
        "Authorisation": {accessToken},
    }
    res, err := client.Do(request)

    if err != nil {
        log.Fatal(err)
        return nil
    }
    return res
}

func main() {

    getPlaylists := getRequest{
        targetEndPoint: "https://api.spotify.com/v1/users/",
        authorisation: accessToken,
        variable: "f5adff",
        value: "playlists",
    }

    client := http.Client{}
    res := sendGetRequest(&getPlaylists,client)
    fmt.Println(res)

}
