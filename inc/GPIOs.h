#ifndef GPIOS_H
#define GPIOS_H

// RS485 pins
#define MODBUS_RS485_TX_PIN 2     // Serial RS485 TX pin
#define MODBUS_RS485_RX_PIN 0     // Serial RS485 RX pin
#define MODBUS_RS485_DE_RE_PIN 16 // Serial RS485 Receiver Enable pin

// I2C bus
#define I2C_SDA_PIN 2 // GPIO 2
#define I2C_SCL_PIN 3 // GPIO 3
#define I2C_BUS_SPEED 400000

// LED
#define LED_STATUS_PIN 15

// Buttons
#define BUTTON_1 2
#define BUTTON_2 3

// Dosing pumps
#define PUMP_1_PIN 6
#define PUMP_2_PIN 5
#define PUMP_3_PIN 9
#define PUMP_4_PIN 10

// Servo
//#define SERVO_1_PIN 10 // Servo 1

#endif