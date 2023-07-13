#include <Arduino_MKRIoTCarrier.h>
#include <LiquidCrystal_I2C.h>

MKRIoTCarrier carrier;
float temperature = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
String tem;

void setup() {
  Serial.begin(9600);

  CARRIER_CASE = false;
  carrier.begin();

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  temperature = carrier.Env.readTemperature();
  Serial.print("온도 : ");
  Serial.println(temperature);
  
   if(temperature > 30){
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("!Fire!");
    lcd.setCursor(0,1);
    lcd.print("Follow the Light");
    
    tone(1, 523, 200);tone(1, 523, 200);
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
   }else{
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
