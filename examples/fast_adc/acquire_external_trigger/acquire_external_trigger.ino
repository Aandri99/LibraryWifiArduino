// Example of data collection on fast ADC IN1 using external trigger
// Before starting, you need to connect Fast OUT 1 <=> Fast IN1

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

  rp.gen.reset();
  rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SINE);
  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);
  rp.gen.enable(scpi_rp::GEN_CH_1, true);
  rp.gen.sync(scpi_rp::GEN_CH_1);

  if (!rp.acq.control.reset()) {
    Serial.println("Error reset acq");
  }

  uint32_t decimation = 128;
  if (!rp.acq.settings.decimationFactor(decimation)) {
    Serial.println("Error set decimation");
  }

  if (!rp.acq.settings.decimationFactorQ(&decimation)) {
    Serial.println("Error get decimation");
  } else {
    Serial.print("Decimation = ");
    Serial.println(decimation);
  }

  if (!rp.acq.control.start()) {
    Serial.println("Error start ADC");
  }

  if (!rp.acq.trigger.trigger(scpi_rp::ACQ_EXT_PE)) {
    Serial.println("Error set external trigger");
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.stateQ(&state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.fillQ(&state);
    if (state) break;
  }

  if (!rp.acq.control.stop()) {
    Serial.println("Error stop ADC");
  }
  // Read data

  uint32_t tp = 0;
  if (!rp.acq.data.triggerPositionQ(&tp)) {
    Serial.println("Error get trigger pointer");
  } else {
    Serial.print("Trigger pointer = ");
    Serial.println(tp);
  }

  bool last = false;
  float sample = 0;
  int idx = 0;
  while (!last) {
    rp.acq.data.dataStartSizeQ(scpi_rp::ACQ_CH_1, tp, 200, &sample, &last);
    Serial.print(idx++);
    Serial.print(" - ");
    Serial.print(sample, 6);
    Serial.println("");
  }
}

void loop() { delay(1000); }
