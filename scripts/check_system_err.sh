#!/bin/sh
echo "[check failed systemd services]"
systemctl --failed
echo "------------" 
echo "[check high priority errors in the systemd journal]"
#journalctl -p 3 -xb
dmesg -l err
echo "------------" 
echo "[check broken symlinks]"
find . -type l -! -exec test -e {} \; -print
rm $(find . -type l -! -exec test -e {} \; -print)
echo "------------" 
