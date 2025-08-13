// Example for analog input (AI0) and output (AO0). Every second it changes the
// voltage value and checks them.

// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

// Before run test need connect AI0 (E2) <=> AO0 (E2) with wire on Red Pitaya

#include <Arduino.h>

#include "SCPI_RP.h"

#if defined(ARDUINO_ARCH_AVR)
#include <SoftwareSerial.h>
SoftwareSerial uart(8, 9);  // Initializes line 8 as RX and line 9 as TX for
                            // SCPI communication via UART
#endif

scpi_rp::SCPIRedPitaya rp;

float value = 0;

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
  rp.aio.reset();
}

void loop() {
  float in_value = 0;
  if ((value * 10) > 18) value = 0;
  if (!rp.aio.state(scpi_rp::AOUT_0, value)) {
    Serial.println("Error set value");
  }
  if (!rp.aio.stateQ(scpi_rp::AOUT_0, &in_value)) {
    Serial.println("Error get value");
  }
  Serial.print("AOUT_0 value = ");
  Serial.println(in_value);
  if (!rp.aio.stateQ(scpi_rp::AIN_0, &in_value)) {
    Serial.println("Error get value");
  }
  Serial.print("AIN_0 value = ");
  Serial.println(in_value);
  delay(1000);
  value += 0.1;
}
