int write_throttle_pin = 9;
int write_yaw_pin = 10;
int write_roll_pin = 3;
int write_pitch_pin = 6;

byte pwm_pin = 11;
int pwm_value;

bool flight_complete = false;

//Interrupt pin - Can only be changed to 2 or 3.
const byte interruptPin = 2;
volatile byte state = LOW;

void interrupt_service(){
      Serial.println("INTERRUPT");
      //analogWrite(write_throttle_pin, 120); // force to drone to lower throttle values
      flight_disarm();
      while (true) {
        Serial.println("infinite");
      }

  }


void setup() {  
  // put your setup code here, to run once:\\
  pinMode(pwm_pin, INPUT);
  pinMode(write_throttle_pin, OUTPUT);
  pinMode(write_yaw_pin, OUTPUT);
  pinMode(write_roll_pin, OUTPUT);
  pinMode(write_pitch_pin, OUTPUT);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt_service, HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(!flight_complete){
    Serial.println("Beginning flight sequence...");
    delay(10000);
    
    Serial.println("Entering flight arming...");
    int throttle_val;
    throttle_val = flight_arm();
    delay(4000);

    Serial.println("Entering stable mode...");
    stabilize_drone();
    delay(4000);

    Serial.println("Entering taxi method...");
    taxi(throttle_val);
    delay(4000);
    
    Serial.println("Entering take-off...");
    throttle_val = flight_takeoff(throttle_val);
//    delay(4000);
    
    Serial.println("Flight pattern...");
    flight_pattern();
//    delay(4000);
    
    Serial.println("Entering landing...");
    flight_land(throttle_val);
    delay(4000);  
    flight_complete = true;
    Serial.println("Flight complete");

    flight_disarm();
  }
  
      
}

int taxi(int current_throttle_val) {
  Serial.println("Taking off...");
  int takeoff_value = 170;
  
  for(current_throttle_val; current_throttle_val < takeoff_value; current_throttle_val+=5){
    analogWrite(write_throttle_pin, current_throttle_val);
    delay(400);
  }
  Serial.println("Take off complete.");
  return current_throttle_val;
  
}

int flight_arm(){
  Serial.println("Flight arming...");
  int throttle_val = 120;
  analogWrite(write_throttle_pin, throttle_val);
  analogWrite(write_yaw_pin, 250);
  delay(3000);
  Serial.println("Arming complete.");
  return throttle_val;
}

int flight_disarm(){
  Serial.println("Flight disarming...");
  int throttle_val = 120;
  analogWrite(write_throttle_pin, throttle_val);
  analogWrite(write_yaw_pin, 120);
  delay(3000);
  Serial.println("Disarming complete.");
  return throttle_val;
}

void stabilize_drone() {
    Serial.println("Stabilizing...");
    analogWrite(write_yaw_pin, 190);
    delay(5000);  
    analogWrite(write_roll_pin, 100);
    delay(5000);
    analogWrite(write_pitch_pin, 100);
    delay(5000);
//    return throttle_val;
}

int flight_takeoff(int current_throttle_val){
  Serial.println("Taking off...");
  int takeoff_value = 184;
  
  for(current_throttle_val; current_throttle_val < takeoff_value; current_throttle_val+=5){
      pwm_value = pulseIn(pwm_pin, HIGH);
      Serial.println(pwm_value);
      if (int(pwm_value) >= 1200) {
        interrupt_service();
      }
      else {
        analogWrite(write_throttle_pin, current_throttle_val);
        delay(50);      
      }
  }
  Serial.println("Take off complete.");
  return current_throttle_val;
  
}

void flight_pattern(){
  Serial.println("Flight pattern...");
//  analogWrite(write_pitch_pin, 160);
  for (int i = 0; i < 100; i++) {
      pwm_value = pulseIn(pwm_pin, HIGH);
      Serial.println(pwm_value);
      if (int(pwm_value) >= 1200) {
        interrupt_service();
      }
      else {
        delay(50);      
      }
  }
//  delay(5000);
  Serial.println("Flight complete.");
}

void flight_land(int current_throttle_val){
  Serial.println("Landing...");
  int landing_value = 120;
  for(landing_value; current_throttle_val > landing_value; current_throttle_val-=10){
    analogWrite(write_throttle_pin, current_throttle_val);
    delay(50);
  }  
  Serial.println("Landing complete.");
}
