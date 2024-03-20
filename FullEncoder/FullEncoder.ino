#include <SoftwareSerial.h>
#include <Servo.h>

// Create servo
Servo servo();

// Servo starts and ends
const int servoStart = 10;
const int servoEnd = 169;

// Output pins
const int firePin = 5;

const int bridge1Pin1 = 11;
const int bridge1Pin2 = 12;

const int bridge2Pin1 = 7;
const int bridge2Pin2 = 8;

SoftwareSerial Slave(2,3);
int num;

void setup() {
  Serial.begin(9600);
  Slave.begin(38400);

  servo.attach(firePin);
  servo.write(servoStart);
}

void loop() {
  
  if (Serial.available() > 0) {
    num = Slave.read();

  }
  else {
    num = 234;
  }
  
  // Servo control
  if (num > 100 && num < 200) {
    servo.write(servoEnd);

  } 
  else {
    servo.write(servoStart);

  } 


  // Run for H-Bridge 2 on all combinations
  Find2Digit(num, 1, bridge2Pin1, true);
  Find2Digit(num, 1, bridge2Pin2, false);

  Find2Digit(num, 2, bridge2Pin1, false);
  Find2Digit(num, 2, bridge2Pin2, true);

  Find2Digit(num, 3, bridge2Pin1, true);
  Find2Digit(num, 3, bridge2Pin2, true);


  // Run for H-Bridge 1 on all combinations
  Find3Digit(num, 8, bridge1Pin1, true);
  Find3Digit(num, 8, bridge1Pin2, false);

  Find3Digit(num, 6, bridge1Pin1, false);
  Find3Digit(num, 6, bridge1Pin2, true);

  Find3Digit(num, 4, bridge1Pin1, true);
  Find3Digit(num, 4, bridge1Pin2, true);
  
}


void Find2Digit(int pureNum ,int Digit, int pinNumber, bool isOpposite) 
{
  int pureNumHun = floor(pureNum / 100);
  int num = (pureNum - (pureNumHun * 100));
  
  if (num < ((Digit * 10) + 10) && num >= (Digit * 10)) {
    if (isOpposite == false) {
      pinMode(pinNumber,OUTPUT);
      digitalWrite(pinNumber, HIGH);
    }
    else if (isOpposite == true) {
      pinMode(pinNumber,OUTPUT);
      digitalWrite(pinNumber, LOW);
    }
  }
  else {

  }
}

void Find3Digit(int pureNum ,int Digit, int pinNumber, bool isOpposite) 
{
  int pureNumTen = floor(pureNum / 10);
  int num = pureNum - (pureNumTen * 10);
  
  if (num == Digit) {
    if (isOpposite == false) {
      pinMode(pinNumber,OUTPUT);
      digitalWrite(pinNumber, HIGH);
    }
    else if (isOpposite == true) {
      digitalWrite(pinNumber, LOW);
    }
  }
  else {

  }
}





