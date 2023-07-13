#include <Arduino_MKRIoTCarrier.h>
#include <LiquidCrystal_I2C.h>  // lcd 모니터

MKRIoTCarrier carrier;
float temperature = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  CARRIER_CASE = false;
  carrier.begin();

  // 순서대로 흰색, 노란색, 초록색, 파란색 led 전구 디지털 핀과 연결
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  // 모니터 초기화
  lcd.init();
  lcd.backlight();
}

void loop() {
  // 온도 측정 및 시리얼 출력
  temperature = carrier.Env.readTemperature();
  Serial.print("온도 : ");
  Serial.println(temperature);

  // 30도 이상 -> 화재로 가정
  if(temperature > 30){
    // 화재 및 대피 안내
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("!Fire!");
    lcd.setCursor(0,1);
    lcd.print("Follow the Light");

    // 경보
    tone(1, 523, 200);
    // 전구
    digitalWrite(5, HIGH);
    delay(200);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    delay(200);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
   }else{ // 화재 없거나 진압 완료 시
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("temp : ");
    lcd.setCursor(8,0);
    lcd.print(temperature);
    lcd.setCursor(0,1);
    lcd.print("Have a Safe Hike");
    
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    delay(800);
   }
}
