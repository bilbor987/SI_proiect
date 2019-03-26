#include <LiquidCrystal.h>
 
#define trigPin1 6
#define echoPin1 7
#define buzzPin 8
#define trigPin2 9
#define echoPin2 10
 
#define minDistance 10
#define maxDistance 100
#define minFrequency 31
#define maxFrequency 4095

// LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() {
    lcd.begin(16, 2);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(buzzPin, OUTPUT);
}

long readDistance(int echoPin, int trigPin) {
    // Reads a pulse (either HIGH or LOW) on a pin and returns the length of the pulse in microseconds
    long distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads a pulse (either HIGH or LOW) on a pin and returns the length of the pulse in microseconds
    distance = pulseIn(echoPin, HIGH);
    distance = (distance / 2) / 29.1;
    return distance;
}
 
void loop() {
    long distance1, distance2, distance;
    distance1 = readDistance(echoPin1, trigPin1);
    distance2 = readDistance(echoPin2, trigPin2);
    distance = (distance1 + distance2) / 2;
    if(distance > minDistance && distance < maxDistance) {
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 0);
        lcd.print(distance);
        lcd.print(" cm");
        distance = map(distance, minDistance, maxDistance, maxFrequency, minFrequency);
        //Serial.println(distance);
        tone(buzzPin, distance);
    }
    else {
        lcd.setCursor(0, 0);
        lcd.print("Safe to proceed!");
        noTone(buzzPin);
    }
    delay(20);
}
