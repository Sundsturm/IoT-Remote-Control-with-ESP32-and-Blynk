#include <Arduino.h>
#define DISABLE_CODE_FOR_RECEIVER

#define BLYNK_TEMPLATE_ID "TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "TV Remote Vision TV"
#define BLYNK_AUTH_TOKEN "AUTH_TOKEN"
#define BLYNK_PRINT Serial
#define DECODE_NEC
#define IR_SEND_PIN 15 // Transmitter pin
#define LED_PIN 19
#define LM35_PIN 39

#include <IRremote.hpp>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // Use <BlynkSimpleEsp32.h> for ESP32

uint8_t sRepeats = 0;

BlynkTimer timer; //Blynk Timer

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN; // Replace with your Blynk token

// Array of Hexcodes for IR signals
unsigned long hexCodes[] = {
  0xFF005000, // OFF - 0
  0x946B5000, // GOOGLE ASSISTANT - 1
  0xE31C5000, // RED HORIZONTAL BUTTON - 2
  0xE21D5000, // GREEN HORIZONTAL BUTTON - 3
  0xE51A5000, // YELLOW HORIZONTAL BUTTON - 4
  0xE11E5000, // BLUE HORIZONTAL BUTTON - 5
  0x5DA25000, // REVERSE - 6
  0x5AA55000, // FORWARD - 7
  0x5BA45000, // PLAY/PAUSE - 8
  0x5CA35000, // STOP - 9
  0xF10E5000, // MENU - 10
  0xE8175000, // INFO - 11
  0xB14E5000, // + - 12
  0xE41B5000, // TV GUIDE - 13
  0xE9165000, // BACK - 14
  0xEE115000, // NAVIGATE UP - 15
  0xEB145000, // NAVIGATE RIGHT - 16
  0xEA155000, // NAVIGATE DOWN - 17
  0xED125000, // NAVIGATE LEFT - 18
  0xEC135000, // OK - 19
  0xE01F5000, // VOLUME UP - 20
  0xBF405000, // VOLUME DOWN - 21
  0x956A5000, // HOME - 22
  0xE7185000, // MUTE - 23
  0xEF105000, // CHANNEL NEXT - 24
  0xF00F5000, // CHANNEL BEFORE - 25
  0xFC035000, // 1 - 26
  0xFB045000, // 2 - 27
  0xFA055000, // 3 - 28
  0xF9065000, // 4 - 29
  0xF8075000, // 5 - 30
  0xF7085000, // 6 - 31
  0xF6095000, // 7 - 32
  0xF50A5000, // 8 - 33
  0xF40B5000, // 9 - 34
  0xF30C5000, // 0 - 35
  0xFD025000, // MESSAGES - 36
  0x4BB45000  // FAV - 37
};

void readTemperature(){
  int LManalog = analogRead(LM35_PIN);
  double temperature = LManalog * 0.08058608;
  Blynk.virtualWrite(V18, temperature); // Send to V18; 
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, "WIFI_NAME", "WIFI_PASSWORD"); // Connect to Wi-Fi and Blynk
  IrSender.begin(); // Initialize the IR transmitter
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Initialize OFF for LED
  timer.setInterval(500L, readTemperature);
}

// Blynk virtual pin handlers
BLYNK_WRITE(V0) { if (param.asInt() == 1) sendIRSignal(0); }
BLYNK_WRITE(V1) { if (param.asInt() == 1) sendIRSignal(10); }
BLYNK_WRITE(V2) { if (param.asInt() == 1) sendIRSignal(1); }
BLYNK_WRITE(V3) { if (param.asInt() == 1) sendIRSignal(20); }
BLYNK_WRITE(V4) { if (param.asInt() == 1) sendIRSignal(21); }
BLYNK_WRITE(V5) { if (param.asInt() == 1) sendIRSignal(23); }
BLYNK_WRITE(V6) { if (param.asInt() == 1) sendIRSignal(24); }
BLYNK_WRITE(V7) { if (param.asInt() == 1) sendIRSignal(25); }
BLYNK_WRITE(V8) { if (param.asInt() == 1) sendIRSignal(15); }
BLYNK_WRITE(V9) { if (param.asInt() == 1) sendIRSignal(18); }
BLYNK_WRITE(V10) { if (param.asInt() == 1) sendIRSignal(17); }
BLYNK_WRITE(V11) { if (param.asInt() == 1) sendIRSignal(16); }
BLYNK_WRITE(V12) { if (param.asInt() == 1) sendIRSignal(19); }
BLYNK_WRITE(V13) { if (param.asInt() == 1) sendIRSignal(14); }
BLYNK_WRITE(V14) { if (param.asInt() == 1) sendIRSignal(22); }
BLYNK_WRITE(V15) { if (param.asInt() == 1) sendIRSignal(11); }
BLYNK_WRITE(V16) { if (param.asInt() == 1) sendIRSignal(12); }
BLYNK_WRITE(V17) {
  if (param.asInt() == 1) digitalWrite(LED_PIN, HIGH);
  else digitalWrite(LED_PIN, LOW);
 }

// Function to send IR signal
void sendIRSignal(int index) {
  if (index < 0 || index >= sizeof(hexCodes) / sizeof(hexCodes[0])) return;
  IrSender.sendNECRaw(hexCodes[index], sRepeats); // Send NEC signal
  Serial.printf("Sent signal: 0x%08X\n", hexCodes[index]);
  sRepeats++;
  if(sRepeats > 3) sRepeats = 3;
  delay(500);
}

void loop() {
  Blynk.run(); // Run Blynk
  timer.run(); // Run Blynk Timer
}
