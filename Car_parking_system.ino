#include <Servo.h>  //includes the servo library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 24, 8);

Servo myservo;

#define ir_enter 2
#define ir_back 4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8


int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4;

void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);


  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  myservo.attach(3);
  myservo.write(90);
  lcd.init();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 1);
  lcd.print("   Smart Car  parking ");

  Serial.println(" car parking  ");
  lcd.setCursor(0, 2);
  lcd.print("       System     ");
  Serial.println(" system");

  delay(1000);
  Read_Sensor();
  //Edit 2 lines
  int total = S1 + S2 + S3 + S4;
  slot = slot - total;
}

void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;

  if (digitalRead(ir_car1) == 0) {
    S1 = 1;
  }
  if (digitalRead(ir_car2) == 0) {
    S2 = 1;
  }
  if (digitalRead(ir_car3) == 0) {
    S3 = 1;
  }
  if (digitalRead(ir_car4) == 0) {
    S4 = 1;
  }

  // int total = S1 + S2 + S3 + S4;
  // slot = slot - total;
}

void loop() {

  Read_Sensor();

  // int total = S1 + S2 + S3 + S4;
  // slot = slot - total;
  lcd.setCursor(0, 0);
  lcd.print("   Have Slot:  ");
  Serial.println("  Have Slot: ");
  lcd.print(slot);
  Serial.println("slot");
  lcd.print("    ");

  lcd.setCursor(0, 1);
  if (S1 == 1) {
    lcd.print("S1:Fill   ");
    Serial.println("S1:Fill ");
  } else {
    lcd.print("S1:Empty  ");
    Serial.println("S1:Empty");
  }

  lcd.setCursor(10, 1);
  if (S2 == 1) {
    lcd.print("S2:Fill ");
    Serial.println("S2:Fill ");
  } else {
    lcd.print("S2:Empty ");
    Serial.println("S2:Empty ");
  }

  lcd.setCursor(0, 2);
  if (S3 == 1) {
    lcd.print("S3:Fill   ");
    Serial.println("S3:Fill   ");
  } else {
    lcd.print("S3:Empty  ");
    Serial.println("S3:Empty");
  }

  lcd.setCursor(10, 2);
  if (S4 == 1) {
    lcd.print("S4:Fill ");
    Serial.println("S4:Fill ");
  } else {
    lcd.print("S4:Empty ");
    Serial.println("S4:Empty ");
  }


  if (digitalRead(ir_enter) == 0 && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180);
        slot = slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print(" Sorry Parking Full ");
      Serial.println("Sorry Parking Full ");
      delay(1500);
    }
  }

  if (digitalRead(ir_back) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180);
      slot = slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(90);
    flag1 = 0, flag2 = 0;
  }

  delay(1000);
}
