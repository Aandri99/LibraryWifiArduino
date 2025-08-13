// The example returns the entire buffer in RAW format.

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
  rp.system.log(scpi_rp::CONSOLE);
  if (!rp.acq.control.reset()) {
    Serial.println("Error reset acq");
  }

  scpi_rp::EACQDecimation decimation = scpi_rp::ACQ_DEC_64;
  if (!rp.acq.settings.decimation(decimation)) {
    Serial.println("Error set decimation");
  }

  if (!rp.acq.settings.decimationQ(&decimation)) {
    Serial.println("Error get decimation");
  } else {
    Serial.print("Decimation = ");
    Serial.println(decimation);
  }

  scpi_rp::EACQDataType dt = scpi_rp::ACQ_DT_RAW;
  if (!rp.acq.settings.units(dt)) {
    Serial.println("Error set data type");
  }

  if (!rp.acq.settings.unitsQ(&dt)) {
    Serial.println("Error get data type");
  } else {
    Serial.print("Type = ");
    Serial.println(dt);
  }
  uint32_t b_size = 0;
  if (!rp.acq.settings.bufferSizeQ(&b_size)) {
    Serial.println("Error get buffer size");
  } else {
    Serial.print("Buffer size = ");
    Serial.println(b_size);
  }

  if (!rp.acq.control.start()) {
    Serial.println("Error start ADC");
  }

  if (!rp.acq.trigger.trigger(scpi_rp::ACQ_NOW)) {
    Serial.println("Error set trigger");
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

  bool last = false;
  float sample = 0;
  int idx = 0;
  while (!last) {
    rp.acq.data.dataFullBufferQ(scpi_rp::ACQ_CH_1, &sample, &last);
    Serial.print(idx++);
    Serial.print(" - ");
    Serial.print(sample, 6);
    Serial.println("");
  }
}

void loop() { delay(1000); }
