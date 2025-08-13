// The example sets DIO2_P as an output and DIO2_N as an input. Every second it
// changes the state of the P output and reads the N input.

// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

// Before run test need connect DIO2_P <=> DIO2_N with wire on Red Pitaya

#include <Arduino.h>

#include "SCPI_RP.h"

#if defined(ARDUINO_ARCH_AVR)
#include <SoftwareSerial.h>
SoftwareSerial uart(8, 9);  // Initializes line 8 as RX and line 9 as TX for
                            // SCPI communication via UART
#endif

scpi_rp::SCPIRedPitaya rp;
bool set_state = 0;
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
  rp.dio.dir(scpi_rp::DIO_2_P, scpi_rp::OUT);
  rp.dio.dir(scpi_rp::DIO_2_N, scpi_rp::IN);
  scpi_rp::EDIODir dir;
  if (!rp.dio.dirQ(scpi_rp::DIO_2_P, &dir)) {
    Serial.println("Error get dir");
  } else {
    Serial.print("DIO_2_P dir = ");
    Serial.println(dir);
  }
  if (!rp.dio.dirQ(scpi_rp::DIO_2_N, &dir)) {
    Serial.println("Error get dir");
  } else {
    Serial.print("DIO_2_N dir = ");
    Serial.println(dir);
  }
}

void loop() {
  bool state = 0;
  if (!rp.dio.state(scpi_rp::DIO_2_P, set_state)) {
    Serial.println("Error set state");
  }
  if (!rp.dio.stateQ(scpi_rp::DIO_2_N, &state)) {
    Serial.println("Error get state");
  }
  Serial.print("DIO N/2 state = 0x");
  Serial.println(state);
  delay(1000);
  set_state = !set_state;
}
