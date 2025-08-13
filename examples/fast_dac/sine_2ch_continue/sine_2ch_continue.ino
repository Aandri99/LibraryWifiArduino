// The example runs 2 synchronized generator channels.

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

  if (!rp.gen.wave(scpi_rp::GEN_CH_2, scpi_rp::TRIANGLE)) {
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

  if (!rp.gen.offset(scpi_rp::GEN_CH_1, 0.2)) {
    Serial.println("Error set offset to ch1");
  }

  if (!rp.gen.offset(scpi_rp::GEN_CH_2, -0.2)) {
    Serial.println("Error set offset to ch1");
  }

  if (!rp.gen.dutyCycle(scpi_rp::GEN_CH_1, 0.3)) {
    Serial.println("Error set duty cycle to ch1");
  }

  if (!rp.gen.dutyCycle(scpi_rp::GEN_CH_2, 0.8)) {
    Serial.println("Error set duty cycle to ch2");
  }

  if (!rp.gen.enableSync(true)) {  // Power on CH1 and CH2
    Serial.println("Error enable ch1 and ch2");
  }

  if (!rp.gen.sync()) {
    Serial.println("Error start generator");
  }
}

void loop() {
  delay(1000);
  scpi_rp::EGENWave wave = scpi_rp::SINE;
  float freq = 0;
  float amp = 0;
  float offset = 0;
  float dc = 0;
  bool enable = false;

  if (!rp.gen.waveQ(scpi_rp::GEN_CH_1, &wave)) {
    Serial.println("Error get waveform from ch1");
  } else {
    Serial.print("Waveform CH1: ");
    Serial.println(wave);
  }

  if (!rp.gen.waveQ(scpi_rp::GEN_CH_2, &wave)) {
    Serial.println("Error get waveform from ch2");
  } else {
    Serial.print("Waveform CH2: ");
    Serial.println(wave);
  }

  if (!rp.gen.freqQ(scpi_rp::GEN_CH_1, &freq)) {
    Serial.println("Error get freq from ch1");
  } else {
    Serial.print("Freq CH1: ");
    Serial.println(freq);
  }

  if (!rp.gen.freqQ(scpi_rp::GEN_CH_2, &freq)) {
    Serial.println("Error get freq from ch2");
  } else {
    Serial.print("Freq CH2: ");
    Serial.println(freq);
  }

  if (!rp.gen.ampQ(scpi_rp::GEN_CH_1, &amp)) {
    Serial.println("Error get amp from ch1");
  } else {
    Serial.print("Amplitude CH1: ");
    Serial.println(amp);
  }

  if (!rp.gen.ampQ(scpi_rp::GEN_CH_2, &amp)) {
    Serial.println("Error get amp from ch2");
  } else {
    Serial.print("Amplitude CH2: ");
    Serial.println(amp);
  }

  if (!rp.gen.offsetQ(scpi_rp::GEN_CH_1, &offset)) {
    Serial.println("Error get offset from ch1");
  } else {
    Serial.print("Offset CH1: ");
    Serial.println(offset);
  }

  if (!rp.gen.offsetQ(scpi_rp::GEN_CH_2, &offset)) {
    Serial.println("Error get offset from ch2");
  } else {
    Serial.print("Offset CH2: ");
    Serial.println(offset);
  }

  if (!rp.gen.dutyCycleQ(scpi_rp::GEN_CH_1, &dc)) {
    Serial.println("Error get duty cycle from ch1");
  } else {
    Serial.print("Duty cycle CH1: ");
    Serial.println(dc);
  }

  if (!rp.gen.dutyCycleQ(scpi_rp::GEN_CH_2, &dc)) {
    Serial.println("Error get duty cycle from ch2");
  } else {
    Serial.print("Duty cycle CH2: ");
    Serial.println(dc);
  }

  if (!rp.gen.enableQ(scpi_rp::GEN_CH_1, &enable)) {
    Serial.println("Error get state from ch1");
  } else {
    Serial.print("Enable CH1: ");
    Serial.println(enable);
  }

  if (!rp.gen.enableQ(scpi_rp::GEN_CH_2, &enable)) {
    Serial.println("Error get state from ch2");
  } else {
    Serial.print("Enable CH2: ");
    Serial.println(enable);
  }
}
