#!/bin/sh
sudo modprobe -r vboxnetflt
sudo modprobe -r vboxnetadp
sudo modprobe -r vboxpci
sudo modprobe -r vboxdrv