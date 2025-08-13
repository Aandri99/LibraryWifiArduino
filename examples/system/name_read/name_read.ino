// Example of a test sketch for Read Red Pitaya board name and board family ID.

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

#define BUFF_SIZE 30

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

  char name[BUFF_SIZE];
  if (!rp.system.boardNameQ(name, BUFF_SIZE)) {  // Request name from RP
    Serial.println("Error getting board name from RP");
  } else {
    Serial.print("Board name: ");
    Serial.println(name);
  }

  uint32_t board_id;
  if (!rp.system.boardIDQ(&board_id)) {  // Request id from RP
    Serial.println("Error getting board ID from RP");
  } else {
    Serial.print("ID: ");
    Serial.println(board_id);
  }
}

void loop() {}
