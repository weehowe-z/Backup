#!/bin/sh
make
insmod mtest.ko
cat /proc/mtest
echo "listvma" > /proc/mtest
cat /proc/mtest
echo "listvma 9181" > /proc/mtest
cat /proc/mtest
echo "findpage 0x7fffbda9d000" > /proc/mtest
cat /proc/mtest
echo "writeval 0x7fffbda9d000 0x7fffbda9d023" > /proc/mtest
cat /proc/mtest
rmmod mtest
dmesg | tail -50
