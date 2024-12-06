name="Nordic"
theme_path="$HOME/.themes/$name"
if [ -d "$theme_path" ]; then
	rm -rf "$theme_path" 
fi

git clone https://github.com/EliverLara/Nordic.git $theme_path

gsettings set org.gnome.desktop.interface gtk-theme "Nordic"
gsettings set org.gnome.desktop.wm.preferences theme "Nordic"
