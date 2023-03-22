String inp;
int R = 6, G = 9, B = 11;
float time;
int lv[4] = { 0, 0, 0, 0 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {

  if (Serial.available()) {
    // nếu có dữ liệu gửi đến
    inp = Serial.readStringUntil('\n');
    Serial.println("\n\n");
    // đọc giá trị gửi đến cho đến khi gặp kí tự xuống dòng \n
    Serial.println(inp);
    for (int i = 0; i < inp.length(); i++) {
      //Serial.println(text.charAt(i));
      // cuong do den red
      if (inp.charAt(i) == 'R') {
        i++;
        lv[0] = 0;
        while (inp.charAt(i) > 47 && inp.charAt(i) < 58) {
          lv[0] = lv[0] * 10 + inp.charAt(i++) - 48;
        }
        i--;
      }
      // cuong do den green
      if (inp.charAt(i) == 'G') {
        i++;
        lv[1] = 0;
        while (inp.charAt(i) > 47 && inp.charAt(i) < 58) {
          lv[1] = lv[1] * 10 + inp.charAt(i++) - 48;
        }
        i--;
      }
      // cuong do den blue
      if (inp.charAt(i) == 'B') {
        i++;
        lv[2] = 0;
        while (inp.charAt(i) > 47 && inp.charAt(i) < 58) {
          lv[2] = lv[2] * 10 + inp.charAt(i++) - 48;
        }
        i--;
      }
      if (inp.charAt(i) == 'D') {
        i++;
        lv[3] = 0;
        while (inp.charAt(i) > 47 && inp.charAt(i) < 58) {
          lv[3] = lv[3] * 10 + inp.charAt(i++) - 48;
        }
        i--;
      }
    }
    Serial.println(lv[0] > 255 ? 255 : lv[0]);
    Serial.println(lv[1] > 255 ? 255 : lv[1]);
    Serial.println(lv[2] > 255 ? 255 : lv[2]);
    Serial.println(lv[3] > 255 ? 255 : lv[3]);
    analogWrite(R, lv[0] > 255 ? 255 : lv[0]);
    analogWrite(G, lv[1] > 255 ? 255 : lv[1]);
    analogWrite(B, lv[2] > 255 ? 255 : lv[2]);
    // delay(2000);
    // "R255, G0, B50, D1"
    delay(lv[3] * 1000);
    analogWrite(R, LOW);
    analogWrite(G, LOW);
    analogWrite(B, LOW);
    lv[3] = 0;
  }
}


