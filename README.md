# 🚨 Sistem Deteksi Kebocoran Gas Dapur Berbasis IoT dengan Notifikasi Telegram

Proyek ini adalah sistem **pendeteksi kebocoran gas otomatis** yang menggunakan sensor **MQ-2**, mikrokontroler **NodeMCU ESP32**, serta **notifikasi Telegram**. Ketika terdeteksi kebocoran gas, sistem akan secara otomatis:
- Mengaktifkan **kipas (relay)**
- Mengaktifkan **buzzer (alarm)**
- Mengirim **peringatan ke Telegram**

---

## 📦 Fitur Utama

- Deteksi kebocoran gas menggunakan **sensor MQ-2**
- Pengendalian **kipas otomatis via relay**
- **Alarm buzzer** aktif saat deteksi bahaya
- Kirim notifikasi real-time ke **Telegram Bot**
- Pemantauan data gas melalui **Serial Monitor**

---

## 🛠️ Komponen Hardware

| No | Komponen              | Keterangan               |
|----|------------------------|--------------------------|
| 1  | NodeMCU ESP32          | Mikrokontroler IoT       |
| 2  | Sensor MQ-2            | Deteksi gas LPG, CO, dll |
| 3  | Relay Module           | Mengendalikan kipas      |
| 4  | Buzzer                 | Alarm suara              |
| 5  | Breadboard & Kabel     | Rangkaian                |
| 6  | Kipas DC               | Ventilasi otomatis       |
| 7  | Sumber Daya 5V         | Power supply             |

---

## ⚙️ Diagram Blok

```text
[SENSOR MQ-2] ---> [ESP32] ---> [RELAY -> KIPAS]
                            |-> [BUZZER]
                            |-> [WIFI] ---> [TELEGRAM]
```

💻 Instalasi dan Penggunaan
1. Clone Repository

git clone https://github.com/username/deteksi-kebocoran-gas-iot.git
cd deteksi-kebocoran-gas-iot

2. Buka kode di Arduino IDE
3. Pastikan Library Tersedia:
WiFi.h (untuk ESP32)

HTTPClient.h

4. Ganti Konfigurasi di Kode:
cpp
Salin
Edit

const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
const String BOT_TOKEN = "TOKEN_BOT_TELEGRAM";
const String CHAT_ID = "CHAT_ID_KAMU";
5. Upload ke Board
Pilih board: ESP32 Dev Module

Upload kode

🔄 Alur Kerja
ESP32 tersambung ke WiFi

Sensor MQ-2 membaca kadar gas

Jika melebihi ambang batas:

Kipas menyala (via relay)

Alarm berbunyi

Notifikasi dikirim ke Telegram

Jika gas normal kembali:

Kipas dan alarm mati

Sistem reset untuk notifikasi berikutnya

📷 Dokumentasi Visual (Opsional)
Tambahkan foto alat & wiring diagram di sini.

Gas value: 1890
Gas value: 2103
⚠️ PERINGATAN! Kebocoran gas terdeteksi...
Peringatan terkirim ke Telegram

🤝 Kontribusi
Pull request dan saran sangat diterima! Jangan ragu untuk fork dan bantu kembangkan proyek ini 💡

