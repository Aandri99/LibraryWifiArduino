// Example for managing system indicators.

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

bool enable = false;

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
}

void loop() {
  bool state = false;
  if (!rp.system_led.mmc(enable)) {
    Serial.println("Error set MMC state");
  }

  if (!rp.system_led.mmcQ(&state)) {
    Serial.println("Error get MMC state");
  }

  Serial.print("MMC state = ");
  Serial.println(state);

  if (!rp.system_led.heartBeat(enable)) {
    Serial.println("Error set HB state");
  }

  if (!rp.system_led.heartBeatQ(&state)) {
    Serial.println("Error get HB state");
  }

  Serial.print("HB state = ");
  Serial.println(state);

  if (!rp.system_led.ethernet(enable)) {
    Serial.println("Error set ETH state");
  }

  if (!rp.system_led.ethernetQ(&state)) {
    Serial.println("Error get ETH state");
  }

  Serial.print("ETH state = ");
  Serial.println(state);
  delay(3000);
  enable = !enable;
}
