// The example shows how you can switch the signal frequency without resetting
// the settings and stopping the generator.

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

float freq = 10000;

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

  if (!rp.gen.reset()) {
    Serial.println("Error reset");
  }

  if (!rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SQUARE)) {
    Serial.println("Error set waveform to ch1");
  }

  if (!rp.gen.freq(scpi_rp::GEN_CH_1, freq)) {
    Serial.println("Error set freq to ch1");
  }

  if (!rp.gen.amp(scpi_rp::GEN_CH_1, 0.6)) {
    Serial.println("Error set amplitude to ch1");
  }

  if (!rp.gen.enable(scpi_rp::GEN_CH_1, true)) {  // Power on CH1
    Serial.println("Error enable ch1");
  }

  if (!rp.gen.sync()) {
    Serial.println("Error start generator");
  }
}

void loop() {
  delay(100);

  if (!rp.gen.freqDirect(scpi_rp::GEN_CH_1, freq)) {
    Serial.println("Error set freq to ch1");
  }

  if (!rp.gen.sync()) {
    Serial.println("Error sync generator");
  }

  if (!rp.gen.freqQ(scpi_rp::GEN_CH_1, &freq)) {
    Serial.println("Error get freq from ch1");
  } else {
    Serial.print("Freq CH1: ");
    Serial.println(freq);
  }
  freq += 1000;
  if (freq > 100000) {
    freq = 10000;
  }
}
