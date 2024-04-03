package go_tify

import (
	"context"
	"errors"
	"fmt"
	agent "github.com/f5aaff/spotify-wrappinator/agent"
	auth "github.com/f5aaff/spotify-wrappinator/auth"
	device "github.com/f5aaff/spotify-wrappinator/device"
	recommendations "github.com/f5aaff/spotify-wrappinator/recommendations"
	requests "github.com/f5aaff/spotify-wrappinator/requests"
	search "github.com/f5aaff/spotify-wrappinator/search"
	"github.com/joho/godotenv"
	"golang.org/x/oauth2"
	"log"
	"net/http"
	"os"
)

const (
	redirectURL = "http://localhost:3000/redirect"
)

var (
	envloaderr          = godotenv.Load()
	state        string = "abc123"
	clientId     string = os.Getenv("CLIENT_ID")
	clientSecret string = os.Getenv("CLIENT_SECRET")
	conf                = auth.New(auth.WithRedirectURL(redirectURL), auth.WithClientID(clientId), auth.WithClientSecret(clientSecret), auth.WithScopes(auth.ScopeUserReadPrivate, auth.ScopeUserReadPlaybackState, auth.ScopeUserModifyPlaybackState, auth.ScopeStreaming))
	validToken   oauth2.Token
	a            = agent.New(conf, agent.WithToken(validToken))
	d            = device.New()
)

func main() {

	if envloaderr != nil {
		return
	}
	/*
		if a token can't be read from file, prompt the user to log in
	*/
	if agent.ReadTokenFromFile(a) == false {

		http.HandleFunc("/callback", AuthoriseSession)
		http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
			log.Println("request: ", r.URL.String())
		})

		url := auth.GetAuthURL(conf, state)
		fmt.Println("Please log in to Spotify by visiting the following page in your browser:", url)

		err := http.ListenAndServe(":8080", nil)
		if err != nil {
			log.Fatal(err)
		}
	}
	err := errors.New("")
	a.Token, err = auth.RefreshToken(conf, context.Background(), a.Token)
	if err != nil {
		log.Fatalf("Token Refresh error: %s", err.Error())
	}
	a.Client = auth.Client(conf, context.Background(), a.Token)

	err = d.GetCurrentDevice(a)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("%+v\n", d)
	// this paused my music, very jarring
	//	err = d.PlayPause(a, "pause")

	_, _ = d.GetCurrentlyPlaying(a)
	_, _ = d.GetQueue(a)
	//	contextUri := "spotify:show:0qw2sRabL5MOuWg6pgyIiY"
	//	err = d.PlayCustom(a, &contextUri, nil, nil)
	//	if err != nil {
	//		fmt.Println(err)
	//	}
	getPlaylistsRequest := requests.New(requests.WithRequestURL("me/playlists"), requests.WithBaseURL("https://api.spotify.com/v1/"))
	paramRequest := requests.New(requests.WithRequestURL("browse/new-releases"), requests.WithBaseURL("https://api.spotify.com/v1/"))
	playerRequest := requests.New(requests.WithRequestURL("me/player/devices"), requests.WithBaseURL("https://api.spotify.com/v1/"))
	requests.GetRequest(a, getPlaylistsRequest)
	requests.ParamRequest(a, paramRequest)
	requests.ParamRequest(a, playerRequest)
	searchRequest := requests.New(requests.WithRequestURL("search"), requests.WithBaseURL("https://api.spotify.com/v1/"))
	requests.ParamRequest(a, searchRequest, search.Query("thy art is murder", nil), search.Types([]string{"artist"}), search.Market("ES"), requests.Limit(1))
	seedVals := map[string][]string{"seed_genres": {"deathmetal"}, "seed_artists": {"3et9upNERQI5IYt5jEDTxM"}}
	percentVals := map[string]int{"max_loudness": 100, "min_loudness": 90}
	intVals := map[string]int{"min_tempo": 80, "max_tempo": 200}
	recRequest := requests.New(requests.WithRequestURL("recommendations"), requests.WithBaseURL("https://api.spotify.com/v1/"))
	_ = requests.ParamRequest(a, recRequest, recommendations.ListParams(seedVals), requests.Limit(1), recommendations.PercentParams(percentVals), recommendations.IntParams(intVals))
	fmt.Printf("%s", string(recRequest.Response))

}

func AuthoriseSession(w http.ResponseWriter, r *http.Request) {
	err := errors.New("")
	a.Token, err = auth.GetToken(a.Conf, r.Context(), state, r)
	if err != nil {
		http.Error(w, "token could not be retrieved", http.StatusForbidden)
		log.Fatal(err)
	}
	log.Println("AuthoriseSession: Storing Token to File...")
	if err = agent.StoreTokenToFile(a.Token); err != nil {
		log.Println("Could Not Save token:" + err.Error())
	}
	if st := r.FormValue("state"); st != state {
		http.NotFound(w, r)
		log.Fatalf("state mismatch: %s != %s\n", st, state)
	}

	_, err = fmt.Fprintf(w, "login successful\n%s", a.Token)
	if err != nil {
		log.Printf("AuthoriseSession: " + err.Error())
		return
	}
}