#!/bin/bash

protocol_version='{ "version": 1 }'

echo "$protocol_version"
echo '['
echo '[]'

while :;
do
	date_formatted=$(date "+%a %F %H:%M:%S")
	date_formatted_json=$(cat <<EndOfString
{
	"name": "Date and Time",
	"full_text": " $date_formatted ",
	"color": "#000000",
	"background": "#ffffff",
	"border": "#ffffff",
	"separator": false,
	"separator_block_width": 0
}
EndOfString
)
	
	linux_version=$(uname -r | cut -d '-' -f1)
	linux_version_json=$(cat <<EndOfString
{
	"name": "Kernel Version",
	"full_text": " $linux_version ",
	"color": "#ffffff",
	"background": "#000000",
	"border": "#000000",
	"separator": false,
	"separator_block_width": 0
}
EndOfString
)
	
	battery_status=$(cat /sys/class/power_supply/BAT0/status)
	battery_percent=$(cat /sys/class/power_supply/BAT0/capacity)
	battery_json=$(cat <<EndOfString
{
	"name": "Battery",
	"full_text": " $battery_status at $battery_percent% ",
	"color": "#ffffff",
	"background": "#000000",
	"border": "#000000",
	"separator": false,
	"separator_block_width": 0
}
EndOfString
)

	# OLD
	# echo "Version: $linux_version / $date_formatted / $battery_status battery at $battery_percent%"
	
	# NEW
	echo ",[$linux_version_json,$battery_json,$date_formatted_json]"
	sleep 1
done
