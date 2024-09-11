#!/bin/bash

path_backlight_brightness=/sys/class/backlight/intel_backlight/

cd $path_backlight_brightness

read max < max_brightness
read current < brightness

if [ "$1" = "+" ]; then
	current=$(($current + 10))

	current=$(( $current > $max ? $max : $current ))
elif [ "$1" = "-" ]; then
	current=$(($current - 10))

	current=$(( $current < 10 ? 10 : $current ))
fi

echo $current > "$path_backlight_brightness/brightness"
