#!/bin/bash

sudo pacman -S --noconfirm vim

git clone https://github.com/Dequilla/vimconfig.git && cd vimconfig/ && chmod +x arch-install.sh && ./arch-install.sh
vim +'PlugInstall --sync' +qa

rm -rf ./vimconfig
