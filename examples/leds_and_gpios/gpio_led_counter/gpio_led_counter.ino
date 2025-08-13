// The example counts the number of button presses connected to DIO0_N to GND
// and changes the state of the indicators.

// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

// Before running the test, you need to connect the Button to the DIO0_N and
// DIO0_P pins on the Red Pitaya

#include <Arduino.h>

#include "SCPI_RP.h"

#if defined(ARDUINO_ARCH_AVR)
#include <SoftwareSerial.h>
SoftwareSerial uart(8, 9);  // Initializes line 8 as RX and line 9 as TX for
                            // SCPI communication via UART
#endif

scpi_rp::SCPIRedPitaya rp;

bool last_state = 0;
uint8_t led_state = 0;
uint8_t led_state_new = 0;

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
  rp.dio.dir(scpi_rp::DIO_0_N, scpi_rp::IN);
  for (uint8_t i = scpi_rp::LED_0; i <= scpi_rp::LED_7; i++) {
    rp.dio.state((scpi_rp::EDIOPin)(i), false);
  }
}

void loop() {
  bool state = 0;
  if (!rp.dio.stateQ(scpi_rp::DIO_0_N, &state)) {
    Serial.println("Error get state");
  }
  if (state != last_state && state) {
    led_state_new++;
  }
  last_state = state;
  if (led_state_new != led_state) {
    for (uint8_t i = scpi_rp::LED_0; i <= scpi_rp::LED_7; i++) {
      rp.dio.state((scpi_rp::EDIOPin)(i), (1 << i) & led_state_new);
    }
    led_state = led_state_new;
  }
  delay(100);
}
