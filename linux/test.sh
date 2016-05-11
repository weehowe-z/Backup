#!/bin/sh
make
insmod mtest.ko
cat /proc/mtest
echo "hello" > /proc/mtest
cat /proc/mtest
echo "listvma" > /proc/mtest
cat /proc/mtest
echo "listvma1" > /proc/mtest
cat /proc/mtest
rmmod mtest
dmesg | tail -50
