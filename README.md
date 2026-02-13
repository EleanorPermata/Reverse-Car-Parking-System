# 🚗 Arduino Maker UNO Reverse Car Park System

## 📌 Project Overview
This project demonstrates the use of **Arduino Maker UNO** to build a **Reverse Car Parking Assistance System**.  
The system helps drivers detect obstacles while reversing by providing **real-time audio, visual, and LCD feedback**.  

It integrates **ultrasonic sensors, LEDs, buzzer, and LCD display** to notify drivers of safe, warning, and danger distances, improving safety and showcasing practical IoT applications in automotive systems.

---

## 🎯 Objectives
- Develop a functional reverse car parking system using **Arduino Maker UNO**.  
- Provide **audio (buzzer)** and **visual (LEDs + LCD)** alerts when obstacles are detected.  
- Enhance understanding of **sensor integration, signal processing, and user interface design**.  

---

## 🛠️ Components Used
- **Arduino Maker UNO (ATmega328P)** – main microcontroller  
- **HC-SR04 Ultrasonic Sensor** – distance measurement  
- **16x2 LCD (I2C)** – real-time distance display  
- **LEDs (Red, Yellow, Green)** – proximity indicators  
- **Piezoelectric Buzzer** – audio alerts  
- **Breadboard & Jumper Wires** – circuit prototyping  
- **Resistors (220Ω, 1kΩ)** – current control  
- **USB Power Supply / Battery Pack**  

---

## ⚙️ System Design
- **Green LED** → Safe distance (>10 cm)  
- **Yellow LED + buzzer beep** → Warning distance (5–10 cm)  
- **Red LED + continuous buzzer tone** → Danger distance (≤4 cm)  
- **LCD Display** → Shows exact distance + status message  

---

## 🖥️ Tinkercad & Physical Setup
- Designed and tested virtually in **Tinkercad** before physical assembly.  
- Physical prototype includes proper wiring of LEDs, buzzer, LCD, and ultrasonic sensor to the Arduino Maker UNO.  

---

## 💻 Source Code
The project uses **Arduino IDE** with the `LiquidCrystal_I2C` library for LCD control.  
Key features:
- **Setup function** initializes components.  
- **Loop function** continuously measures distance and updates LEDs, buzzer, and LCD.  
- **Distance-based actions** provide real-time feedback to the driver.  

```cpp
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzer = 8;
int pinGREEN = 2, pinYELLOW = 3, pinRED = 4;
int echoPin = 6, trigPin = 7;
int duration = 0, distanceCM = 0;

void setup() {
  lcd.init(); lcd.backlight();
  pinMode(buzzer, OUTPUT);
  pinMode(pinGREEN, OUTPUT);
  pinMode(pinYELLOW, OUTPUT);
  pinMode(pinRED, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCM = duration * 0.017175;

  lcd.clear(); lcd.setCursor(0,0);
  lcd.print("Distance: "); lcd.print(distanceCM); lcd.print(" cm");

  if (distanceCM <= 4) {
    digitalWrite(pinRED, HIGH); tone(buzzer, 2000);
    lcd.setCursor(0,1); lcd.print("DANGER DISTANCE");
  } else if (distanceCM <= 10 && distanceCM >= 5) {
    digitalWrite(pinYELLOW, HIGH); tone(buzzer, 2000);
    lcd.setCursor(0,1); lcd.print("WARNING DISTANCE");
  } else {
    digitalWrite(pinGREEN, HIGH); noTone(buzzer);
    lcd.setCursor(0,1); lcd.print("SAFE DISTANCE");
  }
  delay(50);
}
```
---

## ⚠️ Limitations
- Sensor accuracy may be affected by **dust, rain, or extreme temperatures**.  
- System only measures **distance**, not obstacle type/shape.  
- **Simple LED + buzzer alerts** may be insufficient in noisy environments.  
- Small delays in response time.  

---

## 🚀 Future Enhancements
- Integrate **multiple sensors (radar/infrared)** for better accuracy.  
- Add **voice alerts or graphical displays** for richer feedback.  
- Implement **machine learning** for obstacle classification.  
- Enable **wireless connectivity** to sync with smartphone apps.  

---

## 🏁 Conclusion
This project highlights the **real-world application of Arduino Maker UNO** in automotive safety.  
By combining sensors, LEDs, buzzer, and LCD, the system provides **affordable and effective reverse parking assistance**.  
It serves as a foundation for future research in **embedded systems and automotive IoT**.

