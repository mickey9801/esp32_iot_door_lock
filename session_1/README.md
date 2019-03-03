# 1. ESP32 開發板簡介
Copyright &copy; 2019 Mickey Chan. ALL RIGHTS RESERVED.  

## 專案目標：物聯網電門鎖
（整體計劃：物聯網出入保安系統專案）   

### 連接智能助理
  
### 保安考量
(MQTT/TLS)  
(ACL)  

## ESP32 規格
<img src="esp-wroom-32.jpg" width="250" alt="ESP-WROOM-32 模組" title="ESP-WROOM-32 模組" />

* 240MHz 雙核 LX6 微處理器；
* 內藏 448KB ROM；
* 內藏 520KB SRAM ＋ 16KB SRAM ( RTC )；
* 支援 802.11b/g/n Wi-Fi，最大傳輸速度 150Mbps；
* 支援藍牙 BR/EDR BLE；
* 內藏 4MB SPI Flash 記憶，寫入次數最多 100,000 次；
* 內藏霍爾效應感測器及 10 個電容式感應介面；
* 32kHz 水晶發振器
* 支援 SD card 介面；
* 附有 RTC 副系統，可進入超低電量（ ULP ）模式

ESP32 包括以下介面：

* 18 個 12 bits 類比-數碼轉換器 ( ADC ) 頻道（非線性電壓）
* 3 個 SPI 介面（ VSPI 和 HSPI ）
* 3 個 UART 介面
* 2 個 I2C 介面
* 16 個 PWM 輸出頻道
* 2 個 8 bits 數碼-類比轉換器 ( DAC )
* 2 個 I2S 介面
* 10 個電容式感應 GPIO
* 16 個 RTC GPIO ，可用作從低電量模式喚醒 EPS32

Deep Sleep 超低電量模式

實時時鐘（ RTC ）

### 優點
* 可使用 Arduino IDE 編寫程式；
* 原廠 SDK 備有 OTA 更新、網頁伺服器、 UDP 通信等功能；

### 缺點
* 不擅於單精度浮點除數及所有雙精度浮點運算；

## 針腳
![ESP32 Pinmap](esp32-pinout-v2.png?raw=true "ESP32 Pinmap")

不同廠商推出的 ESP32 開發板在針腳位置和數量上都會有所分別，不過相同名稱的針腳在任何廠商的開發板中**功能都是一樣的**！

### 注意事項
* 各 GPIO 電壓為 3.3V ；
* 各 GPIO 絕對最大電流為 40mA ，大於這個電流的電路應使用 MOSFET 來控制（例如繼電器）；
* GPIO 6-11：由於連到 SPI Flash 記憶體，所以隨非你知道自己在做甚麼，否則不要使用；
* GPIO 34-39：由於並沒有內部 Pull-up 或 Pull-down 電阻，也不能產生 PWM ，只能夠用作輸入；
* 所有 GPIO 均可掛載外部插斷（ Interrupt ）處理函式；
* EN：也被稱為 RST ，將此腳接到 GND ，開發板即會重啟；

## 安裝 Arduino IDE ESP32 開發環境
![Arduino IDE](https://raw.githubusercontent.com/espressif/arduino-esp32/master/docs/arduino-ide/win-screenshots/arduino-ide.png "Arduino IDE")

（安裝程序） 
在選單選擇`Arduino`＞`Peferences `＞`Settings`

在`Additional Boards Manager URLs`欄輸入網址`https://dl.espressif.com/dl/package_esp32_index.json`。

如果有多於一個網址，可以按後面的介面按鈕，打開`Additional Boards Manager URLs`視窗，以一行一網址的方式將上述網址加到最後一行。

（開發板管理員）

（程式庫管理員）  

## 基本 ESP32 編程
（連接開發板）  
（上載程式）  
（串行監視器）  

### 小遊戲：利用開發板上的 BOOT 按鈕來控制板上的 LED 閃燈次數
[草稿碼](session_1.ino)

## 參考文獻
* [Arduino language reference](https://www.arduino.cc/en/Reference/HomePage)
* [Espressif Arduino core for ESP32 WiFi chip](https://github.com/espressif/arduino-esp32)
