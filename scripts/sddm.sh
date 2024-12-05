# Theme
active=maldives
theme_path=/usr/share/sddm/themes/$active

echo "[Theme]
Current=$active" | sudo tee /etc/sddm.conf

echo "[General]
background=$HOME/Images/Backgrounds/joris-beugels-alaska.jpg" | sudo tee "$theme_path/theme.conf"
