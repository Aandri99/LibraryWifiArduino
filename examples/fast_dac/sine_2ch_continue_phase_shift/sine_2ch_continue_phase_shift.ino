// In the example, 2 synchronized generator channels operate with a phase shift
// of 90 degrees.

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

  if (!rp.gen.reset()) {
    Serial.println("Error reset");
  }

  if (!rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SINE)) {
    Serial.println("Error set waveform to ch1");
  }

  if (!rp.gen.wave(scpi_rp::GEN_CH_2, scpi_rp::SINE)) {
    Serial.println("Error set waveform to ch2");
  }

  if (!rp.gen.freq(scpi_rp::GEN_CH_1, 10000)) {
    Serial.println("Error set freq to ch1");
  }

  if (!rp.gen.freq(scpi_rp::GEN_CH_2, 10000)) {
    Serial.println("Error set freq to ch1");
  }

  if (!rp.gen.amp(scpi_rp::GEN_CH_1, 0.6)) {
    Serial.println("Error set amplitude to ch1");
  }

  if (!rp.gen.amp(scpi_rp::GEN_CH_2, 0.6)) {
    Serial.println("Error set amplitude to ch1");
  }

  if (!rp.gen.phase(scpi_rp::GEN_CH_2, 90)) {
    Serial.println("Error set phase shift to ch2");
  }

  float phase = 0;
  if (!rp.gen.phaseQ(scpi_rp::GEN_CH_2, &phase)) {
    Serial.println("Error get phase shift from ch2");
  } else {
    Serial.print("Phase: ");
    Serial.println(phase);
  }

  if (!rp.gen.enableSync(true)) {  // Power on CH1 and CH2
    Serial.println("Error enable ch1 and ch2");
  }

  if (!rp.gen.sync()) {
    Serial.println("Error start generator");
  }
}

void loop() { delay(1000); }
