#!/system/bin/sh

while true; do
    echo 40 > /sys/class/leds/torch-sec1/brightness
    sleep 1
    echo 0 > /sys/class/leds/torch-sec1/brightness
    sleep 1
done
