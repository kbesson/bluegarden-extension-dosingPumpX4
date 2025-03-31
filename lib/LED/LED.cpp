#include "LED.h"

void setLedColor(const char *color) {
  statusLed.setBrightness(100);
  // None - LED off
  if (strcmp(color, "none") == 0) {
    statusLed.clear();
  // Red
  } else if (strcmp(color, "red") == 0) {
    statusLed.setPixelColor(0, statusLed.Color(255, 0, 0)); // RGB value
  // Green
  } else if (strcmp(color, "green") == 0) {
    statusLed.setPixelColor(0, statusLed.Color(0, 255, 0)); // RGB value
  // Blue
  } else if (strcmp(color, "blue") == 0) {
    statusLed.setPixelColor(0, statusLed.Color(0, 0, 255)); // RGB value
  // White
  } else if (strcmp(color, "white") == 0) {
    statusLed.setPixelColor(0, statusLed.Color(255, 255, 255)); // RGB value
  // Yellow
  } else if (strcmp(color, "yellow") == 0) {
    statusLed.setPixelColor(0, statusLed.Color(255, 0, 0)); // RGB value
  // Purple
  } else if (strcmp(color, "purple") == 0) {
    statusLed.setPixelColor(0, statusLed.Color(191, 64, 191)); // RGB value
  // Cyan
  } else if (strcmp(color, "cyan") == 0) {
    statusLed.setPixelColor(0, statusLed.Color(43, 250, 250)); // RGB value
  }

  statusLed.show(); // Initialize all pixels to 'off'
  strcpy(previousColor, currentColor); // Update previous color
  strcpy(currentColor, color); // Update current color
}

void setLedPreviousColor() {
  setLedColor(previousColor);
};

const char* getLedPreviousColor() {
  return previousColor;
};

const char* getLedColor() {
  return currentColor;
};