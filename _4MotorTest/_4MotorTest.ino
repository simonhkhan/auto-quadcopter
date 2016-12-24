#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
int mon = 12;
int value = 700;


void arm(){
  motor1.writeMicroseconds(700);
  motor2.writeMicroseconds(700);
  motor3.writeMicroseconds(700);
  motor4.writeMicroseconds(700);
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  motor1.attach(3);
  motor2.attach(5);
  motor3.attach(6);
  motor4.attach(9);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  arm();
}

// Lift off at 1235

void loop() {
  // put your main code here, to run repeatedly:
  int switchState = digitalRead(12);
  if(switchState == 1){
    motor1.writeMicroseconds(value);
    motor2.writeMicroseconds(value);
    motor3.writeMicroseconds(value + 5);
    motor4.writeMicroseconds(value + 5);
  }
  else{
//    motor1.writeMicroseconds(1180);
    int speed;
    if (value >= 1185){
      speed = value - (value % 5);
      for(speed; speed > 1175; speed -= 5){
        motor1.writeMicroseconds(speed);
        motor2.writeMicroseconds(speed);
        motor3.writeMicroseconds(speed);
        motor4.writeMicroseconds(speed);
        Serial.println(speed);
        delay(100);
      }
      motor1.writeMicroseconds(700);
      motor2.writeMicroseconds(700);
      motor3.writeMicroseconds(700);
      motor4.writeMicroseconds(700);
      value = speed;
    }
  }
  
  Serial.println(value);
  Serial.println(switchState);
  
  if(Serial.available()) 
    value = Serial.parseInt();    // Parse an Integer from Serial
}
