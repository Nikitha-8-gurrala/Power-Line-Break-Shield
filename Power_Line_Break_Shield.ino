#define BLYNK_TEMPLATE_ID "TMPL3zIIcs3z-"
#define BLYNK_TEMPLATE_NAME "power line break shield"
#define BLYNK_AUTH_TOKEN "your_auth_token"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
char ssid[] = "your_wifi_name";
char pass[] = "your_wifi_password";

int voltagePin = 34;
int buzzerPin = 5;
int ledPin = 18;

bool notified = false;

void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  Serial.println("--------------------------------------------------");
  Serial.println("SYSTEM STARTING...");
  Serial.println("Connecting to WiFi...");
  Serial.println("SSID: " + String(ssid));
  Serial.println("--------------------------------------------------");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected Successfully!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("--------------------------------------------------");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Blynk Connected!");
}

void loop() {
  Blynk.run();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("⚠ WiFi Disconnected! Trying to reconnect...");
    WiFi.reconnect();
    delay(1000);
  }

  int raw = analogRead(voltagePin);
  float voltage = (raw / 4095.0) * 25.0;

  Serial.print("RAW: ");
  Serial.print(raw);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);

  Blynk.virtualWrite(V0, voltage);

  if (voltage <= 0.1) {
    if (!notified) {
      Blynk.logEvent("powerlinebreak", "⚠ No Voltage Detected at location :https://maps.app.goo.gl/sVLNHtZcR27UrsfV8?g_st=aw");
      Serial.println("Blynk Notification Sent!");
      notified = true;
    }

    digitalWrite(buzzerPin, HIGH);

    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);

    Serial.println("Voltage = 0 → Buzzer ON, LED BLINKING...");
  }

  else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    if (notified) {
      Serial.println("Voltage Restored → Alarm OFF");
      notified = false;
    }

    delay(200);
  }
}