#include <WiFiS3.h>
#include "SCPI_RP.h"
#include "arduino_secrets.h"  // defines SECRET_SSID & SECRET_PASS

// ---- Red Pitaya over TCP ----
scpi_rp::SCPIRedPitaya rp;
WiFiClient client;
IPAddress server(192, 168, 0, 17);   // <-- adjust if needed
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

  // ----- CONFIGURE GENERATOR CH1 FOR SWEEP -----
  Serial.println("\n--- Configuring Generator CH1 (Sweep) ---");
  rp.gen.reset();
  Serial.print("[LOG] Generator reset at millis() = ");
  Serial.println(millis());

  // Base signal setup
  rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SINE);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);  // 0.9 Vpp

  // Sweep setup: 1 kHz -> 100 kHz, LOG, up-down, 10 s
  rp.gen.sweepDefault();
  rp.gen.sweepDirection(scpi_rp::GEN_CH_1, scpi_rp::GEN_SWEEP_UP_DOWN);
  rp.gen.sweepFreqStart(scpi_rp::GEN_CH_1, 1000);
  rp.gen.sweepFreqEnd(scpi_rp::GEN_CH_1, 100000);
  rp.gen.sweepMode(scpi_rp::GEN_CH_1, scpi_rp::GEN_SWEEP_LOG);
  rp.gen.sweepTime(scpi_rp::GEN_CH_1, 10000000ULL);  // 10,000,000 us = 10 s

  // ----- VERIFY SETTINGS -----
  scpi_rp::EGENSweepMode mode = scpi_rp::GEN_SWEEP_LINEAR;
  scpi_rp::EGENSweepDir dir = scpi_rp::GEN_SWEEP_NORMAL;
  bool state = false;
  float start = 0.0f;
  float end = 0.0f;
  uint64_t time = 0;

  if (rp.gen.sweepDirectionQ(scpi_rp::GEN_CH_1, &dir)) {
    Serial.print("Direction = ");
    Serial.println((int)dir);
  } else {
    Serial.println("Error get direction");
  }

  if (rp.gen.sweepModeQ(scpi_rp::GEN_CH_1, &mode)) {
    Serial.print("Mode = ");
    Serial.println((int)mode);
  } else {
    Serial.println("Error get mode");
  }

  if (rp.gen.sweepFreqStartQ(scpi_rp::GEN_CH_1, &start)) {
    Serial.print("Start freq = ");
    Serial.println(start);
  } else {
    Serial.println("Error get start freq");
  }

  if (rp.gen.sweepFreqEndQ(scpi_rp::GEN_CH_1, &end)) {
    Serial.print("End freq = ");
    Serial.println(end);
  } else {
    Serial.println("Error get end freq");
  }

  if (rp.gen.sweepTimeQ(scpi_rp::GEN_CH_1, &time)) {
    Serial.print("Time (us) = ");
    Serial.println((double)time);
  } else {
    Serial.println("Error get time");
  }

  // ----- ENABLE & START SWEEP -----
  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
  rp.gen.sync(scpi_rp::GEN_CH_1);

  rp.gen.sweepReset();                     // Ensure clean sweep state
  rp.gen.sweepState(scpi_rp::GEN_CH_1, true);

  if (rp.gen.sweepStateQ(scpi_rp::GEN_CH_1, &state)) {
    Serial.print("Sweep state = ");
    Serial.println(state ? "ON" : "OFF");
  } else {
    Serial.println("Error get state");
  }

  Serial.println("--- Sweep started ---");
}

void loop() {
  delay(1000);
}
