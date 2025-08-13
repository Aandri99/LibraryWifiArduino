// The example first turns on the even LED indicators. Reads the state, then
// turns on the odd indicators and reads the state.

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
uint8_t led_mode = 0xAA;

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
  rp.dio.reset();
}

void loop() {
  uint8_t led_state = 0;
  for (uint8_t i = scpi_rp::LED_0; i <= scpi_rp::LED_7; i++) {
    rp.dio.state((scpi_rp::EDIOPin)(i), (1 << i) & led_mode);
  }
  for (uint8_t i = scpi_rp::LED_0; i <= scpi_rp::LED_7; i++) {
    bool state;
    rp.dio.stateQ((scpi_rp::EDIOPin)(i), &state);
    led_state |= (uint8_t)state << i;
  }
  Serial.print("Led state = 0x");
  Serial.println(led_state, HEX);
  delay(1000);
  led_mode ^= 0xFF;
}
