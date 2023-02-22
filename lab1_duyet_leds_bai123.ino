// C++ code
// Lab1: Duyệt leds

int pinLed[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
//				0, 1, 2, 3, 4, 5, 6, 7,  8,  9

void setup()
{
 // Khai báo chân digital output cho các led
  for(int i=0; i<=9; i++) {
    pinMode(pinLed[i], OUTPUT);
  }
}

// Câu 1: Sáng dần theo thứ tự từ trái sang phải rồi tắt dần từ phải về trái
void cau1()
{
  // Sáng dần theo thứ tự từ trái sang phải
  for(int i=0; i<=9; i++)
  {
    digitalWrite(pinLed[i], HIGH);
    delay(500);
    // Sáng đến đèn thứ 10
    if(i == 9)
    {
      // Tắt dần từ phải về trái
      for(int j=9; j>=0; j--)
      {
      digitalWrite(pinLed[j], LOW);
        delay(500);
      }
    }
  }
}

// Câu 2: Sáng dần từ hai bên vào trong rồi tắt dần từ trong ra hai bên
void cau2()
{
   int i=0;
   int j=9;
   
   do
   {
     digitalWrite(pinLed[i++], HIGH);
     digitalWrite(pinLed[j--], HIGH);
     delay(500);
     if(i>j)
     {
       while(true)
       {
       digitalWrite(pinLed[--i], LOW);
       digitalWrite(pinLed[++j], LOW);
       delay(500);
         if(i==0 && j==9)
         {
           break;
         }
       }
     }
   }while(true);
}

// Câu 3: Sáng lần lượt theo chẳn, lẻ
void tatTatCa()
{
  digitalWrite(pinLed[0], LOW);
  digitalWrite(pinLed[1], LOW);
  digitalWrite(pinLed[2], LOW);
  digitalWrite(pinLed[3], LOW);
  digitalWrite(pinLed[4], LOW);
  digitalWrite(pinLed[5], LOW);
  digitalWrite(pinLed[6], LOW);
  digitalWrite(pinLed[7], LOW);
  digitalWrite(pinLed[8], LOW);
  digitalWrite(pinLed[9], LOW);
}
void cau3()
{
  for(int i=0; i<=8; i=i+2)
  {
    digitalWrite(pinLed[i], HIGH);
    delay(500);
    if(i==8)
    {
      tatTatCa();
      break;
    }
  }
  for(int i=1; i<=9; i=i+2)
  {
    digitalWrite(pinLed[i], HIGH);
    delay(500);
    if(i==9)
    {
      tatTatCa();
    }
  } 
}

void loop()
{
  //cau1();
  //cau2();
  //cau3();
}