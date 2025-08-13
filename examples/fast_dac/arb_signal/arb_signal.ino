// Example of creating an arbitrary waveform

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
  rp.gen.reset();
  rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::ARBITRARY);
  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);

  for (int i = 0; i < 16384; i++) {
    float t = (2.0 * 3.141549) / 16384.0 * i;
    float z = sin(t) + ((1.0 / 3.0) * sin(t * 3));
    rp.gen.arbWave(scpi_rp::GEN_CH_1, z, i == (16384 - 1));
  }

  // Check uploaded ARB signal
  bool last = false;
  float sample = 0;
  int idx = 0;
  while (!last) {
    rp.gen.arbWaveQ(scpi_rp::GEN_CH_1, &sample, &last);
    Serial.print(idx++);
    Serial.print(" - ");
    Serial.print(sample, 6);
    Serial.println("");
  }

  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
  rp.gen.sync(scpi_rp::GEN_CH_1);
}

void loop() { delay(1000); }
