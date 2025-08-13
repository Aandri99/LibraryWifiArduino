// The example generates a signal when a button is pressed.
// The button should close contacts DIO0_N and DIO0_P

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

  rp.dio.reset();
  rp.dio.dir(scpi_rp::DIO_0_P, scpi_rp::IN);
  rp.dio.dir(scpi_rp::DIO_0_N, scpi_rp::OUT);
  rp.dio.state(scpi_rp::DIO_0_N, true);

  rp.gen.reset();

  // Set internal trigger
  rp.gen.trigSource(scpi_rp::GEN_CH_1, scpi_rp::GEN_EXT_NE);

  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);

  // Set burst mode
  rp.gen.genMode(scpi_rp::GEN_CH_1, scpi_rp::GEN_BURST);
  rp.gen.burstInitValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstLastValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstNCycles(scpi_rp::GEN_CH_1, 3);
  rp.gen.burstNRepetitions(scpi_rp::GEN_CH_1, 1);

  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
}

void loop() { delay(100); }
