// Example of using commands for Daisy mode. The example does not carry any
// functionality. It just shows the possibility of using commands. To use this
// mode, you need several Red Pitaya connected in the X - channel system or
// Click shields.

// Information about the X-channel system can be found here:
// https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/125-14_MULTI/top.html#red-pitaya-x-channel-system

// Information about Click Shield:
// https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/ext_modules/click_shield.html

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

  bool state;
  scpi_rp::EDAISYMode mode = scpi_rp::DAISY_ADC;

  if (!rp.daisy.syncTrigger(true)) {
    Serial.println("Error set value");
  }
  if (!rp.daisy.syncTriggerQ(&state)) {
    Serial.println("Error get value");
  }

  Serial.print("Daisy sync trigger = ");
  Serial.println(state);

  if (!rp.daisy.syncClock(true)) {
    Serial.println("Error set value");
  }
  if (!rp.daisy.syncClockQ(&state)) {
    Serial.println("Error get value");
  }

  Serial.print("Daisy sync clock = ");
  Serial.println(state);

  if (!rp.daisy.trigOEnable(true)) {
    Serial.println("Error set value");
  }
  if (!rp.daisy.trigOEnableQ(&state)) {
    Serial.println("Error get value");
  }

  Serial.print("Daisy trigger O enable = ");
  Serial.println(state);

  if (!rp.daisy.trigOSource(scpi_rp::DAISY_ADC)) {
    Serial.println("Error set value");
  }
  if (!rp.daisy.trigOSourceQ(&mode)) {
    Serial.println("Error get value");
  }

  Serial.print("Daisy trigger mode = ");
  Serial.println(mode);
}

void loop() { delay(1000); }
