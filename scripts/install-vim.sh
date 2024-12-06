#!/bin/bash

git clone https://github.com/Dequilla/vimconfig.git && cd vimconfig/ && chmod +x arch-install.sh && ./arch-install.sh
nvim +'PlugInstall --sync' +'qa'

rm -rf ./vimconfig
