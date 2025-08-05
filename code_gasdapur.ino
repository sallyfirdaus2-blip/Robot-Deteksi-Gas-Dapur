#include <WiFi.h>
#include <HTTPClient.h>


// WiFi credentials
const char* ssid = "Sally ridwan";
const char* password = "sallycoyyy";

// Telegram bot credentials
const String BOT_TOKEN = "7782656761:AAE5WhRP3gyGVD222NDknfh7gxdDZ3jtV4c";
const String CHAT_ID = "1985437419";

// Pin konfigurasi
const int GAS_SENSOR_PIN = 34; 
const int RELAY_PIN = 27;
const int BUZZER_PIN = 26;

// Ambang batas gas
const int gasThreshold = 2011;

// Waktu interval kirim ulang peringatan (ms)
const unsigned long alertCooldown = 60000;
unsigned long lastAlertTime = 0;

bool alreadySent = false;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  connectToWiFi();
}

void loop() {
  // Cek koneksi WiFi dan reconnect jika terputus
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  int gasValue = analogRead(GAS_SENSOR_PIN);
  Serial.print("Gas value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    if (!alreadySent || (millis() - lastAlertTime > alertCooldown)) {
      sendTelegramAlert("⚠️ *PERINGATAN!* Kebocoran gas terdeteksi di dapur! Kipas dan alarm telah diaktifkan.");
      alreadySent = true;
      lastAlertTime = millis();
    }
  } else {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    alreadySent = false;
  }

  delay(1000); // Pengambilan data tiap 1 detik
}

void connectToWiFi() {
  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nTerhubung ke WiFi!");
  } else {
    Serial.println("\nGagal terhubung ke WiFi.");
  }
}

void sendTelegramAlert(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // URL Encode jika teks mengandung karakter khusus
    message.replace(" ", "%20");
    message.replace("!", "%21");
    message.replace("*", "%2A");

    String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage?chat_id=" + CHAT_ID + "&text=" + message + "&parse_mode=Markdown";

    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.println("Peringatan terkirim ke Telegram");
    } else {
      Serial.print("Gagal mengirim peringatan, kode: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Tidak terhubung ke WiFi. Gagal mengirim peringatan.");
  }
}
