#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";  

#define BOToken "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"      

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// ย้ายพินรับสัญญาณจาก 16 มาเป็น พิน 4 (GPIO4) เพื่อป้องกันบอร์ดค้างช่วง Boot
#define SIGNAL_PIN 4 

bool isAlarmState = false;

void setup() {
  Serial.begin(115200);
  pinMode(SIGNAL_PIN, INPUT_PULLDOWN);

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  client.setInsecure(); 

  // รอเชื่อมต่อ Wi-Fi (ถ้าเกิน 20 วินาทีจะรีเซ็ตเริ่มใหม่)
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    bool sent = bot.sendMessage(CHAT_ID, "🤖 ระบบห้องเรียนอัจฉริยะป้องกันฝุ่น PM2.5 พร้อมใช้งานแล้ว!", "");
    if (sent) {
      Serial.println("Telegram sent successfully!");
    } else {
      Serial.println("Telegram failed! Check Token or Chat ID.");
    }
  } else {
    Serial.println("\nWiFi Connection Failed! Restarting...");
    ESP.restart(); // ถ้าต่อ Wi-Fi ไม่ติดให้สั่งรีสตาร์ตบอร์ดอัตโนมัติ
  }
}

void loop() {
  int signalStatus = digitalRead(SIGNAL_PIN);

  // สภาวะที่ 1: ตรวจพบฝุ่นสูง (พิน 4 เป็น HIGH)
  if (signalStatus == HIGH && !isAlarmState) {
    isAlarmState = true;
    Serial.println("ALARM Triggered!");

    String message = "🚨 **คำเตือน! ตรวจพบฝุ่นละอองสูง (PM2.5 >= 100)**\n";
    message += "😷 สถานะระบบ: เปิดพัดลมฟอกอากาศอัตโนมัติ\n";
    message += "🚪 สถานะประตู-หน้าต่าง: ปิดอัตโนมัติ";
    
    bot.sendMessage(CHAT_ID, message, "Markdown");
  } 
  // สภาวะที่ 2: ฝุ่นกลับสู่ปกติ (พิน 4 เป็น LOW)
  else if (signalStatus == LOW && isAlarmState) {
    isAlarmState = false;
    Serial.println("NORMAL Triggered!");

    String message = "🟢 **อากาศกลับสู่ภาวะปกติแล้ว (PM2.5 < 100)**\n";
    message += "🍃 สถานะระบบ: ปิดพัดลมฟอกอากาศ\n";
    message += "🚪 สถานะประตู-หน้าต่าง: เปิดระบายอากาศ";

    bot.sendMessage(CHAT_ID, message, "Markdown");
  }

  delay(200);
}