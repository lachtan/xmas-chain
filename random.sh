#!/bin/bash

function rand()
{
	max=$1
	echo $[ $RANDOM % $max ]
}

function light()
{
	side=$1
	max=$2
	value=`rand $max`
	echo "$side$value" | nc 192.168.4.55 23
}

if [ $# -eq "0" ]; then
	echo "random.sh <delay>"
	exit 1
fi
delay=$1
while :; do
	light l 10
	light r 10
	light w 50
	sleep $delay
done
