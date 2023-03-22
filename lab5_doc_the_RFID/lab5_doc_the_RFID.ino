
// // GND
// // Vcc = 3.3V
// // * -----------------------------------------------------------------------------------------
// //  *             MFRC522      Arduino       
// //  *             Reader/PCD   Uno/101       
// //  * Signal      Pin          Pin           
// //  * -----------------------------------------------------------------------------------------
// //  * RST/Reset   RST          9             
// //  * SPI SS      SDA(SS)      10           
// //  * SPI MOSI    MOSI         11 / ICSP-4   
// //  * SPI MISO    MISO         12 / ICSP-1   
// //  * SPI SCK     SCK          13 / ICSP-3  
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 2 // led chân dương số 2, chân âm GND
int status = 0;
long preTime = -9999;

MFRC522 mfrc522(SS_PIN, RST_PIN);

//byte correctUID[] = { 0x71, 0x53, 0x03, 0x27 };  // Replace with the correct UID
byte correctUID[] = { 0x30, 0xf1, 0x70, 0x1A };  // Replace with the correct UID
//406E061A
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  // Check for a new card
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

    // // Đọc ID từ thẻ RFID
    String id = "";
    // for (byte i = 0; i < mfrc522.uid.size; i++) {
    //   id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    //   id.concat(String(mfrc522.uid.uidByte[i], HEX));
    // }
    // Serial.println("ID: " + id);

    byte uid[4];
    for (byte i = 0; i < 4; i++) {
      uid[i] = mfrc522.uid.uidByte[i];
      id.concat(String(uid[i] < 0x10 ? "0" : ""));
      id.concat(String(uid[i], HEX));
    }
    Serial.println("ID: " + id);
    if (memcmp(uid, correctUID, sizeof(correctUID)) == 0) {
      status = 1;
      long curTime = millis();
      if (curTime - preTime < 1000) {
        
        Serial.println(curTime);
        Serial.println(preTime);
        Serial.println(curTime - preTime);
        status = 3;
      }
      preTime = millis();
    } else {
      status = 2;
    }
  }
  if (status == 1) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("1");
  } else if (status == 2) {
    Serial.println("2");
    blink();
  } else if (status == 3) {
    Serial.println("3");
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("else");
    digitalWrite(LED_PIN, LOW);
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(100);
}


void blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
}