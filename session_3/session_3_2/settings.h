#ifndef SETTINGS_H
#define SETTINGS_H

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

#include <Arduino.h>

#define LOCK_LED_PIN     32
#define LOCK_PIN         17
#define BTN_PIN          27

#define DOOR_LED_PIN     4
#define DOOR_SENSOR_PIN  16
#define BUZZER_PIN       33

#define DETECT_DOOR_OPENED true

#define UNLOCK_TIMEOUT     5000  // Millisecond. For auto-relock
#define DOOR_BOUNCE_DELTA  300   // Millisecond
#define AUTO_RELOCK_DELAY  1500  // Delay auto relock for door close

#endif /* SETTINGS_H */

