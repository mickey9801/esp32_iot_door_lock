#define LOCK_LED_PIN 32
#define LOCK_PIN     17
#define BTN_PIN      27

// Variables
int btnState = HIGH; // button not pushed by default
bool isPushed = false;
// Lock related variables
bool isLocked = true;
unsigned long lastUnlockTime = 0;        // The last time unlocked
unsigned long unlockTimeout = 5000;      // Millisecond. For auto-relock

void gpioSetup() {
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
  if (!isLocked &&  (millis() - lastUnlockTime) > unlockTimeout) {
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
  handleAutoRelock();
}
