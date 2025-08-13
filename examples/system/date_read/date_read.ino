// Example of a test sketch for reading date and time from Red Pitaya board via
// SCPI server.

// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

#include <Arduino.h>

#include "SCPI_RP.h"

#if defined(ARDUINO_ARCH_AVR)
#include <SoftwareSerial.h>
SoftwareSerial uart(8, 9);  // Initializes line 8 as RX and line 9 as TX for
                            // SCPI communication via UART
#endif

scpi_rp::SCPIRedPitaya rp;

void setup() {
  // Initializing console output
  Serial.begin(115200);

#if defined(ARDUINO_ARCH_AVR)
  uart.begin(RED_PITAYA_UART_RATE);
  rp.initStream(&uart);
#elif defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_SAMD) || \
    defined(ARDUINO_ARCH_SAM)
  Serial1.begin(RED_PITAYA_UART_RATE);
  rp.initStream(&Serial1);
#endif

  uint16_t year;
  uint8_t month, day;
  if (!rp.system.dateQ(&year, &month, &day)) {  // Request date from RP
    Serial.print("Error getting date from RP");
  } else {
    Serial.print("Year: ");
    Serial.print(year);
    Serial.print(" Month: ");
    Serial.print(month);
    Serial.print(" Day: ");
    Serial.println(day);
  }

  uint8_t hour, min, sec;
  if (!rp.system.timeQ(&hour, &min, &sec)) {  // Request time from RP
    Serial.print("Error getting time from RP");
  } else {
    Serial.print("Hour: ");
    Serial.print(hour);
    Serial.print(" Minute: ");
    Serial.print(min);
    Serial.print(" Second: ");
    Serial.println(sec);
  }
}

void loop() {}
