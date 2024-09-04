#!/bin/bash

cp ./config ~/.config

sudo pacman -S sway swaylock swayidle swaybg dmenu wmenu polkit

# Open sway after TTY login (when logged in in terminal)
echo "if [ -z "$WAYLAND_DISPLAY" ] && [ "$XDG_VTNR" -eq 1 ]; then" >> ~/.profile
echo "	exec sway" >> ~/.profile
echo "fi" >> ~/.profile
