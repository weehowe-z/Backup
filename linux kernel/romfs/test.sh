#!/bin/sh
make
genromfs -V "vromfs" -f test.img -d img
sudo mount -o loop -t romfs test.img test

echo "[hidden file]"

select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done

sudo umount test
sudo rmmod romfs
sudo insmod romfs.ko hided_file_name=aa
sudo mount -o loop -t romfs test.img test

echo "[Encrypt file]"

select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done

sudo umount test
sudo rmmod romfs
sudo insmod romfs.ko encrypted_file_name=aa
sudo mount -o loop -t romfs test.img test

echo "[Add exec file]"

select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done

sudo umount test
sudo rmmod romfs
sudo insmod romfs.ko exec_file_name=aa
sudo mount -o loop -t romfs test.img test

echo "[clean files]"

select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done

sudo umount test
sudo rmmod romfs
make clean
rm test.img
