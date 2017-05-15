#!/bin/bash

echo "[INFO]begin downloading..."

echo "[INFO]soruce arddress: $1"

aria2c --header "User-Agent: netdisk;5.3.4.5;PC;PC-Windows;5.1.2600;WindowsBaiduYunGuanJia" -s 4 "$1"
