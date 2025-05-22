#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzer = 8; 

int pinGREEN = 2;
int pinYELLOW = 3;
int pinRED = 4;

int echoPin = 6;
int trigPin = 7;
  
int duration = 0;
int distanceCM = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(buzzer, OUTPUT); // Buzzer
  pinMode(pinGREEN, OUTPUT); // Green LED
  pinMode(pinYELLOW, OUTPUT); // Yellow LED
  pinMode(pinRED, OUTPUT); // Red LED

  pinMode(echoPin, INPUT); // Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCM = duration * 0.017175;

  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Distance: ");
  lcd.print(distanceCM);
  lcd.println(" cm");

  if (distanceCM <= 4) {
    digitalWrite(pinRED, HIGH);
    digitalWrite(pinYELLOW, LOW);
    digitalWrite(pinGREEN, LOW);
    tone(buzzer, 2000);

    lcd.setCursor(0, 1); 
    lcd.print("DANGER DISTANCE");
  }
  else if (distanceCM <= 10 && distanceCM >= 5) {
    digitalWrite(pinRED, LOW);
    digitalWrite(pinYELLOW, HIGH); 
    digitalWrite(pinGREEN, LOW);
    noTone(buzzer);

    for (int i = 0; i < 5; i++) {
      digitalWrite(pinYELLOW, HIGH);
      tone(buzzer, 2000);
      delay(100); 
      digitalWrite(pinYELLOW, LOW);
      noTone(buzzer);
      delay(100); 

      lcd.setCursor(0, 1); 
      lcd.print("WARNING DISTANCE ");
    }
  } 
  else {
    digitalWrite(pinRED, LOW);
    digitalWrite(pinYELLOW, LOW);
    digitalWrite(pinGREEN, HIGH); 
    noTone(buzzer); 

    for (int i = 0; i < 5; i++) {
      digitalWrite(pinGREEN, HIGH);
      delay(300); 
      digitalWrite(pinGREEN, LOW);
      delay(300); 
      
      lcd.setCursor(1, 1); 
      lcd.print("SAFE  DISTANCE");
    }
  }
  delay(50);
}