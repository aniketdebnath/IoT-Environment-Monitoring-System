#include <DHT.h>

// Pin definitions
#define DHTPIN 2          // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // DHT 11 type
#define LDRPIN A0         // Analog pin connected to the LDR
#define BUZZER_PIN 8       // Digital pin connected to the buzzer
#define GREEN_LED_PIN 10       // Digital pin connected to the green LED
#define RED_LED_PIN 9        // Digital pin connected to the red LED
#define YELLOW_LED_PIN 11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Thresholds and control variables
int tempThresholdHigh = 30; // Temperature high threshold
int lightLevelDark = 100;   // Light level considered "dark"


void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();
  Serial.begin(9600);
}

// Global variables to track the blinking state and timing
unsigned long previousMillis = 0;
const long ledBlinkInterval = 100; // blink interval for LEDs in milliseconds
const long buzzerInterval = 250; // interval for buzzer beeping in milliseconds

// Function to blink any LED
void blinkLED(int pin) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= ledBlinkInterval) {
        previousMillis = currentMillis;
        digitalWrite(pin, !digitalRead(pin)); // Toggle the LED state
    }
}

// Function to blink multiple LEDs together
void blinkLEDsTogether(int pin1, int pin2) {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= ledBlinkInterval) {
        previousMillis = currentMillis;
        
        // Toggle both LEDs at the same time
        digitalWrite(pin1, !digitalRead(pin1));  // Toggle the first LED
        digitalWrite(pin2, !digitalRead(pin2));  // Toggle the second LED
    }
}

// Function to beep the buzzer
void beepBuzzer() {
    static unsigned long lastBuzzerToggle = 0;
    static bool buzzerState = false;
    
    unsigned long currentMillis = millis();
    if (currentMillis - lastBuzzerToggle >= buzzerInterval) {
        lastBuzzerToggle = currentMillis;
        buzzerState = !buzzerState;  // Toggle the buzzer state
        digitalWrite(BUZZER_PIN, buzzerState);
    }
}

// Handle LEDs and buzzer based on sensor readings
void handleLEDsAndBuzzer(float temp, int lightLevel) {
    bool shouldBuzz = false;  // Flag to determine if the buzzer should be on

    if (temp > tempThresholdHigh) {
        // Blink red and green LEDs together
        blinkLEDsTogether(RED_LED_PIN, GREEN_LED_PIN);
        shouldBuzz = true;  // Set buzzer flag
    } else {
        digitalWrite(RED_LED_PIN, LOW);     
        digitalWrite(GREEN_LED_PIN, HIGH);
    }  

    // Handling light level for the yellow LED and buzzer
    if (lightLevel < lightLevelDark) {
        digitalWrite(YELLOW_LED_PIN, HIGH);  // Keep yellow LED on for dark but not very dark
        shouldBuzz = true;  // Set buzzer flag
    } else {
        digitalWrite(YELLOW_LED_PIN, LOW);   // Turn off yellow LED if not dark
    }

    // Activate or deactivate the buzzer based on the flag
    if (shouldBuzz) {
        beepBuzzer();  // Beep the buzzer
    } else {
        digitalWrite(BUZZER_PIN, LOW);  // Ensure buzzer is off
    }
}

void loop() {
if (Serial.available() > 0) {
        String serialInput = Serial.readStringUntil('\n');
        Serial.println("Received: " + serialInput);  // Echo for debugging
        if (serialInput.startsWith("SET_TEMP:")) {
            tempThresholdHigh = serialInput.substring(9).toInt();
            Serial.print("New temp threshold set to: ");
            Serial.println(tempThresholdHigh);
        } else if (serialInput.startsWith("SET_LIGHT:")) {
            lightLevelDark = serialInput.substring(10).toInt();
            Serial.print("New light level threshold set to: ");
            Serial.println(lightLevelDark);
        }
    }
  // Read humidity and temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature as Celsius
  int lightLevel = analogRead(LDRPIN); // Read light level
  lightLevel = map(lightLevel, 0, 1023, 0, 255); // Map light level to 0-255

  // Print the results to the Serial Monitor
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.println(lightLevel);

  // Handle LEDs and buzzer based on readings
  handleLEDsAndBuzzer(t, lightLevel);

  delay(1000);
}