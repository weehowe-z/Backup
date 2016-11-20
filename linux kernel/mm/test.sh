#!/bin/sh
rmmod mtest

echo "------------"

make
insmod mtest.ko
cat /proc/mtest
echo "listvma" > /proc/mtest
# cat /proc/mtest
echo "listvma 9181" > /proc/mtest
# cat /proc/mtest
echo "findpage 0x400000" > /proc/mtest
# cat /proc/mtest
echo "writeval 0x7fffbda9d000 0x1" > /proc/mtest
# cat /proc/mtest
dmesg -c
