#!/bin/bash

# meni nahodne intenzitu jednotlivych svetelnych vetvi

set -o nounset

. settings.sh

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
	echo "$side$value" | nc $ARDUINO_IP $ARDUINO_PORT
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


