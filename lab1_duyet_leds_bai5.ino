// C++ code
//
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // các chân kết nối đến các LED
int analogPin = A0; // chân kết nối đến biến trở

void setup() {
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT); // thiết lập chế độ OUTPUT cho các chân kết nối LED
  }
}

void loop() {
  int sensorValue = analogRead(analogPin); // đọc giá trị từ biến trở
  int brightness = map(sensorValue, 0, 1023, 0, 255); // chuyển đổi giá trị từ 0-1023 về 0-255

  for (int i = 0; i < 10; i++) {
    analogWrite(ledPins[i], brightness); // điều chỉnh độ sáng của LED
  }
  delay(10); // đợi 10ms
}