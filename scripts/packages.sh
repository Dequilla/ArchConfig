# This file contains and installs all the required packages
# Append to the packages variable to add packages that auto
# install.
packages=()

# Sway window manager
packages+=(sway swaylock swayidle swaybg dmenu wmenu polkit gcc)

# Login manager
packages+=(sddm)

# Utilities
packages+=(vim tree)

sudo pacman -S ${packages[@]}
