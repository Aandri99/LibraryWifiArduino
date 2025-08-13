// Example of data capture at the Fast ADC IN1 via DMA
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

  uint32_t startAddressReserved = 0;
  uint32_t sizeReserved = 0;

  if (!rp.acq.dma.settings.memoryStartAddressQ(&startAddressReserved)) {
    Serial.println("Error get decimation");
  } else {
    Serial.print("Start address = ");
    Serial.println(startAddressReserved);
  }

  if (!rp.acq.dma.settings.memorySizeQ(&sizeReserved)) {
    Serial.println("Error get decimation");
  } else {
    Serial.print("Size = ");
    Serial.println(sizeReserved);
  }

  uint32_t decimation = 123;
  if (!rp.acq.dma.settings.decimation(decimation)) {
    Serial.println("Error set decimation");
  }

  if (!rp.acq.dma.settings.decimationQ(&decimation)) {
    Serial.println("Error get decimation");
  } else {
    Serial.print("Decimation = ");
    Serial.println(decimation);
  }

  uint32_t delay = 1024;

  if (!rp.acq.dma.settings.delayCh(scpi_rp::ACQ_CH_1, delay)) {
    Serial.println("Error set delay");
  }

  if (!rp.acq.dma.settings.delayChQ(scpi_rp::ACQ_CH_1, &delay)) {
    Serial.println("Error get delay");
  } else {
    Serial.print("Delay = ");
    Serial.println(delay);
  }

  scpi_rp::EACQDataType dt = scpi_rp::ACQ_DT_RAW;
  if (!rp.acq.dma.settings.units(dt)) {
    Serial.println("Error set data type");
  }

  if (!rp.acq.dma.settings.unitsQ(&dt)) {
    Serial.println("Error get data type");
  } else {
    Serial.print("Type = ");
    Serial.println(dt);
  }

  // delay (samples) * 2 = bytes
  if (!rp.acq.dma.settings.setAddress(scpi_rp::ACQ_CH_1, startAddressReserved,
                                      delay * 2)) {
    Serial.println("Error set address");
  }

  if (!rp.acq.dma.settings.enable(scpi_rp::ACQ_CH_1, true)) {
    Serial.println("Error enable");
  }

  if (!rp.acq.control.start()) {
    Serial.println("Error start ADC");
  }

  if (!rp.acq.trigger.trigger(scpi_rp::ACQ_CH1_PE)) {
    Serial.println("Error set trigger");
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.stateQ(&state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.dma.data.fillChQ(scpi_rp::ACQ_CH_1, &state);
    if (state) break;
  }

  if (!rp.acq.control.stop()) {
    Serial.println("Error stop ADC");
  }
  // Read data

  uint32_t wp = 0;
  if (!rp.acq.dma.data.writePositionChQ(scpi_rp::ACQ_CH_1, &wp)) {
    Serial.println("Error get write pointer");
  } else {
    Serial.print("Write pointer = ");
    Serial.println(wp);
  }

  uint32_t tp = 0;
  if (!rp.acq.dma.data.triggerPositionChQ(scpi_rp::ACQ_CH_1, &tp)) {
    Serial.println("Error get trigger pointer");
  } else {
    Serial.print("Trigger pointer = ");
    Serial.println(tp);
  }

  bool last = false;
  float sample = 0;
  int idx = 0;
  while (!last) {
    rp.acq.dma.data.dataStartSizeQ(scpi_rp::ACQ_CH_1, tp, delay, &sample,
                                   &last);
    Serial.print(idx++);
    Serial.print(" - ");
    Serial.print(sample, 6);
    Serial.println("");
  }
}

void loop() { delay(1000); }
