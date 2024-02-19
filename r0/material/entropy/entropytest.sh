#!/bin/sh

# this file 
ESTIMATE=/proc/sys/kernel/random/entropy_avail

# reads 4 kilobyte of data from /dev/random, stops after 3s
timeout 3s dd if=/dev/random bs=4k count=1 2> /dev/null | base64

# shows current entropy estimate
ent=`cat $ESTIMATE`

# wait until entropy estimate reaches 128
while [ $ent -lt 128 ]
do
    # sleep for 3 seconds
    sleep 3    
    # get and show the estimate
    ent=`cat $ESTIMATE` 
    echo $ent 
done

dd if=/dev/random bs=8 count=1 2> /dev/null | base64
cat $ESTIMATE
