
// Choose pins for each output
int throttle_pin = 0;
int yaw_pin = 0;
int pitch_pin = 0;
int roll_pin = 0;

// Idle speed
int motor_startup = 1210;


/* 
 The following are values we want for flight
 In this case, we are just doing a take-off and landing
 So we only need throttle value for hovering at approximately 3-4ft.
 The rest can stay at a constant value
 */

int throttle_value = 0;
int yaw_value = 0;
int pitch_value = 0;
int roll_value = 0;



void setup() {
  // put your setup code here, to run once:
  throttle.attach(throttle_pin);
  yaw.attach(yaw_pin);
  pitch.attach(pitch_pin);
  roll.attach(roll_pin);

  Serial.begin(9600);
  Serial.println("Setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Beginning flight pattern...");
  Serial.println("Entering flight arming...");
  flight_arm();
  Serial.println("Entering take-off...");
  flight_takeoff();
  Serial.println("Flight pattern...");
  flight_pattern();
  Serial.println("Entering landing...");
  flight_land();
  
}

void flight_arm(){
  Serial.println("Flight arming...");
  analogWrite(throttle_pin, 120);
  analogWrite(yaw_pin, 250);
  delay(3000);
  analogWrite(yaw_pin, 195);
  Serial.println("Arming complete.");
}

void flight_takeoff(){
  Serial.println("Taking off...");
  int takeoff_value = 1400;
  for(throttle_value; throttle_value < takeoff_value; throttle_value+=10){
    // write throttle value to throttle pin
    
    delay(50);
  }
  Serial.println("Take off complete.");
}

void flight_pattern(){
  Serial.println("Flight pattern...");
  delay(5000);
  Serial.println("Flight complete.");
}

void flight_land(){
  Serial.println("Landing...");
  int landing_value = motor_startup;
  for(throttle_value; throttle_value > landing_value; throttle_value-=10){
    // write throttle value to throttle pin
    
    delay(50);
  }  
  Serial.println("Landing complete.");
}

