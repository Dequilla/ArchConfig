# This file contains and installs all the required packages
# Append to the packages variable to add packages that auto
# install.
packages=()

# Sway window manager
packages+=(sway swaylock swayidle swaybg dmenu wmenu polkit gcc keepassxc qt5-wayland)

# Login manager
packages+=(sddm)

# Fonts
packages+=(noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra)

# Utilities
packages+=(vim tree neovim brightnessctl yazi)

sudo pacman -S ${packages[@]}
