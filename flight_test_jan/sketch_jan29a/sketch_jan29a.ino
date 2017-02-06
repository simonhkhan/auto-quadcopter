byte read_yaw_pin = 5; 
byte read_throttle_pin = 3;

int yaw_pin_low = 13;
int yaw_pin_med = 12;
int yaw_pin_high = 4;

int throttle_pin_low = 8;
int throttle_pin_high = 7;

int write_throttle_pin = 9;
int write_yaw_pin = 10;
int write_high_pwm = 11;

int pwm_value_yaw;
int pwm_value_throttle;
int throttle_value = 100;
int yaw_value = 100;


void setup() {  
  // put your setup code here, to run once:\\
  pinMode(yaw_pin_high, INPUT);
  pinMode(yaw_pin_med, INPUT);
  pinMode(yaw_pin_low, INPUT);

  pinMode(write_high_pwm, INPUT);

  pinMode(read_yaw_pin, INPUT);
  pinMode(read_throttle_pin, INPUT);
  
  pinMode(write_throttle_pin, OUTPUT);
  pinMode(write_yaw_pin, OUTPUT);
  
  Serial.begin(57600);
}

void loop() {
   analogWrite(write_high_pwm, 240);


  if (digitalRead(yaw_pin_low) == LOW) { 
    yaw_value = 145;
  }
  else if (digitalRead(yaw_pin_med) == LOW) {
    yaw_value = 180;
  }
  else if (digitalRead(yaw_pin_high) == LOW) {
    yaw_value = 225;
  }
  else {
    yaw_value = 100;
  }

  if (digitalRead(throttle_pin_low) == LOW) { 
    throttle_value = 145;
  }
  else if (digitalRead(throttle_pin_high) == LOW) {
    throttle_value = 215;
  }
  else {
    throttle_value = 100;
  }
  
  analogWrite(write_throttle_pin, throttle_value);
  pwm_value_throttle = pulseIn(read_throttle_pin, HIGH);
  Serial.println("Throttle Signal");
  Serial.println(pwm_value_throttle);

  analogWrite(write_yaw_pin, yaw_value);
  pwm_value_yaw = pulseIn(read_yaw_pin, HIGH);
  Serial.println("Yaw Signal");
  Serial.println(pwm_value_yaw);

}
