// Example of capturing data from an internal generator using the generator
// trigger. Before starting, you need to connect Fast OUT 1 <=> Fast IN1

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

  // Set burst mode
  rp.gen.genMode(scpi_rp::GEN_CH_1, scpi_rp::GEN_BURST);
  rp.gen.burstInitValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstLastValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstNCycles(scpi_rp::GEN_CH_1, 1);
  rp.gen.burstNRepetitions(scpi_rp::GEN_CH_1, 1);

  if (!rp.acq.control.reset()) {
    Serial.println("Error reset acq");
  }

  // Enables averaging of values ​​when
  // decimating data. Enabled by default.
  if (!rp.acq.settings.average(true)) {
    Serial.println("Error set average");
  }

  bool avarage = false;
  if (!rp.acq.settings.averageQ(&avarage)) {
    Serial.println("Error get average");
  } else {
    Serial.print("Average = ");
    Serial.println(avarage);
  }
  scpi_rp::EACQGain gain = scpi_rp::ACQ_GAIN_LV;
  if (!rp.acq.settings.gain(scpi_rp::ACQ_CH_1, gain)) {
    Serial.println("Error set gain");
  }

  if (!rp.acq.settings.gainQ(scpi_rp::ACQ_CH_1, &gain)) {
    Serial.println("Error get gain");
  } else {
    Serial.print("Gain = ");
    Serial.println(gain);
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

  float trigger_level = 0.01;
  if (!rp.acq.trigger.level(trigger_level)) {
    Serial.println("Error set trigger level");
  }

  if (!rp.acq.trigger.levelQ(&trigger_level)) {
    Serial.println("Error get trigger level");
  } else {
    Serial.print("Trigger level = ");
    Serial.println(trigger_level);
  }

  int trigger_delay = 123;
  if (!rp.acq.trigger.delay(trigger_delay)) {
    Serial.println("Error set trigger delay");
  }

  if (!rp.acq.trigger.delayQ(&trigger_delay)) {
    Serial.println("Error get trigger delay");
  } else {
    Serial.print("Trigger delay = ");
    Serial.println(trigger_delay);
  }

  if (!rp.acq.control.start()) {
    Serial.println("Error start ADC");
  }

  delay(100);

  if (!rp.acq.trigger.trigger(scpi_rp::ACQ_AWG_PE)) {
    Serial.println("Error set trigger");
  }

  rp.gen.enable(scpi_rp::GEN_CH_1, true);
  rp.gen.sync(scpi_rp::GEN_CH_1);

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
    rp.acq.data.dataFromTriggerQ(scpi_rp::ACQ_CH_1, scpi_rp::ACQ_PRE_POST_TRIG,
                                 200, &sample, &last);
    Serial.print(idx++);
    Serial.print(" - ");
    Serial.print(sample, 6);
    Serial.println("");
  }
}

void loop() { delay(1000); }
