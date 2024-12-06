# Theme
active=sddm-alaska-theme
theme_path=/usr/share/sddm/themes/$active

sudo git clone https://github.com/Dequilla/sddm-alaska-theme.git $theme_path
sudo cp /usr/share/sddm/themes/sddm-alaska-theme/Fonts/* /usr/share/fonts/

echo "[Theme]
Current=$active" | sudo tee /etc/sddm.conf
