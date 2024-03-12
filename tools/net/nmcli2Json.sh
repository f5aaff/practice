nmcli -t -f ssid,mode,chan,rate,signal,bars,security device wifi |
    jq -sR 'split("\n") | map(split(":")) | map({
    "network": .[0],
    "mode": .[1],
    "channel": .[2],
    "rate": .[3],
    "signal": .[4],
    "bars": .[5],
    "security": .[6]})'

