int apply_button = 2;

byte read_yaw_pin = 5; 
byte read_throttle_pin = 3;

int write_throttle_pin = 9;
int write_yaw_pin = 10;

int pwm_value_throttle;
int pwm_value_yaw;
int pwm_motor_val;          

byte read_motor_val = 11;

int throttle_signal = 4;
int yaw_signal = 2;

//int write_signal = 100;

int readPotValue() {
    int sensorValue = analogRead(A0);
    int mappedValue = map(sensorValue, 0, 1001, 100, 255);
    return mappedValue;
}


void writeSignalValues(int write_signal) {
  
      if (digitalRead(throttle_signal) == HIGH)
      {
        analogWrite(write_throttle_pin, write_signal);
        pwm_value_throttle = pulseIn(read_throttle_pin, HIGH);
        Serial.println("Throttle Signal");
        Serial.println(pwm_value_throttle);
        Serial.println(write_signal);

      }
      if (digitalRead(yaw_signal) == HIGH)
      {
        analogWrite(write_yaw_pin, write_signal);
        pwm_value_yaw = pulseIn(read_yaw_pin, HIGH);
        Serial.println("Yaw Signal");
        Serial.println(pwm_value_yaw);
        Serial.println(write_signal);

      }
}

void setup() {  
  // put your setup code here, to run once:\\
  pinMode(read_yaw_pin, INPUT);
  pinMode(read_throttle_pin, INPUT);
  pinMode(read_motor_val, INPUT);


  pinMode(write_throttle_pin, OUTPUT);
  pinMode(write_yaw_pin, OUTPUT);

  //PINS FOR WRITE SIGNAL MODE
  pinMode(throttle_signal, INPUT_PULLUP);           
  pinMode(yaw_signal, INPUT_PULLUP);           

  Serial.begin(9600);
}

void loop() {
        Serial.println();
        delay(500);

        int write_signal = readPotValue();

        writeSignalValues(write_signal);

//        pwm_motor_val = pulseIn(read_motor_val, HIGH);
//        Serial.println("Motor Value");
//        Serial.println(pwm_motor_val);
        
}
