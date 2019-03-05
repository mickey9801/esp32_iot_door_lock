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
#include "door.h"

// Variables
int reedState                    = LOW;   // door closed by default
bool isDoorOpened                = false;
unsigned long lastDoorBounceTime = 0;     // Bounce time for reed sensor

// Functions
void doorSetup() {
  // Setup outputs
  pinMode(DOOR_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Setup input with pull-up
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP);
  // Initialize outputs
  digitalWrite(DOOR_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void handleDoorState() {
  reedState = digitalRead(DOOR_SENSOR_PIN);
  // If the door is opened at the first time
  if (reedState == HIGH && !isDoorOpened && (millis() - lastDoorBounceTime) > DOOR_BOUNCE_DELTA) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(DOOR_LED_PIN, HIGH);
    isDoorOpened = true;
    Serial.println("Door being opened");
    lastDoorBounceTime = millis();
  }
  // If the door being closed from open state
  if (reedState == LOW && isDoorOpened && (millis() - lastDoorBounceTime) > DOOR_BOUNCE_DELTA) {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(DOOR_LED_PIN, LOW);
    isDoorOpened = false;
    Serial.println("Door being closed");
    lastDoorBounceTime = millis();
  }
}


