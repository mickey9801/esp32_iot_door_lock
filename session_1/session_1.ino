/*
 * ComicParty ESP32 IoT door lock
 * Copyright (C) 2019 Mickey Chan. ALL RIGHTS RESERVED.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * Develop for Arduino-ESP32
 * by Mickey Chan (developer AT comicparty.com)
 * 
 */

#define LED_PIN   2
#define BTN_PIN   0

// Variables
long lastPushing = 0;
bool isPushed    = false;
int  pushCount   = 0;

void gpioSetup () {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);      // No need for pull-up
  digitalWrite(LED_PIN, HIGH);  // Set HIGH for dim the LED
}

void handlePushbutton () {
  int btn = digitalRead(BTN_PIN);
  long now = millis();
  if (!isPushed && btn == LOW && (now - lastPushing) > 300) {
    lastPushing = now;
    ++pushCount;
    Serial.print("Pushed ");
    Serial.println(pushCount);
    isPushed = true;
  } else if (isPushed && btn == HIGH) {
    isPushed = false;
  }
}

void publishButton () {
  int btn = digitalRead(BTN_PIN);
  long now = millis();  
  if (!isPushed && btn == HIGH && pushCount > 0 && (now - lastPushing) > 1300) {
    Serial.println("Flash LED...");
    flashingLED(pushCount);
    pushCount = 0;
  }
}

void flashingLED (int t) {
  for (int i=0; i<t; i++) {
    digitalWrite(LED_PIN, LOW);
    delay(300);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
  }
}

void setup() {
  Serial.begin(115200);
  gpioSetup();
}

void loop() {
  handlePushbutton();
  publishButton();
}
