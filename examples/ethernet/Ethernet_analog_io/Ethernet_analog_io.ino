// The example shows how you can use RP SCPI API together with Ethernet
// controllers of the W5100, W5200, W5500 series Before starting, you need to
// Example for analog input (AI0) and output (AO0). Every second it changes the
// voltage value and checks them.

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
    isInit = true;
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  if (isInit) {
    float in_value = 0;
    if ((value * 10) > 18) value = 0;
    if (!rp.aio.state(scpi_rp::AOUT_0, value)) {
      Serial.println("Error set value");
    }
    if (!rp.aio.stateQ(scpi_rp::AOUT_0, &in_value)) {
      Serial.println("Error get value");
    }
    Serial.print("AOUT_0 value = ");
    Serial.println(in_value);
    if (!rp.aio.stateQ(scpi_rp::AIN_0, &in_value)) {
      Serial.println("Error get value");
    }
    Serial.print("AIN_0 value = ");
    Serial.println(in_value);
    delay(1000);
    value += 0.1;
  }
}