//byte read_free_pwm_signal = 11;
//int pwm_free_signal;          

int write_throttle_pin = 9;
int write_yaw_pin = 10;
int write_roll_pin = 5;
int write_pitch_pin = 3;


int throttle_signal = 4;
int yaw_signal = 2;
int roll_signal = 7;
int pitch_signal = 13;

int readPotValue() {
    int sensorValue = analogRead(A0);
    int mappedValue = map(sensorValue, 0, 1001, 100, 255);
    return mappedValue;
}

void armMotors() {
  Serial.println("arming");
  analogWrite(write_throttle_pin, 120);
  analogWrite(write_yaw_pin, 250);
  delay(3000);
  analogWrite(write_yaw_pin, 195);
  Serial.println("armed");
}


void writeSignalValues(int write_signal) {
  
      if (digitalRead(throttle_signal) == HIGH)
      {
        analogWrite(write_throttle_pin, write_signal);
        Serial.println("Throttle Signal");
        Serial.println(write_signal);

      }
      if (digitalRead(yaw_signal) == HIGH)
      {
        analogWrite(write_yaw_pin, write_signal);
        Serial.println("Yaw Signal");
        Serial.println(write_signal);

      }
//      if (digitalRead(roll_signal) == HIGH)
//      {
//        analogWrite(write_roll_pin, write_signal);
//        Serial.println("Roll Signal");
//        Serial.println(write_signal);
//
//      }
      if (digitalRead(pitch_signal) == HIGH)
      {
        analogWrite(write_pitch_pin, write_signal);
        Serial.println("Pitch Signal");
        Serial.println(write_signal);

      }
}

void setup() {  
//        pinMode(read_free_pwm_signal, INPUT);
      
        pinMode(write_throttle_pin, OUTPUT);
        pinMode(write_yaw_pin, OUTPUT);
        pinMode(write_roll_pin, OUTPUT);
        pinMode(write_pitch_pin, OUTPUT);
      
        //PINS FOR WRITE SIGNAL MODE
        pinMode(throttle_signal, INPUT_PULLUP);           
        pinMode(yaw_signal, INPUT_PULLUP);           
        pinMode(roll_signal, INPUT_PULLUP);           
        pinMode(pitch_signal, INPUT_PULLUP);           
      
        Serial.begin(9600);

        Serial.println();
        delay(8000);
        armMotors();
        delay(5000);
}

void loop() {        
        int write_signal = readPotValue();

        writeSignalValues(write_signal);
//
//        pwm_free_signal = pulseIn(read_free_pwm_signal, HIGH);
//        Serial.println("Free PWM Signal");
//        Serial.println(pwm_free_signal);
        
}
