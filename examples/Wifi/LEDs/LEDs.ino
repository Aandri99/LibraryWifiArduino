#include <WiFiS3.h>

#include "SCPI_RP.h"
#include "arduino_secrets.h"  // defines SECRET_SSID & SECRET_PASS

// Forward‐declare your full acquisition routine
void acquire();

// SCPI + WiFi client objects
scpi_rp::SCPIRedPitaya rp;
WiFiClient client;
uint8_t led_state = 1;
// Red Pitaya’s IP & port (update as needed)
IPAddress server(192, 168, 0, 17);
const uint16_t serverPort = 5000;

void setup() {
  Serial.begin(115200);
  delay(100);

  // ————— STATIC IP (or DHCP if it fails silently) —————
  {
    IPAddress local(192, 168, 0, 50);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress dns(8, 8, 8, 8);
    WiFi.config(local, gateway, subnet, dns);
    Serial.println("⚙️  Static IP configuration applied (no return code)");
  }

  // ————— CONNECT TO WIFI —————
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
    Serial.println("❌ WiFi connection failed");
    while (true) delay(1000);
  }
  Serial.print("✅ WiFi connected — IP = ");
  Serial.println(WiFi.localIP());

  // ————— CONNECT TCP TO RED PITAYA —————
  Serial.print("Connecting to Red Pitaya at ");
  Serial.print(server);
  Serial.print(":");
  Serial.println(serverPort);

  if (!client.connect(server, serverPort)) {
    Serial.println("❌ TCP connection failed");
    while (true) delay(1000);
  }
  Serial.println("✅ TCP connected!");

  // ————— RUN YOUR SCPI STREAM + ACQUIRE —————
  rp.initSocket(&client);
  acquire();

  client.stop();
  Serial.println("All done.");
}

void loop() {
  // nothing left to do
  delay(1000);
}

// ————— Original acquisition routine, verbatim —————
void acquire() {
  // Toggle LEDs 1–5 in sequence forever
  for (uint8_t led = 1; led <= 5; led++) {
    rp.dio.state((scpi_rp::EDIOPin)led, 1);
    delay(500);
    rp.dio.state((scpi_rp::EDIOPin)led, 0);
    delay(200);
}
}
