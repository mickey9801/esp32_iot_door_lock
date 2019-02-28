# EPS32 IoT 物聯網門鎖
這個專案是學習如何使用 ESP32 開發板和 Arduino IDE 來開發物聯網門鎖。這門鎖將會成為「多因素物聯網出入保安系統專案」的組成部分。

## 功能
* 連接本地 Wi-Fi 網絡，並支援 mDNS ；
* 以不同方式開鎖及上：
   *  按掣；
   *  HTTP 請求；
   *  加密的 MQTT/TLS；
   *  Apple Homekit 及 Siri；
* 門鎖會在開鎖後 5 秒重新上鎖；
* 開鎖時亮著綠色 LED；
* 以磁力感測器來感測門的開關狀況，如果門被打開，蜂鳴器須發出聲響，並點亮紅色 LED；
* 當門開啟時，暫緩自動重新上鎖；
* 當門關上後，應在延遲 1.5 秒後自動上鎖，以防門鎖在門未完全關妥時就上鎖；
* 雙擊 ESP32 開發板的 RST 按鈕時轉為 AP 模式，並提供網頁重設 Wi-Fi；
* 以 OTA 方式更新靭體

## 專案槪覽

\#|題目|說明
:--:|---|---
1|ESP32 開發板簡介|<ul><li>專案目標</li><li>接口 （GPIO、SPI、I2C、UART）</li><li>Arduino IDE 開發環境</li></ul>
2|基礎門鎖|<p>建立使用按扭的門鎖系統</p><ul><li>介紹電門鎖規格</li><li>如何使用 TIP120 晶體管控制 12V 電源</li><li>認識附有 LED 的按鈕</li><li>自動重新上鎖 1：單純重新上鎖</li></ul>
3|門窗感測器|<p>當門被打開時發出警號</p><ul><li>門窗感測器應用</li><li>運用主動式蜂鳴器</li><li>警告 LED</li><li>自動重新上鎖 2：延遲重新上鎖</li></ul>
4|連接 Wi-Fi|<p>透過瀏覽器來控制門鎖</p><ul><li>連接 Wi-Fi</li><li>透過 NTP 同步時鐘</li><li>介紹 mDNS 和 Bonjour</li><li>架設網頁伺服器</li><li>開發門鎖 API</li><li>提示開鎖 LED</li><ul>
5|MQTT 第 1 部：經理人端|<p>在 Raspberry Pi 上架設 MQTT 經理人</p><ul><li>認識 MQTT</li><li>安裝 Mosquitto</li><li>設定 Mosquitto</li><li>示範訂閱與出版</li><li>安裝 MQTTBox</li><li>設計題目並測試</li></ul>
6|MQTT 第 2 部：客戶端|<p>使用 MQTT 來控制門鎖</p><ul><li>認識 PubSubClient</li><li>連接 MQTT 經理人</li><li>認識 ArduinoJson</li><li>訂閱門鎖題目並控制門鎖</li><li>發布門鎖和門的狀態</li></ul>
7|MQTT 第 3 部：保安|<p>認識互聯網裝置的基礎保安</p><ul><li>Mosquitto 的認證選擇</li><li>建立用戶＋密碼方式認證</li><li>以 TLS 進行加密連線</li><li>在 Raspberry Pi 建立私人認證中心</li><li>自簽 MQTT 伺服器證書</li><li>在 ESP32 設定 TLS 連線</li><li>認識客戶端證書</li><li>認識存取控制與 ACL （存取控制清單）</li></ul>
8|以 iPhone 來控制|<p>透過 Homekit 和 Siri 來控制門鎖</p><ul><li>Homebridge</li><li>MQTT 插件</li><li>Siri 捷徑</li></ul>
9|以 Google Assistant 來控制|
10|進階功能|<ul><li>分離設定程式碼</li><li>Flash 記憶與 SPIFFS 檔案系統</li><li>OTA 更新</li><li>重設 Wi-Fi （ ESP32 的 WiFiManager 程式庫與 Double Reset Detector ）</li></ul>

## 參考文獻
* [Arduino language reference](https://www.arduino.cc/en/Reference/HomePage)
* [Espressif Arduino core for ESP32 WiFi chip](https://github.com/espressif/arduino-esp32)
* [Espressif ESP32 MQTT Library (ESP-IDF)](https://github.com/espressif/esp-mqtt)
* [lmroy's PubSubClient](https://github.com/Imroy/pubsubclient)
* [Homebridge](https://github.com/nfarina/homebridge)
* [ESP32Dev Board pinout](https://github.com/espressif/arduino-esp32/blob/master/docs/esp32_pinmap.png)

