#!/bin/bash

#######################
# Sway Window Manager #
#######################

if [ ! -d "$HOME/.config/sway/" ]; then
	mkdir -p "$HOME/.config/sway"	
fi
cp -rf "./config/sway/config" "$HOME/.config/sway/config"
cp -rf "./status-bar.sh" "$HOME/.config/sway/status-bar.sh"
sudo chmod 744 "$HOME/.config/sway/status-bar.sh"

sudo pacman -S sway swaylock swayidle swaybg dmenu wmenu polkit

if [ ! -f $HOME/.profile ]; then
	touch $HOME/.profile
fi

# Open sway after TTY login (when logged in in terminal)
start_sway_commands='if [ -z "$WAYLAND_DISPLAY" ] && [ "$XDG_VTNR" -eq 1 ]; then
	exec sway
fi'

if grep -q 'exec sway' "$HOME/.profile"
then
	echo "Start sway command already in .profile."
else
	echo "$start_sway_commands" >> "$HOME/.profile"
fi

if [ ! -d "$HOME/Images/Backgrounds" ]; then
	echo "~/Images/Backgrounds not found, creating."
	mkdir -p "$HOME/Images/Backgrounds"
fi
echo "Adding background image to ~/Images/Backgrounds/"
cp "./images/casper-van-battum-gotland-background.jpg" "$HOME/Images/Backgrounds/casper-van-battum-gotland-background.jpg"

######################
# SDDM Login Manager #
######################

sudo pacman -S sddm

sudo systemctl enable sddm.service

if [[ -f "/etc/systemd/system/display-manager.service" ]]; then
	sudo unlink "/etc/systemd/system/display-manager.service"
fi

sudo ln -sf /usr/lib/systemd/system/sddm.service /etc/systemd/system/display-manager.service 
