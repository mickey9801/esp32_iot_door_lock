/*
 * ComicParty ESP32 IoT door lock
 * Copyright (C) 2019 Mickey Chan
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
 * Develop for Arduino-ESP32 (Currently)
 * by Mickey Chan (developer AT comicparty.com)
 * 
 */

// Load Wi-Fi library
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define LOCK_LED_PIN 26    // A0
#define DOOR_LED_PIN 25    // A1
#define LOCK_PIN 13
#define BTN_PIN 4          // A5
#define DOOR_PIN 27
#define BUZZER_PIN 21

const String API_VER = "1.0";

// Network credentials
const char* ssid = "ssid";
const char* password = "password";
const char* mDNSName = "hostname";

// Construct web server on port 80
WebServer server(80);

// Variables
int btnState = HIGH; // button not released by default
int reedState = LOW; // door closed by default
// Lock related variables
bool isLocked = true;
unsigned long lastUnlockTime = 0;        // The last time unlocked
unsigned long unlockTimeout = 5000;      // Millisecond. For auto-relock
// Door sensor related variables
bool isDoorOpened = false;
bool detectDoorOpened = true;
unsigned long lastDoorBounceTime = 0;    // Bounce time for reed sensor
unsigned long doorBounceDelta = 300;     // Millisecond
unsigned long autoRelockDelay = 1500;    // Delay auto relock for door close

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
  reedState = digitalRead(DOOR_PIN);
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

// show lock page and lock status
void retrivePage() {
  int lock_state = digitalRead(LOCK_PIN);
  String html = "<!DOCTYPE html><html>\n";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "<link rel=\"icon\" href=\"data:,\">\n";
  html += "<meta http-equiv=\"refresh\" content=\"30\">\n";
  // CSS to style the on/off buttons
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html += ".btn { border: none; color: white; padding: 16px 40px;\n";
  html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\n";
  html += ".lock_btn { background-color: #C40D0D; }\n";
  html += ".unlock_btn { background-color: #4CAF50; }\n";
  html += ".locked { color: #4CAF50; }\n";
  html += ".unlocked { color: #C40D0D; }\n";
  html += ".copyright { font-size: 10px; color: #AAAAAA; }</style></head>\n";
  // HTML body
  html += "<body><h1>ESP32 IoT Door Lock v" + API_VER + "</h1>\n";
  html += "<form method=\"POST\">\n";

  // Display current state and LOCK/UNLOCK button
  if (!lock_state) {
    html += "<p>Lock State <span class=\"locked\">locked</span></p>\n";
    html += "<input type=\"hidden\" name=\"act\" value=\"unlock\" />\n";
    html += "<p><button class=\"btn unlock_btn\">UNLOCK</button></p>\n";
  } else {
    html += "<p>Lock State <span class=\"unlocked\">unlocked</span></p>\n";
    html += "<input type=\"hidden\" name=\"act\" value=\"lock\" />\n";
    html += "<p><button class=\"btn lock_btn\">LOCK</button></p>\n";
  }
  
  html += "</form>\n";
  html += "<p class=\"copyright\">&copy; 2019 Mickey Chan</p>\n";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// handle post requests
void handleQuery() {
  String action = server.arg("act");
  if (action == "lock") {
    lock();
  } else if (action == "unlock") {
      unlock();
  }
  delay(500);
  retrivePage();
}

// return lock and door status in JSON format
void retriveState() {
  char response[255];
  sprintf(response, "{\"uptime\": %ld, \"lock\":\"%s\",\"door\":\"%s\"}", 
    millis(),
    digitalRead(LOCK_PIN) ? "unlocked" : "locked", 
    digitalRead(DOOR_PIN) ? "opened" : "closed");
  server.send(200, "application/json", response);
}

void setup() {
  Serial.begin(115200);
  // Initialize outputs
  pinMode(LOCK_LED_PIN, OUTPUT);
  pinMode(DOOR_LED_PIN, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Initialize input with pull-up
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(DOOR_PIN, INPUT_PULLUP);
  // Set outputs to LOW
  digitalWrite(LOCK_LED_PIN, LOW);
  digitalWrite(DOOR_LED_PIN, LOW);
  digitalWrite(LOCK_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Connect Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.print("WiFi connected to ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(mDNSName)) {
    char buf[255];
    sprintf(buf, "MDNS responder started with name %s.local", mDNSName);
    Serial.println(buf);
  }

  // Setup server and route handlers
  server.on("/", HTTP_GET, retrivePage);           // Query lock page and lock state
  server.on("/", HTTP_POST, handleQuery);          // Set lock state
  server.on("/status", HTTP_GET, retriveState);   // Query lock and door state
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  
  handlePushButton();
  handleDoorState();
  handleAutoRelock();
}

