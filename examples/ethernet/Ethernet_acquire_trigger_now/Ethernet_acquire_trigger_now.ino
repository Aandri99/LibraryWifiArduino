// The example shows how you can use RP SCPI API together with Ethernet
// controllers of the W5100, W5200, W5500 series Before starting, you need to
// Example of data capture at the Fast ADC IN1
// Before starting, you need to connect Fast OUT 1 <=> Fast IN1

// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino
// - Ethernet

// Before run test need connect AI0 (E2) <=> AO0 (E2) with wire on Red Pitaya

#include <Ethernet.h>

#include "SCPI_RP.h"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);
IPAddress server(200, 0, 0, 15);

EthernetClient client;

scpi_rp::SCPIRedPitaya rp;

bool isInit = false;
float value = 0;

void acquire() {
  rp.gen.reset();
  rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SINE);
  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);
  rp.gen.enable(scpi_rp::GEN_CH_1, true);
  rp.gen.sync(scpi_rp::GEN_CH_1);

  if (!rp.acq.control.reset()) {
    Serial.println("Error reset acq");
  }

  float hysteresis = 0.05;
  if (!rp.acq.trigger.hysteresis(hysteresis)) {
    Serial.println("Error set hysteresis");
  }

  if (!rp.acq.trigger.hysteresisQ(&hysteresis)) {
    Serial.println("Error get hysteresis");
  } else {
    Serial.print("Hysteresis = ");
    Serial.println(hysteresis);
  }

  uint32_t decimation = 123;
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
    rp.acq.trigger.fillQ(&state);
    if (state) break;
  }

  if (!rp.acq.control.stop()) {
    Serial.println("Error stop ADC");
  }
  // Read data

  uint32_t wp = 0;
  if (!rp.acq.data.writePositionQ(&wp)) {
    Serial.println("Error get write pointer");
  } else {
    Serial.print("Write pointer = ");
    Serial.println(wp);
  }

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
    rp.acq.data.dataStartEndQ(scpi_rp::ACQ_CH_1, tp, wp, &sample, &last);
    Serial.print(idx++);
    Serial.print(" - ");
    Serial.print(sample, 6);
    Serial.println("");
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println("Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println(
          "Ethernet shield was not found.  Sorry, can't run without "
          "hardware. ");
      while (true) {
        delay(1);  // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // initialize the Ethernet device not using DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.print("DHCP IP address: ");
  Serial.println(Ethernet.localIP());

  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 5000)) {
    Serial.println("connected");
    rp.initSocket(&client);
    acquire();
    client.stop();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() { delay(1000); }