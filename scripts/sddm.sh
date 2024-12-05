# Theme
active=sddm-astronaut-theme
theme_path=/usr/share/sddm/themes/$active

sudo pacman -Sy qt6-svg 
sudo git clone https://github.com/keyitdev/sddm-astronaut-theme.git $theme_path
sudo cp /usr/share/sddm/themes/sddm-astronaut-theme/Fonts/* /usr/share/fonts/

echo "[Theme]
Current=$active" | sudo tee /etc/sddm.conf

echo "[General]
background=$HOME/Images/Backgrounds/joris-beugels-alaska.jpg" | sudo tee "$theme_path/theme.conf.user"
