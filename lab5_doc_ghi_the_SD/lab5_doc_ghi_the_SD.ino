// Kết nối module đọc ghi thẻ nhớ SD với Arduino Uno R3. Module này sẽ cung cấp giao diện SPI cho Arduino để giao tiếp với thẻ nhớ SD.
// MISO: kết nối đến chân 12 trên Arduino Uno R3
// MOSI: kết nối đến chân 11 trên Arduino Uno R3
// CLK: kết nối đến chân 13 trên Arduino Uno R3
// CS: kết nối đến chân 10 trên Arduino Uno R3
// Kết nối cảm biến nhiệt độ DHT11 với Arduino Uno R3. Cảm biến DHT có 3 chân:
// Chân GND: kết nối đến GND trên Arduino Uno R3
// Chân VCC: kết nối đến 5V trên Arduino Uno R3
// Chân DAT: kết nối đến chân 2 trên Arduino Uno R3
// Kết nối module thời gian thực RTC DS1307 với Arduino Uno R3. Module này sẽ cung cấp thông tin về thời gian để ghi vào thẻ nhớ SD.
// Chân GND: kết nối đến GND trên Arduino Uno R3
// Chân VCC: kết nối đến 5V trên Arduino Uno R3
// Chân SDA: kết nối đến chân analog A4 trên Arduino Uno R3
// Chân SCL: kết nối đến chân analog A5 trên Arduino Uno R3


#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

const int chipSelect = 10;  // Chân CS của module đọc ghi thẻ nhớ SD

RTC_DS1307 rtc;            // Khởi tạo module thời gian thực RTC
float tempC;               // Biến lưu giá trị nhiệt độ
#define DHTPIN 2           // Chân kết nối của cảm biến DHT11
#define DHTTYPE DHT11      // Loại cảm biến DHT11
DHT dht(DHTPIN, DHTTYPE);  // Khởi tạo đối tượng cảm biến DHT

void setup() {
  Serial.begin(9600);
  dht.begin();

  if (!SD.begin(chipSelect)) {
    Serial.println("Khong the khoi dong the nho SD.");
    return;
  }
  if (!rtc.begin()) {
    Serial.println("Khong the khoi dong module RTC.");
    while (1)
      ;
  }
  if (!rtc.isrunning()) {
    Serial.println("Loi: Module RTC khong the hoat dong.");
    // Thay đổi ngày giờ của module RTC ở đây
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  File dataFile = SD.open("datalog.txt", FILE_WRITE | O_TRUNC);
  if (dataFile) {
    dataFile.print('ok');
  }
}


void loop() {
  float temperature = dht.readTemperature();
  // Đọc giá trị nhiệt độ từ cảm biến LM35
  // int reading = analogRead(sensorPin);
  // tempC = (reading * 5.0) / 1024.0 * 100.0;
  tempC = temperature;
  // Lấy thời gian hiện tại từ module RTC
  DateTime now = rtc.now();
  // Kiểm tra nếu nhiệt độ thay đổi so với lần đọc trước đó
  static float prevTemp = 0;
  // if (abs(prevTemp - tempC) > 0.1) {
    // Ghi thông tin vào thẻ nhớ SD
    if(true){
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.print(now.year(), DEC);
      dataFile.print('/');
      dataFile.print(now.month(), DEC);
      dataFile.print('/');
      dataFile.print(now.day(), DEC);
      dataFile.print(' ');
      dataFile.print(now.hour(), DEC);
      dataFile.print(':');
      dataFile.print(now.minute(), DEC);
      dataFile.print(':');
      dataFile.print(now.second(), DEC);
      dataFile.print(',');
      dataFile.println("nhiet do: ");
      dataFile.print(tempC);
      dataFile.println();
      dataFile.close();
      Serial.println("Da ghi du lieu vao the nho.");
      Serial.print(now.year(), DEC);
      Serial.print('/');
      Serial.print(now.month(), DEC);
      Serial.print('/');
      Serial.print(now.day(), DEC);
      Serial.print(' ');
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.print(',');
      Serial.println("nhiet do: ");
      // Serial.print(tempC);
      Serial.println(tempC);
      prevTemp = tempC;
    }
  }

  //Mở tệp tin "datalog.txt" để đọc dữ liệu đã ghi vào
  File dataFile = SD.open("datalog.txt", FILE_READ);
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }

  //Chờ 10s để đọc lại giá trị nhiệt độ và ghi vào thẻ nhớ
  delay(10000);
}
