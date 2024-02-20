#!/bin/bash

targetUrl=$1
echo $targetUrl
accessToken=$(curl -X POST "https://accounts.spotify.com/api/token"\
                -H "Content-Type: application/x-www-form-urlencoded"\
                -d "grant_type=client_credentials&client_id=1b0ac2b304e941d9890dc016171c2226&client_secret=dd8f644ef4074f7f82daca80487818b6" | jq ".access_token"
            )

echo $accessToken
curl --request GET --url $targetUrl --header 'Authorization: Bearer $accessToken'
