# This file contains and installs all the required packages
# Append to the packages variable to add packages that auto
# install.
packages=()

# Sway window manager
packages+=(sway swaylock swayidle waybar swaybg polkit gcc qt5-wayland)

# Login manager
packages+=(sddm qt6-svg)

# Fonts
packages+=(noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra)

# Utilities
packages+=(tree neovim brightnessctl yazi grim slurp keepassxc)

sudo pacman -S ${packages[@]}
