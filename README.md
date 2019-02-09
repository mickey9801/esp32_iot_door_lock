# EPS32 IoT Door Lock
This is a sketch for IoT door lock using EPS32 microcontroller with Arduino IDE. This will be used as a door lock component of Multi-factor IoT door security system project.

Current I am using Adafruit HAZZAH32 Feather for development. I intend to switch to Espressif's ESP32 development board later for lower cost.

## Features
1. Connect local Wi-Fi network with mDNS
2. Lock and Unlock the lock by different way:
  4. Push button
  5. HTTP request (may be removed later)
6. Relock after unlocked for 5 sec.
7. Turn on green LED when unlocked
8. Detect door opened with reed sensor. If opened, beep the buzzer and turn on red LED
9. Delay auto relock when the door opened
10. Resume auto relock when the door closed, with 1.5s delay for sensor bounce

## How To Start
Change `ssid`, `password` as your Wi-Fi AP setup, and set `mDNSName` with any valid hostname you want. The ESP32 will then be able to access using `http://<mDNSName>.local` by browser in the same Wi-Fi network.

## APIs
Method|URI|Params|Description
:----:|:-:|:-----|:----------
GET|/||Lock page with lock state  
POST|/|act=lock\|unlock|Lock or unlock, return lock page with updated lock state
GET|/status||Retrieve lock and door state in JSON format

## TODO
* MQTTs support (topic: comicparty/iot/lock/#)
* Homebridge and Siri support
* Log for lock and door state
* Battery alert (if still using Adafruit ESP32 Feather)

## Reference
* [Arduino language reference](https://www.arduino.cc/en/Reference/HomePage)
* [Espressif Arduino core for ESP32 WiFi chip](https://github.com/espressif/arduino-esp32)
* [Espressif ESP32 MQTT Library (ESP-IDF)](https://github.com/espressif/esp-mqtt)
* [lmroy's PubSubClient](https://github.com/Imroy/pubsubclient)
* [Homebridge](https://github.com/nfarina/homebridge)
* [ESP32Dev Board pinout](https://github.com/espressif/arduino-esp32/blob/master/docs/esp32_pinmap.png)

