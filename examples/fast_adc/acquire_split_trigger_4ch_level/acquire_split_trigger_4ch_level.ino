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
  rp.acq.control.splitTriggerMode(split);
  float level = 0;
  int delay = 0;
  for (int i = 1; i <= 4; i++) {
    rp.acq.control.resetCh((scpi_rp::EACQChannel)i);
    rp.acq.settings.decimationFactorCh((scpi_rp::EACQChannel)i, 1024);
    rp.acq.trigger.levelCh((scpi_rp::EACQChannel)i, 0.1);
    rp.acq.trigger.delayCh((scpi_rp::EACQChannel)i, 1024);
    rp.acq.trigger.levelChQ((scpi_rp::EACQChannel)i, &level);
    rp.acq.trigger.delayChQ((scpi_rp::EACQChannel)i, &delay);
    Serial.print(level);
    Serial.print(" - ");
    Serial.println(delay);
  }

  for (int i = 1; i <= 4; i++) {
    rp.acq.control.startCh((scpi_rp::EACQChannel)i);
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_1, scpi_rp::ACQ_CH1_PE)) {
    Serial.println("Error set trigger ch1");
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_2, scpi_rp::ACQ_CH2_PE)) {
    Serial.println("Error set trigger ch2");
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_3, scpi_rp::ACQ_CH3_PE)) {
    Serial.println("Error set trigger ch3");
  }

  if (!rp.acq.trigger.triggerCh(scpi_rp::ACQ_CH_4, scpi_rp::ACQ_CH4_PE)) {
    Serial.println("Error set trigger ch4");
  }

  for (int i = 1; i <= 4; i++) {
    while (1) {
      bool state = false;
      rp.acq.trigger.stateChQ((scpi_rp::EACQChannel)i, &state);
      if (state) break;
    }
  }

  for (int i = 1; i <= 4; i++) {
    while (1) {
      bool state = false;
      rp.acq.trigger.fillChQ((scpi_rp::EACQChannel)i, &state);
      if (state) break;
    }
  }

  for (int i = 1; i <= 4; i++) {
    rp.acq.control.stopCh((scpi_rp::EACQChannel)i);
  }

  // Read data
  uint32_t tp[4] = {0, 0, 0, 0};
  for (int i = 1; i <= 4; i++) {
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
