# 3.1 門窗感測
Copyright &copy; 2019 Mickey Chan. ALL RIGHTS RESERVED.  

## 功能
* 感測門是否被開啟；
* 門被開啟時亮起紅色 LED ，並發出警號

## 零件表
* 1 x ESP32 DevKitC 開發板（或兼容板）；
* 2 x 19 針單排母座；
* 1 x 門窗感測器（磁力開關 ＋ 磁石）；
* 1 x 紅色 LED；
* 1 x 220 Ohms 電阻；
* 1 x 有源蜂鳴器；
* 1 x 2 針 2.54mm JST 迷你直針插和座（門窗感測器用）；
* 1 x 麵包板；
* 適量杜邦線

## 門窗感測器
![門窗感測器](../imgs/wired-magnetic-door-sensor.jpg "門窗感測器")

磁力開關（ Reed switch ），又稱為干簧管，常見的是一支小玻璃管，裡面封裝了簧片和惰性氣體，當有磁力靠近時就會閉合通電。而門窗感測器就是把玻璃管封裝在匣子裡，並附上一粒不太強的磁石。安裝在門和門框上，就能感測門窗的開關狀態。

有部分門窗感測器／磁力開關更像繼電器一樣有三支電極，即常開（ NO ，有磁場時接通）、常閉（ NC ，沒有磁場時接通）和 COM ，讓大家可以對不同的磁場狀況作不同處理。

![不同種類的磁力開關](../imgs/reed_switchs.jpg "不同種類的磁力開關")
![磁力開關的原理](../imgs/reed_switch_mechanism.gif "磁力開關的原理")

## 蜂鳴器種類
### 有源蜂鳴器
* 有正負電極之分；
* 只要通電，就能利用內藏的發震器來發聲；
* 給予方形波可以產生不同頻率的聲音

<img src="../imgs/active_buzzer.jpg" width="250" alt="有源蜂鳴器" title="有源蜂鳴器">

### 無源蜂鳴器
* 沒有正負極之分；
* 必須給予方形波或交流電才可以產生指定頻率的聲音；
* 使用起來像一般喇叭

## 接線
* 門窗感測器其中一支電極直接連接 GPIO16 （使用內部 Pull-up），另一電極接地；
* GPIO4 連到紅色 LED ，經 220 Ohm 電阻接地；
* GPIO33 連接到有源蜂鳴器正極，蜂鳴器負極接地

### 線路圖
<img src="../imgs/session_3_1-schematic.png" width="300" alt="門窗感測線路圖" title="門窗感測線路圖">

### 麵包板
<img src="../imgs/session_3_1_breadboard.jpg" width="400" alt="門窗感測麵包板" title="門窗感測麵包板">

## 草稿碼
* 當 GPIO16 （門窗感測器）電壓為 HIGH （門啟）時，將 GPIO4 （紅色 LED）和 GPIO33 （蜂鳴器）設為 HIGH；
* 當 GPIO16 （門窗感測器）電壓為 LOW （門啟）時，將 GPIO4 （紅色 LED）和 GPIO33 （蜂鳴器）設為 LOW

[門窗感測草稿碼](session_3_1.ino)

### 程式解說
首先是常數和變數的宣告：

* 23-25 行：為 GPIO 設定有含意的名稱；
* 27-28 行：設定程式常數；
* 30-34 行：宣告全域變數並設定初始值；

接著是一些功能函式：

* 36-45 行：`gpioSetup()` 設定各 GPIO 的功能，並設定初始電壓。其中連接門窗感測器的 GPIO 可以設定為 INPUT_PULLUP 以使用內部 Pull-up 電阻；
* 47-65 行：`handleDoorState()`檢測門的開啟狀態，如果開啟了就亮起紅色 LED 和響起警號，否則就要關掉。檢測時由於會有門快開和快關之間的曖昩狀態，所以要延遲 0.3 秒以確認狀態；

```cpp
(millis() - lastDoorBounceTime) > DOOR_BOUNCE_DELTA
```

最後就是 Arduino 程式的起始點和循環流程：

* 67-70 行：`setup()`裡要呼叫剛才寫好的`gpioSetup()`設定 GPIO 和串連通訊速度，以便將除錯資料傳回 Arduino IDE ；
* 72-74 行：`loop()`以`DETECT_DOOR_OPENED`的設定決定是否檢查門的開關狀態，並用`handleDoorState()`來檢測門的狀態。
