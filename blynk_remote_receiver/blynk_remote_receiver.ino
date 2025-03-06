#include <IRremote.hpp>

int IR_PIN = 36;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN);
  Serial.println("IR Receiver is ready to receive");
}

void loop() {
  if(IrReceiver.decode()){
    Serial.println("\n----- IR Signal Received -----");
    
    // Print the protocol used
    Serial.print("Protocol: ");
    Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));
    
    // Print number of bits
    Serial.print("Number of bits: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);
    
    // Print raw data in different formats
    Serial.print("Raw Data (Dec): ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    
    Serial.print("Raw Data (Hex): 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    
    // Print command and address if available
    Serial.print("Command: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    Serial.print("Address: 0x");
    Serial.println(IrReceiver.decodedIRData.address, HEX);
    
    Serial.println("---------------------------");
    IrReceiver.resume();
  }
}