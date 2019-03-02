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

#define LOCK_LED_PIN     32
#define LOCK_PIN         17
#define BTN_PIN          27

#define DOOR_LED_PIN     4
#define DOOR_SENSOR_PIN  16
#define BUZZER_PIN       33

// Variables
int btnState                     = HIGH; // button not pushed by default
int reedState                    = LOW;  // door closed by default
// Lock related variables
bool isLocked                    = true;
unsigned long lastUnlockTime     = 0;    // The last time unlocked
unsigned long unlockTimeout      = 5000; // Millisecond. For auto-relock
// Door sensor related variables
bool isDoorOpened                = false;
bool detectDoorOpened            = true;
unsigned long lastDoorBounceTime = 0;    // Bounce time for reed sensor
unsigned long doorBounceDelta    = 300;  // Millisecond
unsigned long autoRelockDelay    = 1500; // Delay auto relock for door close

void gpioSetup() {
  // Setup outputs
  pinMode(LOCK_LED_PIN, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(DOOR_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Setup input with pull-up
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP);
  // Initialize outputs
  digitalWrite(LOCK_LED_PIN, LOW);
  digitalWrite(LOCK_PIN, LOW);
  digitalWrite(DOOR_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void lock() {
  digitalWrite(LOCK_LED_PIN, LOW);
  digitalWrite(LOCK_PIN, LOW);
  Serial.println("Door locked");
  isLocked = true;
}

void unlock() {
  digitalWrite(LOCK_LED_PIN, HIGH);
  digitalWrite(LOCK_PIN, HIGH);
  Serial.println("Door unlocked");
  isLocked = false;
  lastUnlockTime = millis();
}

void handlePushButton() {
  btnState = digitalRead(BTN_PIN);
  if (isLocked && btnState == LOW) {
    Serial.println("PushButton pushed");
    unlock();
  }
}

void handleDoorState() {
  reedState = digitalRead(DOOR_SENSOR_PIN);
  // If the door is opened at the first time
  if (reedState == HIGH && !isDoorOpened && (millis() - lastDoorBounceTime) > doorBounceDelta) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(DOOR_LED_PIN, HIGH);
    isDoorOpened = true;
    Serial.println("Door being opened");
    lastDoorBounceTime = millis();
  }
  // If the door being closed from open state
  if (reedState == LOW && isDoorOpened && (millis() - lastDoorBounceTime) > doorBounceDelta) {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(DOOR_LED_PIN, LOW);
    isDoorOpened = false;
    Serial.println("Door being closed");
    lastDoorBounceTime = millis();
  }
}

// Relock the door after delta time if the door is not opened (delay for door close bounce)
void handleAutoRelock() {
  if (!isLocked && !isDoorOpened && (millis() - lastUnlockTime) > unlockTimeout && (millis() - lastDoorBounceTime + doorBounceDelta) > autoRelockDelay) {
    Serial.println("Auto-relock");
    lock();
  }
}

void setup() {
  Serial.begin(115200);
  gpioSetup();
}

void loop() {
  handlePushButton();
  if (detectDoorOpened) handleDoorState();
  handleAutoRelock();
}

