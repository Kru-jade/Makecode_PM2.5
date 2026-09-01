# ระบบตรวจวัดคุณภาพอากาศ PM2.5

โครงงานระบบตรวจวัดคุณภาพอากาศ PM2.5 ด้วย micro:bit และ ESP32

ระบบพัฒนาขึ้นเพื่อใช้ตรวจสอบสถานะค่าฝุ่น PM2.5 และแจ้งเตือนผู้ใช้งานผ่าน Telegram โดยใช้ ESP32 เชื่อมต่อเครือข่าย Wi-Fi

## วัตถุประสงค์

1. เพื่อพัฒนาระบบตรวจวัดและติดตามสถานะฝุ่น PM2.5
2. เพื่อประยุกต์ใช้ micro:bit และ ESP32 ในระบบ IoT
3. เพื่อส่งข้อมูลและการแจ้งเตือนผ่านเครือข่ายอินเทอร์เน็ต
4. เพื่อแจ้งเตือนเมื่อค่าฝุ่น PM2.5 อยู่ในระดับที่กำหนด
5. เพื่อเป็นแนวทางในการพัฒนาระบบตรวจวัดคุณภาพอากาศอัจฉริยะ

## อุปกรณ์

- micro:bit
- เซนเซอร์ PM2.5
- Sensor:bit
- ESP32
- สาย USB
- เครือข่าย Wi-Fi 2.4 GHz
- Telegram

## โปรแกรมที่ใช้

- Microsoft MakeCode
- Arduino IDE
- GitHub
- Visual Studio Code

## โครงสร้างไฟล์

```text
Makecode_PM2.5/
├── PM2.5_Project/
│   ├── microbit-pm25.hex
│   └── PM25_Arduino_Share.ino
├── README.md
└── .gitattributes
```

## โปรแกรม micro:bit

ไฟล์โปรแกรมสำหรับ micro:bit

`PM2.5_Project/microbit-pm25.hex`

ไฟล์ `.hex` สามารถนำไปติดตั้งบน micro:bit ได้โดยเชื่อมต่อ micro:bit กับคอมพิวเตอร์ผ่าน USB แล้วคัดลอกไฟล์ไปยังไดรฟ์ `MICROBIT`

## โปรแกรม ESP32

ไฟล์โปรแกรมสำหรับ ESP32

`PM2.5_Project/PM25_Arduino_Share.ino`

โปรแกรมนี้พัฒนาด้วย Arduino IDE สำหรับบอร์ด ESP32 Dev Module

ESP32 ทำหน้าที่เชื่อมต่อ Wi-Fi และส่งการแจ้งเตือนผ่าน Telegram

## การตั้งค่า Wi-Fi

ก่อน Upload โปรแกรม ESP32 ให้กำหนดข้อมูล Wi-Fi

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```
## การตั้งค่า Telegram

กำหนด Telegram Bot Token และ Chat ID

```cpp
#define BOToken "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"
```

**ห้ามเผยแพร่ Wi-Fi Password หรือ Telegram Bot Token จริงบน GitHub**

## Library ที่ใช้

โปรแกรม ESP32 ใช้ Library ดังต่อไปนี้

- WiFi
- WiFiClientSecure
- UniversalTelegramBot
- ArduinoJson

## การตั้งค่า Arduino IDE

1. เปิด Arduino IDE
2. เปิดไฟล์ `PM25_Arduino_Share.ino`
3. เลือกบอร์ด `ESP32 Dev Module`
4. เลือก COM Port ของ ESP32
5. ติดตั้ง Library ที่จำเป็น
6. กำหนดข้อมูล Wi-Fi
7. กำหนด Telegram Bot Token
8. กำหนด Chat ID
9. กด Verify
10. กด Upload
11. เปิด Serial Monitor ที่ 115200 baud

## การทำงานของระบบ

ระบบทำงานโดยรับสถานะจากระบบตรวจวัด PM2.5 ผ่าน micro:bit
และส่งสัญญาณไปยัง ESP32

ESP32 เชื่อมต่อกับ Wi-Fi และทำหน้าที่ส่งการแจ้งเตือนผ่าน Telegram

### ลำดับการทำงาน

```text
เซนเซอร์ PM2.5
       │
       ▼
    micro:bit
       │
       │ สัญญาณสถานะ
       ▼
      ESP32
       │
       ▼
      Wi-Fi
       │
       ▼
    Telegram
       │
       ▼
    ผู้ใช้งาน