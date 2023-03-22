#include <LiquidCrystal.h>
#include <DHT.h>

// Khai báo các chân kết nối với linh kiện
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, buttonPin = 8, contrastPin = 3;
const int DHT11_PIN = A0;
// Khai báo biến
int buttonState = 0;
float temperatureCC = 0, temperatureCF = 0;
// Khởi tạo LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Khởi tạo cảm biến DHT11
DHT dht(DHT11_PIN, DHT11);

boolean isCelsius = true;
unsigned long lastButtonPress = 0;

void setup() {

  // Khởi tạo LCD với kích thước 16x2
  lcd.begin(16, 2);
  lcd.display();   // Bật đèn nền của màn hình LCD
  // Điều chỉnh độ sáng của LCD
  analogWrite(contrastPin, 30);

  // Khai báo chế độ đầu ra cho nút nhấn
  pinMode(buttonPin, INPUT_PULLUP);

  // Khởi tạo cảm biến DHT11
  dht.begin();
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Đọc trạng thái của nút nhấn

  float temperatureC = dht.readTemperature();  // Đọc nhiệt độ từ cảm biến DHT11
  float temperatureCF = temperatureC * 1.8 + 32;
  unsigned long currentTime = millis();


  if (buttonState == LOW) {
    delay(50);
    if ((currentTime - lastButtonPress) < 1500 && buttonState == LOW) {
      lcd.noDisplay();
      // lcd.print("LCD OFF");
    }
    lastButtonPress = currentTime;
    isCelsius = !isCelsius;  // Toggle between Celsius and Fahrenheit
    delay(200);
  }

  if (isCelsius == true) {   // Nếu nút nhấn được nhấn
    lcd.setCursor(0, 0);     // Đặt con trỏ về vị trí đầu tiên trên màn hình LCD
    lcd.print("Nhiet do:");  // Hiển thị chuỗi "Temp: " lên màn hình LCD
    lcd.print(temperatureC);  // Hiển thị nhiệt độ lên màn hình LCD
    lcd.print("oC");         // Hiển thị đơn vị Celsius lên màn hình LCD

  } else {
    lcd.setCursor(0, 0);
    // Chuyển đổi độ Celsius sang độ Fahrenheit

    lcd.print("Nhiet do:");
    lcd.print(temperatureCF);  // Hiển thị nhiệt độ lên màn hình LCD
    lcd.print("oF");        // Hiển thị đơn vị
  }
}