#include <Keypad.h>
#include <Servo.h>

Servo doorLock;

// Keypad Setup
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int servoPin = 10;
int greenLED = 11;
int redLED = 12;
int buzzer = 13;

String secretCode = "1234";
String enteredCode = "";

void setup() {
  doorLock.attach(servoPin);
  doorLock.write(90); // 90 tells a continuous servo to STOP
  
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    enteredCode += key;
    
    if (enteredCode.length() == 4) {
      if (enteredCode == secretCode) {
        // Code is CORRECT
        digitalWrite(greenLED, HIGH);
        
        // Spin to unlock
        doorLock.write(180); // Spin one way
        delay(500);          // Spin for half a second
        doorLock.write(90);  // STOP the motor
        
        delay(3000);         // Keep door unlocked for 3 seconds
        
        // Spin to lock
        doorLock.write(0);   // Spin the other way
        delay(500);          // Spin for half a second
        doorLock.write(90);  // STOP the motor
        
        digitalWrite(greenLED, LOW);
      } else {
        // Code is WRONG
        digitalWrite(redLED, HIGH);
        tone(buzzer, 1000);
        delay(1000);
        noTone(buzzer);
        digitalWrite(redLED, LOW);
      }
      enteredCode = ""; 
    }
  }
}