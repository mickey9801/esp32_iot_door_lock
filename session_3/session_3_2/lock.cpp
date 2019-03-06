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

#include "settings.h"
#include "lock.h"
#include "door.h"

// Variables
int btnState                     = HIGH; // button not pushed by default
bool isLocked                    = true;
unsigned long lastUnlockTime     = 0;    // The last time unlocked

// Functions
void lockSetup() {
  // Setup outputs
  pinMode(LOCK_LED_PIN, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  // Setup input with pull-up
  pinMode(BTN_PIN, INPUT_PULLUP);
  // Initialize outputs
  digitalWrite(LOCK_LED_PIN, LOW);
  digitalWrite(LOCK_PIN, LOW);
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

// Relock the door after delta time if the door is not opened (delay for door close bounce)
void handleAutoRelock() {
  if (!isLocked && 
    !isDoorOpened && 
    (millis() - lastUnlockTime) > UNLOCK_TIMEOUT && 
    (millis() - lastDoorBounceTime + DOOR_BOUNCE_DELTA) > AUTO_RELOCK_DELAY
  ) {
    Serial.println("Auto-relock");
    lock();
  }
}


