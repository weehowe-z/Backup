#!/bin/sh
echo "[System Packages Upgrade]"
yaourt -Syu --aur
echo
echo "[Gem Packages Upgrade]"
echo "Proceed to gem upgrade?(VPN required)"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) gem update; break;;
        No ) exit;;
    esac
done
