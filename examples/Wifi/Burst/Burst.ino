/*
  DACBurst over WiFi example.

  Connects to a Red Pitaya over WiFi and triggers a 3-cycle
  sine burst on generator channel 1 every second.
  Update the `server` IP below and provide WiFi credentials
  in arduino_secrets.h before uploading.
*/

#include <WiFiS3.h>
#include "SCPI_RP.h"
#include "arduino_secrets.h"  // defines SECRET_SSID & SECRET_PASS

// ---- Red Pitaya over TCP ----
scpi_rp::SCPIRedPitaya rp;
WiFiClient client;
IPAddress server(192, 168, 0, 17);   // <-- adjust to your Red Pitaya
const uint16_t serverPort = 5000;    // SCPI/TCP port on Red Pitaya

void setup() {
  Serial.begin(115200);
  delay(100);

  // ----- STATIC IP (falls back to DHCP silently if unsupported) -----
  {
    IPAddress local(192, 168, 0, 50);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress dns(8, 8, 8, 8);
    WiFi.config(local, gateway, subnet, dns);
    Serial.println("Static IP configuration applied (no return code)");
  }

  // ----- CONNECT TO WIFI -----
  Serial.print("Connecting to WiFi \"");
  Serial.print(SECRET_SSID);
  Serial.println("\" ...");
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  Serial.print("Waiting for connection");
  unsigned long wifiStart = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifiStart < 30000) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection failed");
    while (true) delay(1000);
  }
  Serial.print("WiFi connected - IP = ");
  Serial.println(WiFi.localIP());

  // ----- CONNECT TCP TO RED PITAYA -----
  Serial.print("Connecting to Red Pitaya at ");
  Serial.print(server);
  Serial.print(":");
  Serial.println(serverPort);

  if (!client.connect(server, serverPort)) {
    Serial.println("TCP connection failed");
    while (true) delay(1000);
  }
  Serial.println("TCP connected!");

  // Bind SCPI to the TCP socket
  rp.initSocket(&client);

  // ----- CONFIGURE GENERATOR CH1 FOR BURST -----
  Serial.println("\n--- Configuring Generator CH1 (Burst) ---");
  rp.gen.reset();

  rp.gen.trigSource(scpi_rp::GEN_CH_1, scpi_rp::GEN_INT); // internal trigger
  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);  // 10 kHz
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);    // 0.9 Vpp

  rp.gen.genMode(scpi_rp::GEN_CH_1, scpi_rp::GEN_BURST);
  rp.gen.burstInitValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstLastValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstNCycles(scpi_rp::GEN_CH_1, 3);        // 3 cycles per burst
  rp.gen.burstNRepetitions(scpi_rp::GEN_CH_1, 1);   // one burst per trigger
  rp.gen.burstPeriod(scpi_rp::GEN_CH_1, 400);       // 400 us between bursts

  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
}

void loop() {
  // Trigger a burst each second
  rp.gen.sync(scpi_rp::GEN_CH_1);
  delay(1000);
}
