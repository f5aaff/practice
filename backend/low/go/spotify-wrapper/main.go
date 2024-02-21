
 package main

import (
    "encoding/base64"
    "encoding/json"
    "fmt"
    "io/ioutil"
    "net/http"
    "net/url"
    "strings"
    "math/rand"
)



/*
constants, client ID and secret grabbed from dev page on spotify for the api.
*/
const (
    spotifyAPIBaseURL = "https://api.spotify.com/v1"
    clientID          = "1b0ac2b304e941d9890dc016171c2226"
    clientSecret      = "dd8f644ef4074f7f82daca80487818b6"

/*
this is definitely wrong, despite being what was entered on the web page,
either need to pick apart an existing wrapper and see what the hell they put,
or bang head against wall until epiphany
*/
redirectURI          = "localhost:8080"

letterBytes          = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
)



	http.HandleFunc("/callback", callbackHandler)
	http.HandleFunc("/token", tokenHandler)

	go func() {
		fmt.Println("Opening the Spotify Login Dialog in your browser...")
		err := exec.Command("xdg-open", URL).Run() // macOS open command
		if err != nil {
			log.Println("Error opening browser:", err)
		}
	}()



	err := http.ListenAndServe(fmt.Sprintf(":%d", PORT), nil)
	if err != nil {
		log.Fatal("Error starting server:", err)
	}
}

func main() {
    // Get an access token
    token, err := getAccessToken()
   	http.HandleFunc("/callback", callbackHandler)
	http.HandleFunc("/token", tokenHandler)
	go func() {
		fmt.Println("Opening the Spotify Login Dialog in your browser...")
		err := exec.Command("xdg-open", URL).Run() // macOS open command
		if err != nil {
			log.Println("Error opening browser:", err)
		}
	}()

	err := http.ListenAndServe(fmt.Sprintf(":%d", PORT), nil)
	if err != nil {
		log.Fatal("Error starting server:", err)
	}
}

    // Example: Get a user's profile
    userProfile, err := getUserProfile(token)
    if err != nil {
        fmt.Println("Error fetching user profile:", err)
        return
    }
    fmt.Println(userProfile)
    fmt.Printf("User ID: %s\nDisplay Name: %s\n", userProfile.ID, userProfile.DisplayName)

    playlists,err:= getUserPlaylists(token)
    if err != nil{
        fmt.Println("Error fetching playlists:", err)
        return
    }

    for playlist := range playlists{
        fmt.Println(playlist)
    }

}


func randString(n int) string{
    b := make([]byte,n)
    for i := range b {
        b[i] = letterBytes[rand.Intn(len(letterBytes))]
    }
    return string(b)
}

func getAccessToken() (string, error) {
    // Base64 encode the client ID and secret
    authHeader := base64.StdEncoding.EncodeToString([]byte(clientID + ":" + clientSecret))

    // Create a POST request to get the access token
    reqBody := strings.NewReader("grant_type=client_credentials")
    req, err := http.NewRequest("POST", "https://accounts.spotify.com/api/token", reqBody)
    if err != nil {
        return "", err
    }
    /*
    headers need to be set as such, auth is just the AccessToken
    the content type needs to be form encoded, can't just hand it json afaik
    */
    req.Header.Set("Authorization", "Basic "+authHeader)
    req.Header.Set("Content-Type", "application/x-www-form-urlencoded")

    // Send the request
    client := &http.Client{}
    resp, err := client.Do(req)
    if err != nil {
        return "", err
    }
    defer resp.Body.Close()

    // Read the response body
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        return "", err
    }

    // Parse the JSON response
    // THIS IS DEFINITELY NOT A GOOD WAY TO PARSE JSON, WILDLY UNSAFE
    accessToken := string(body)
    return accessToken, nil
}

func userAuthRequest(w http.ResponseWriter,r *http.Request){
    state:= randString(16)
    scope := "user-read-private user-read-email"
    redirect := fmt.Sprintf("https://accounts.spotify.com/authorize?%s",
        url.Values{
            "response_type" : {"code"},
            "client_id": {clientID},
            "scope": {scope},
            "redirect_uri": {redirectURI},
            "state": {state},
        }.Encode())
    http.Redirect(w,r,redirect,http.StatusFound)
}


func getUserProfile(token string) (*UserProfile, error) {
    // Create a GET request to fetch the user profile
    req, err := http.NewRequest("GET", spotifyAPIBaseURL+"/me", nil)
    if err != nil {
        return nil, err
    }
    req.Header.Set("Authorization", "Bearer "+token)

    // Send the request
    client := &http.Client{}
    resp, err := client.Do(req)
    if err != nil {
        return nil, err
    }
    defer resp.Body.Close()

    // Parse the JSON response
    var userProfile UserProfile
    err = json.NewDecoder(resp.Body).Decode(&userProfile)
    if err != nil {
        return nil, err
    }

    return &userProfile, nil
}

// Define a struct to hold user profile data
type UserProfile struct {
    ID           string `json:"id"`
    DisplayName  string `json:"display_name"`
}


func getUserPlaylists(token string) ([]Playlist, error) {
    // Create a GET request to fetch user playlists
    req, err := http.NewRequest("GET", spotifyAPIBaseURL+"/me/playlists", nil)
    if err != nil {
        return nil, err
    }
    req.Header.Set("Authorization", "Bearer "+token)

    // Send the request
    client := &http.Client{}
    resp, err := client.Do(req)
    if err != nil {
        return nil, err
    }
    defer resp.Body.Close()

    // Parse the JSON response
    var playlistsResponse struct {
        Items []Playlist `json:"items"`
    }
    err = json.NewDecoder(resp.Body).Decode(&playlistsResponse)
    if err != nil {
        return nil, err
    }

    return playlistsResponse.Items, nil
}
func getRefreshToken(authCode string) (string, error) {
    // Base64 encode the client ID and secret
    authHeader := base64.StdEncoding.EncodeToString([]byte(clientID + ":" + clientSecret))

    // Create a POST request to exchange the authorization code for tokens
    reqBody := strings.NewReader(fmt.Sprintf("grant_type=authorization_code&code=%s&redirect_uri=%s", authCode, redirectURI))
    req, err := http.NewRequest("POST", "https://accounts.spotify.com/api/token", reqBody)
    if err != nil {
        return "", err
    }
    req.Header.Set("Authorization", "Basic "+authHeader)
    req.Header.Set("Content-Type", "application/x-www-form-urlencoded")

    // Send the request
    client := &http.Client{}
    resp, err := client.Do(req)
    if err != nil {
        return "", err
    }
    defer resp.Body.Close()

    // Read the response body
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        return "", err
    }

    // Parse the JSON response
    var tokenResponse struct {
        RefreshToken string `json:"refresh_token"`
    }
    err = json.Unmarshal(body, &tokenResponse)
    if err != nil {
        return "", err
    }

    return tokenResponse.RefreshToken, nil
}

func callbackHandler(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "callback.html")
	if r.URL.Query().Get("error") != "" {
		log.Printf("Something went wrong. Error: %s", r.URL.Query().Get("error"))
	}
}

func tokenHandler(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusOK)
	token := r.URL.Query().Get("access_token")
	if token != "" {
		cmd := exec.Command("setclip") // macOS clipboard command
		cmd.Stdin = strings.NewReader(token)
		if err := cmd.Run(); err != nil {
			log.Println("Error copying token to clipboard:", err)
		}
		fmt.Println("Your token is:", token)
		fmt.Println("(It has been copied to your clipboard)")
	}
	os.Exit(0)
}

// Define a struct to hold playlist data
type Playlist struct {
    ID   string `json:"id"`
    Name string `json:"name"`
    // Add other relevant fields as needed
}
