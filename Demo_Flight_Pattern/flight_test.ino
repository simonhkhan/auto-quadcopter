int write_throttle_pin = 9;
int write_yaw_pin = 10;
int write_roll_pin = 5;
int write_pitch_pin = 6;


void setup() {  
  // put your setup code here, to run once:\\
  pinMode(write_throttle_pin, OUTPUT);
  pinMode(write_yaw_pin, OUTPUT);
  pinMode(write_roll_pin, OUTPUT);
  pinMode(write_pitch_pin, OUTPUT);
           

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Beginning flight pattern...");
  Serial.println("Entering flight arming...");
  int throttle_val;
  throttle_val = flight_arm();
  Serial.println("Entering stable mode...");
  stabilize_drone();
  delay(4000);
  Serial.println("Entering take-off...");
  flight_takeoff();
  delay(4000);
  Serial.println("Flight pattern...");
  flight_pattern();
  delay(4000);
  Serial.println("Entering landing...");
  flight_land(200);
  delay(4000);      
}


void stabilize_drone() {
    Serial.println("Stabilizing...");
    analogWrite(write_throttle_pin, 120);
    delay(500);
    analogWrite(write_yaw_pin, 140);
    delay(500);  
    analogWrite(write_roll_pin, 150);
    delay(500);
    analogWrite(write_pitch_pin, 150);
    delay(1500);
}

int flight_arm(){
  Serial.println("Flight arming...");
  int throttle_val = 120;
  analogWrite(write_throttle_pin, throttle_val);
  analogWrite(write_yaw_pin, 250);
  delay(3000);
  analogWrite(write_yaw_pin, 195);
  Serial.println("Arming complete.");
  return throttle_val;
}

void flight_takeoff(){
  Serial.println("Taking off...");
  int takeoff_value = 180;
  int current_throttle_val = 120;
  for(current_throttle_val; current_throttle_val < takeoff_value; current_throttle_val+=10){
      Serial.println(current_throttle_val);
  }
  Serial.println("Take off complete.");
}

void flight_pattern(){
  Serial.println("Flight pattern...");
  delay(5000);
  Serial.println("Flight complete.");
}

void flight_land(int current_throttle_val){
  Serial.println("Landing...");
  int landing_value = 120;
  for(landing_value; current_throttle_val > landing_value; current_throttle_val-=10){
    // write throttle value to throttle pin
    
    delay(50);
  }  
  Serial.println("Landing complete.");
}
