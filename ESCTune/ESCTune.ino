#include <Servo.h>

Servo tune;
Servo other1;
Servo other2;
Servo other3;

int value = 700;

void arm(){
  tune.writeMicroseconds(700);
  other1.writeMicroseconds(700);
  other2.writeMicroseconds(700);
  other3.writeMicroseconds(700);
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  tune.attach(3);
  other1.attach(5);
  other2.attach(6);
  other3.attach(9);
  Serial.begin(9600);
  arm();
}

void loop() {
  // put your main code here, to run repeatedly:
  tune.writeMicroseconds(value);
  Serial.println(value);
  
  if(Serial.available()) 
    value = Serial.parseInt();    // Parse an Integer from Serial
}
