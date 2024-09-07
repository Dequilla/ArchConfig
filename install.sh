#!/bin/bash

cp -r ./config $HOME/.config

sudo pacman -S sway swaylock swayidle swaybg dmenu wmenu polkit

if [ ! -f $HOME/.profile ]; then
	touch $HOME/.profile
fi

# Open sway after TTY login (when logged in in terminal)
start_sway_commands='if [ -z "$WAYLAND_DISPLAY" ] && [ "$XDG_VTNR" -eq 1 ]; then
	exec sway
fi'

if [[ $(cat ~/.profile | grep -i "$start_sway_commands") ]]; then
	echo $start_sway_commands >> "$HOME/.profile"
else
	echo "Start sway command already in .profile."
fi

if [ ! -d "$HOME/Images/Backgrounds" ]; then
	echo "~/Images/Backgrounds not found, creating."
	mkdir -p "$HOME/Images/Backgrounds"
fi
echo "Adding background image to ~/Images/Backgrounds/"
cp "./images/casper-van-battum-gotland-background.jpg" "$HOME/Images/Backgrounds/casper-van-battum-gotland-background.jpg"
