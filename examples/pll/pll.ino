// Example for Phase locked loop
// Worked only on SIGNALlab 250-12

// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

#include <Arduino.h>

#include "SCPI_RP.h"

#if defined(ARDUINO_ARCH_AVR)
#include <SoftwareSerial.h>
SoftwareSerial uart(8, 9);  // Initializes line 8 as RX and line 9 as TX
                            // for SCPI communication via UART
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

  bool state = false;
  if (!rp.pll.enable(true)) {
    Serial.println("Error set value");
  }
  if (!rp.pll.enableQ(&state)) {
    Serial.println("Error get value");
  }

  Serial.print("PLL mode = ");
  Serial.println(state);
}

void loop() {
  bool state = false;
  if (!rp.pll.stateQ(&state)) {
    Serial.println("Error get state");
  }

  Serial.print("PLL state = ");
  Serial.println(state);
  delay(1000);
}
