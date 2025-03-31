#include <Arduino.h>

// Includes libraries
//#include <AceButton.h>       // AceButtons for user physical buttons (https://github.com/bxparks/AceButton)
#include <Adafruit_NeoPixel.h> // Adafruit NeoPixel for RGB LED
#include <ModbusRTUSlave.h>
#include <Servo.h>             // Servo library
#include <Pump.h>              // Custom lib for dosing pumps

// Include libs
#include "../inc/Globals.h"
#include "../inc/GPIOs.h"
#include "../inc/Variables.h"

// Flags
bool systemReady = false;  // Used to check if the system have finished the startup sequence
bool shouldReboot = false; // Used to reboot the system on firmware update

// Objects
Adafruit_NeoPixel statusLed = Adafruit_NeoPixel(5, LED_STATUS_PIN, NEO_GRB + NEO_KHZ800);
ModbusRTUSlave modbus(SERIAL_MODBUS);
PumpClass pump1(PUMP_1_PIN);
PumpClass pump2(PUMP_2_PIN);
PumpClass pump3(PUMP_3_PIN);
PumpClass pump4(PUMP_4_PIN);
//Servo servo1;

// Values
bool coils[] {
  true, // Pump 1 enable
  true, // Pump 2 enable
  true, // Pump 3 enable
  true  // Pump 4 enable
};
uint16_t hRegs[] {
  0, // Pump 1 - Flowrate
  0, // Pump 1 - Value
  0, // Pump 2 - Flowrate
  0, // Pump 2 - Value
  0, // Pump 3 - Flowrate
  0, // Pump 3 - Value
  0, // Pump 4 - Flowrate
  0  // Pump 4 - Value
};
int servo1Position = 0;
unsigned long pumpDuration = 0; // Durée d'activation de la pompe en ms

// Setup
void setup() {
  delay(50);

  // Start debug serial
  SERIAL_DEBUG.begin(SERIAL_DEBUG_SPEED);
  //while (!SERIAL_DEBUG);
  delay(50);
  SERIAL_DEBUG.println("BlueGarden Extension - Dosing pump x4");
  SERIAL_DEBUG.println("Booting...");

  // Print hardware informations
  SERIAL_DEBUG.println("System informations :");
  SERIAL_DEBUG.print("    Hardware version : ");SERIAL_DEBUG.println(HARDWARE_VERSION);
  SERIAL_DEBUG.print("    Firmware version : ");SERIAL_DEBUG.println(FIRMWARE_VERSION);
  SERIAL_DEBUG.println();

  // Initialize LED
  SERIAL_DEBUG.println("LED > Initialize LED...");
  statusLed.begin();
  delay(50);
  statusLed.setBrightness(100); // Set LED brightness
  statusLed.setPixelColor(0, statusLed.Color(255, 255, 255)); // Set LED color
  statusLed.show();
  SERIAL_DEBUG.println();

  // Initialize pumps
  SERIAL_DEBUG.println("LED > Initialize pumps...");
  pump1.begin();
  pump2.begin();
  pump3.begin();
  pump4.begin();
  SERIAL_DEBUG.println();

  // Modbus RTU server
  SERIAL_DEBUG.println("LED > Initialize Modbus...");
  // Configure Modbus addresses
  modbus.configureCoils(coils, MB_COILS_COUNT);
  modbus.configureHoldingRegisters(hRegs, MB_HREG_COUNT);
  //modbus.configureDiscreteInputs(discreteInputs, numDiscreteInputs);
  //modbus.configureInputRegisters(inputRegisters, numInputRegisters);
  // Start Modbus
  SERIAL_MODBUS.begin(SERIAL_MODBUS_SPEED, SERIAL_8N1);
  modbus.begin(MODBUS_DEFAULT_ADDRESS, SERIAL_MODBUS_SPEED, SERIAL_8N1);
  SERIAL_DEBUG.println();

  // Servo motor
  // SERIAL_DEBUG.println("LED > Initialize servo motor...");
  // servo1.attach(SERVO_1_PIN);
  // servo1.write(0); // Set servo to home
  // delay(50);
  // servo1.write(180); // Set servo to 180 for testing
  // delay(3000);
  // servo1.write(0); // Set servo to home
  // SERIAL_DEBUG.println();

  // Boot finished
  statusLed.setPixelColor(0, statusLed.Color(0, 255, 0)); // Set LED blue
  statusLed.show();
  
  delay(3000);
  SERIAL_DEBUG.println("SETUP > Startup sequence finished !");
  SERIAL_DEBUG.println("***********************************");
}

// Main program
void loop() {
  bool packetReceived = modbus.poll();

  // Check if packet have been received
  if (packetReceived) {
    //delay(50);
    SERIAL_DEBUG.println("MODBUS > Message received !");
    // Set status LED blue
    statusLed.setPixelColor(0, statusLed.Color(0, 0, 255));
    statusLed.show(); // Update LEDs

    SERIAL_DEBUG.println();
    SERIAL_DEBUG.println("Pompes :");
    SERIAL_DEBUG.print("  1 : ");SERIAL_DEBUG.println(hRegs[1]);
    SERIAL_DEBUG.print("  2 : ");SERIAL_DEBUG.println(hRegs[3]);
    SERIAL_DEBUG.print("  3 : ");SERIAL_DEBUG.println(hRegs[5]);
    SERIAL_DEBUG.print("  4 : ");SERIAL_DEBUG.println(hRegs[7]);

    // Set pumps doses
    if (coils[0]) pump1.dosePump(hRegs[1]);
    if (coils[1]) pump2.dosePump(hRegs[3]);
    if (coils[2]) pump3.dosePump(hRegs[5]);
    if (coils[3]) pump4.dosePump(hRegs[7]);
  }

  // Manage pumps
  pump1.managePump(&hRegs[1]);
  pump2.managePump(&hRegs[3]);
  pump3.managePump(&hRegs[5]);
  pump4.managePump(&hRegs[7]);
  
  // Set servo position
  // servo1Position = map(channelsColor[0][0], 0, 255, 0, 180); /// Scale it for use with the servo (value between 0 and 180)
  // servo1.write(servo1Position);

  // Update status LED
  if (pump1.isActive() || pump2.isActive() || pump3.isActive() || pump4.isActive()) 
    statusLed.setPixelColor(0, statusLed.Color(0, 0, 255)); // Set LED red
  else statusLed.setPixelColor(0, statusLed.Color(0, 255, 0)); // Set LED green
  statusLed.show(); // Update LEDs
}