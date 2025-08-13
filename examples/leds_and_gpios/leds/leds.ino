// The example switches in order indicators from 1 to 8 with an interval of 1
// second.

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
uint8_t led_state = 1;

void setup() {
#if defined(ARDUINO_ARCH_AVR)
  uart.begin(RED_PITAYA_UART_RATE);
  rp.initStream(&uart);
#elif defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_SAMD) || \
    defined(ARDUINO_ARCH_SAM)
  Serial1.begin(RED_PITAYA_UART_RATE);
  rp.initStream(&Serial1);
#endif
  rp.dio.reset();
}

void loop() {
  rp.dio.state((scpi_rp::EDIOPin)(led_state), 1);
  delay(1000);
  rp.dio.state((scpi_rp::EDIOPin)(led_state), 0);
  led_state++;
  if (led_state == 8) led_state = 0;
}
