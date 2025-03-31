#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

// Generic
#define FIRMWARE_VERSION 0.1
#define HARDWARE_VERSION 1

// Debug Serial configuration
#define SERIAL_DEBUG Serial
#define SERIAL_DEBUG_SPEED 115200

// Modbus configuration
#define SERIAL_MODBUS Serial1
#define SERIAL_MODBUS_SPEED 9600
#define SERIAL_MODBUS_CONFIG SERIAL_8N1
#define MODBUS_DEFAULT_ADDRESS 65 // Dosing pump x4 v1

// Modbus addresses
#define MB_COILS_COUNT 4
#define MB_HREG_COUNT 8

#endif
