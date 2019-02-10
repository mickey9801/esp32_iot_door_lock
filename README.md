# EPS32 IoT Door Lock
This is a sketch for IoT door lock using EPS32 microcontroller with Arduino IDE. This will be used as a door lock component of Multi-factor IoT door security system project.

Current I am using Adafruit HAZZAH32 Feather for development. I intend to switch to Espressif's ESP32 development board later for lower cost.

## Features
* Connect local Wi-Fi network with mDNS
* Lock and Unlock the lock by different way:
   *  Pushbutton
   *  HTTP request (may be removed later)
* Relock after unlocked for 5 sec.
* Turn on green LED when unlocked
* Detect door opened with reed sensor. If opened, beep the buzzer and turn on red LED
* Delay auto relock when the door opened
* Resume auto relock when the door closed, with 1.5s delay for sensor bounce

## Wiring
<img height="550" src="https://raw.githubusercontent.com/mickey9801/eps32_iot_door_lock/master/Door%20Lock%20Sketch_HAZZAH32.jpg?sanitize=true&raw=true" alt="ESP32 IoT door lock wiring" />

## Parts List

### Core
* [Adafruit HUZZAH32 - ESP32 Feather](https://www.adafruit.com/product/3405)
* Headers (HAZZAH32: 12+16pins, ESP32 Dev board: 19+19pins)

### Lock Parts
* [12VDC Solenoid](https://www.adafruit.com/product/1512)
* [TIP120 Power Darlington Transistors](https://www.adafruit.com/product/976)
* [1N4001 Diode](https://www.adafruit.com/product/755)
* [2.1mm DC barrel jack](https://www.adafruit.com/product/373)
* 1kOhm resistor (not require if using MOSFET)

### Push Button Parts
* [Pushbutton - Momentary](https://www.adafruit.com/product/481)
* 4 pin JST plug and socket

### Door Sensor Parts
* [Magnetic contact switch (door sensor)](https://www.adafruit.com/product/375)
* 2 pin JST plug and socket

### LEDs
* 220Ohm resistor x2
* Green and Red LED

### Others
* Active buzzer
* [1/2 sized breadboard](https://www.adafruit.com/product/1609)
* Some wire
* (optional) 3.7V Lithium Ion Battery

## How To Start
Change `ssid`, `password` as your Wi-Fi AP setup, and set `mDNSName` with any valid hostname you want. The ESP32 will then be able to access using `http://<mDNSName>.local` by browser in the same Wi-Fi network.

## APIs
Method|URI|Params|Description
:----:|:-:|:-----|:----------
GET|/||Lock page with lock state  
POST|/|act=lock\|unlock|Lock or unlock, return lock page with updated lock state
GET|/status||Retrieve lock and door state in JSON format

## ToDo
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

