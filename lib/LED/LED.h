#ifndef LED_H
#define LED_H

// Includes libraries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Include external files
#include "../../inc/Globals.h"
#include "../../inc/GPIOs.h"

extern Adafruit_NeoPixel statusLed;

extern char previousColor[10];
extern char currentColor[10];

void setLedColor(const char *color);
void setLedPreviousColor();
const char* getLedPreviousColor();
const char* getLedColor();

#endif