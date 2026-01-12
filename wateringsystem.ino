#include <LiquidCrystal.h>

const int sensorPin = A0;
const int relayPin = 4;
const int buttonPin = 1;
const int modeButtonPin = 5;  // Pin connected to the mode toggle button
const int ledPin = 6;         // Pin connected to the LED

bool relayState = false;
bool lastButtonState = LOW;
bool lastModeButtonState = HIGH;
bool mode = false;           // false = manual, true = automatic

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000; // 1 second

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// --- UPDATED: based on your sensor behavior ---
const int dryValue = 530;    // DRY = low analog value
const int wetValue = 235;   // WET = high analog value

// Scale raw sensor values into a percent or range (0-50)
int getScaledValue(int rawValue) {
  int val = map(rawValue, dryValue, wetValue, 0, 50);
  if (val < 0) return 0;
  if (val > 50) return 50;
  return val;
}

void setup() {
  delay(200); // Give LCD time to power up
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Soil Moisture:");

  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(modeButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, mode ? LOW : HIGH);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
  bool currentModeButtonState = digitalRead(modeButtonPin);

  // Toggle between auto/manual mode
  if (currentModeButtonState == LOW && lastModeButtonState == HIGH) {
    mode = !mode;
    digitalWrite(ledPin, mode ? LOW : HIGH); // LED ON in manual mode
    relayState = mode ? relayState : false;  // Reset relay in manual mode
    delay(50); // debounce
  }
  lastModeButtonState = currentModeButtonState;

  int sensorValue = analogRead(sensorPin);
  int scaledValue = getScaledValue(sensorValue);

  if (mode) {
    // AUTO mode logic — dry = low value, wet = high value
    if (scaledValue <= 10) {
      delay(100);
      relayState = false; // start watering
    } else if (scaledValue >= 45) {
      relayState = true; // stop watering
    }
    digitalWrite(relayPin, relayState);
  } else {
    // MANUAL mode logic
    if (currentButtonState == LOW && lastButtonState == HIGH) {
      relayState = !relayState;
      digitalWrite(relayPin, relayState);
    }
    lastButtonState = currentButtonState;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    lcd.setCursor(0, 0);
    lcd.print("Value: ");
    lcd.print(scaledValue);
    lcd.print("    ");

    lcd.setCursor(0, 1);
    lcd.print("Raw: ");
    lcd.print(sensorValue);
    lcd.print("    ");

    // Debugging to Serial Monitor
    Serial.print("Raw Sensor Value: ");
    Serial.print(sensorValue);
    Serial.print(" | Scaled: ");
    Serial.println(scaledValue);

    Serial.print("Mode: ");
    Serial.println(mode ? "Auto" : "Manual");
    Serial.print("Relay: ");
    Serial.println(relayState ? "ON" : "OFF");
  }

  delay(100);
}
