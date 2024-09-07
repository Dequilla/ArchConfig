#!/bin/bash

date_formatted=$(date "+%a %F %H:%M")

linux_version=$(uname -r | cut -d '-' -f1)

battery_status=$(cat /sys/class/power_supply/BAT0/status)
battery_percent=$(cat /sys/class/power_supply/BAT0/capacity)

echo "Version: $linux_version / $date_formatted / $battery_status battery at $battery_percent%"
