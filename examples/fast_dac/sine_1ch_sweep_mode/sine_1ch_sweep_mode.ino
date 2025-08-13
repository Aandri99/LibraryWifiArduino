// The example starts the generator on channel 1 with a sine wave signal in
// sweep mode from 1kHz to 100kHz

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
  Serial.begin(115200);

#if defined(ARDUINO_ARCH_AVR)
  uart.begin(RED_PITAYA_UART_RATE);
  rp.initStream(&uart);
#elif defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_SAMD) || \
    defined(ARDUINO_ARCH_SAM)
  Serial1.begin(RED_PITAYA_UART_RATE);
  rp.initStream(&Serial1);
#endif

  scpi_rp::EGENSweepMode mode = scpi_rp::GEN_SWEEP_LINEAR;
  scpi_rp::EGENSweepDir dir = scpi_rp::GEN_SWEEP_NORMAL;
  bool state = false;
  float start = 0;
  float end = 0;
  uint64_t time = 0;

  rp.gen.reset();
  rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SINE);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);

  rp.gen.sweepDefault();
  rp.gen.sweepDirection(scpi_rp::GEN_CH_1, scpi_rp::GEN_SWEEP_UP_DOWN);
  rp.gen.sweepFreqStart(scpi_rp::GEN_CH_1, 1000);
  rp.gen.sweepFreqEnd(scpi_rp::GEN_CH_1, 100000);
  rp.gen.sweepMode(scpi_rp::GEN_CH_1, scpi_rp::GEN_SWEEP_LOG);
  rp.gen.sweepTime(scpi_rp::GEN_CH_1, 10000000);  // 10 sec

  if (rp.gen.sweepDirectionQ(scpi_rp::GEN_CH_1, &dir)) {
    Serial.print("Direction = ");
    Serial.println(dir);
  } else {
    Serial.println("Error get direction");
  }

  if (rp.gen.sweepModeQ(scpi_rp::GEN_CH_1, &mode)) {
    Serial.print("Mode = ");
    Serial.println(mode);
  } else {
    Serial.println("Error get mode");
  }

  if (rp.gen.sweepFreqStartQ(scpi_rp::GEN_CH_1, &start)) {
    Serial.print("Start freq = ");
    Serial.println(start);
  } else {
    Serial.println("Error get start freq");
  }

  if (rp.gen.sweepFreqEndQ(scpi_rp::GEN_CH_1, &end)) {
    Serial.print("End freq = ");
    Serial.println(end);
  } else {
    Serial.println("Error get end freq");
  }

  if (rp.gen.sweepTimeQ(scpi_rp::GEN_CH_1, &time)) {
    Serial.print("Time = ");
    Serial.println((double)time);
  } else {
    Serial.println("Error get time");
  }

  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
  rp.gen.sync(scpi_rp::GEN_CH_1);

  rp.gen.sweepReset();
  rp.gen.sweepState(scpi_rp::GEN_CH_1, true);

  if (rp.gen.sweepStateQ(scpi_rp::GEN_CH_1, &state)) {
    Serial.print("State = ");
    Serial.println(state);
  } else {
    Serial.println("Error get state");
  }
}

void loop() { delay(1000); }
