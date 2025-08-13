// An example of data capture on a 4-channel board in split trigger mode.

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

  bool split = true;
  if (!rp.acq.control.splitTriggerMode(split)) {
    Serial.println("Error set split trigger");
  }

  if (!rp.acq.control.resetCh(scpi_rp::ACQ_CH_1)) {
    Serial.println("Error reset acq ch1");
  }

  if (!rp.acq.control.resetCh(scpi_rp::ACQ_CH_2)) {
    Serial.println("Error reset acq ch2");
  }

  if (!rp.acq.control.resetCh(scpi_rp::ACQ_CH_3)) {
    Serial.println("Error reset acq ch3");
  }

  if (!rp.acq.control.resetCh(scpi_rp::ACQ_CH_4)) {
    Serial.println("Error reset acq ch4");
  }

  scpi_rp::EACQDecimation dec = scpi_rp::ACQ_DEC_1024;

  if (!rp.acq.settings.decimationCh(scpi_rp::ACQ_CH_1, dec)) {
    Serial.println("Error set decimation ch1");
  }

  if (!rp.acq.settings.decimationChQ(scpi_rp::ACQ_CH_1, &dec)) {
    Serial.println("Error get decimation ch1");
  } else {
    Serial.print("Decimation CH 1 = ");
    Serial.println(dec);
  }

  uint32_t decimation = 1024 * 1.5;
  if (!rp.acq.settings.decimationFactorCh(scpi_rp::ACQ_CH_2, decimation)) {
    Serial.println("Error set decimation ch2");
  }

  if (!rp.acq.settings.decimationFactorChQ(scpi_rp::ACQ_CH_2, &decimation)) {
    Serial.println("Error get decimation ch2");
  } else {
    Serial.print("Decimation CH 2 = ");
    Serial.println(decimation);
  }

  decimation = 1024 * 2;
  if (!rp.acq.settings.decimationFactorCh(scpi_rp::ACQ_CH_3, decimation)) {
    Serial.println("Error set decimation ch3");
  }

  if (!rp.acq.settings.decimationFactorChQ(scpi_rp::ACQ_CH_3, &decimation)) {
    Serial.println("Error get decimation ch3");
  } else {
    Serial.print("Decimation CH 3 = ");
    Serial.println(decimation);
  }

  decimation = 1024 * 2.5;
  if (!rp.acq.settings.decimationFactorCh(scpi_rp::ACQ_CH_4, decimation)) {
    Serial.println("Error set decimation ch4");
  }

  if (!rp.acq.settings.decimationFactorChQ(scpi_rp::ACQ_CH_4, &decimation)) {
    Serial.println("Error get decimation ch4");
  } else {
    Serial.print("Decimation CH 4 = ");
    Serial.println(decimation);
  }

  if (!rp.acq.control.startCh(scpi_rp::ACQ_CH_1)) {
    Serial.println("Error start ch1 ADC");
  }

  if (!rp.acq.control.startCh(scpi_rp::ACQ_CH_2)) {
    Serial.println("Error start ch2 ADC");
  }

  if (!rp.acq.control.startCh(scpi_rp::ACQ_CH_3)) {
    Serial.println("Error start ch3 ADC");
  }

  if (!rp.acq.control.startCh(scpi_rp::ACQ_CH_4)) {
    Serial.println("Error start ch4 ADC");
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_1, scpi_rp::ACQ_NOW)) {
    Serial.println("Error set trigger ch1");
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_2, scpi_rp::ACQ_NOW)) {
    Serial.println("Error set trigger ch2");
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_3, scpi_rp::ACQ_NOW)) {
    Serial.println("Error set trigger ch3");
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_4, scpi_rp::ACQ_NOW)) {
    Serial.println("Error set trigger ch4");
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.stateChQ(scpi_rp::ACQ_CH_1, &state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.stateChQ(scpi_rp::ACQ_CH_2, &state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.stateChQ(scpi_rp::ACQ_CH_3, &state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.stateChQ(scpi_rp::ACQ_CH_4, &state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.fillChQ(scpi_rp::ACQ_CH_1, &state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.fillChQ(scpi_rp::ACQ_CH_2, &state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.fillChQ(scpi_rp::ACQ_CH_3, &state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.fillChQ(scpi_rp::ACQ_CH_4, &state);
    if (state) break;
  }

  if (!rp.acq.control.stopCh(scpi_rp::ACQ_CH_1)) {
    Serial.println("Error stop ch1 ADC");
  }

  if (!rp.acq.control.stopCh(scpi_rp::ACQ_CH_2)) {
    Serial.println("Error stop ch2 ADC");
  }

  if (!rp.acq.control.stopCh(scpi_rp::ACQ_CH_3)) {
    Serial.println("Error stop ch3 ADC");
  }

  if (!rp.acq.control.stopCh(scpi_rp::ACQ_CH_4)) {
    Serial.println("Error stop ch4 ADC");
  }

  // Read data
  uint32_t wp[4] = {0, 0, 0, 0};
  uint32_t tp[4] = {0, 0, 0, 0};
  for (int i = 1; i <= 4; i++) {
    if (!rp.acq.data.writePositionChQ((scpi_rp::EACQChannel)i, &wp[i])) {
      Serial.println("Error get write pointer");
    } else {
      Serial.print("Write pointer CH");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(wp[i]);
    }

    if (!rp.acq.data.triggerPositionChQ((scpi_rp::EACQChannel)i, &tp[i])) {
      Serial.println("Error get trigger pointer");
    } else {
      Serial.print("Trigger pointer CH");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(tp[i]);
    }

    bool last = false;
    float sample = 0;
    int idx = 0;
    Serial.print("CH ");
    Serial.println(i);
    while (!last) {
      rp.acq.data.dataStartSizeQ(scpi_rp::ACQ_CH_1, tp[i], 20, &sample, &last);
      Serial.print(idx++);
      Serial.print(" - ");
      Serial.print(sample, 6);
      Serial.println("");
    }
  }
}

void loop() { delay(1000); }
