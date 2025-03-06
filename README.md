# IoT-Remote-Control-with-ESP32-and-Blynk
An IoT remote control that controls the TV, LED, and temperature measurements in real-time with ESP32 and Blynk.

The circuit uses KY-022 as an IR-receiver and KY-005 as an IR-transmitter.
Furthermore, the circuit is divided into two parts: an IR-receiver circuit and an IR-transmitter circuit.
Both circuit parts can be built using the predefined pins in the code.
The IR-receiver circuit only uses KY-022, but the IR-transmitter uses KY-005, LM35 for temperature measurements in real-time, and LED with 220Ohms resistor.
Blynk is used on the IR-transmitter circuit.

As an additional note, KY-022 and KY-005 have 3 pins: GND, VCC+ (5V), and Signal.
