#!/bin/bash

# vypne vsechny LED

. settings.sh

echo "0" | nc $ARDUINO_IP $ARDUINO_PORT
