int apply_button = 2;

byte read_yaw_pin = 5; 
byte read_throttle_pin = 3;

int write_throttle_pin = 9;
int write_yaw_pin = 10;

int pwm_value_throttle;
int pwm_value_yaw;          

int transmitter_highest = 13;
int transmitter_high = 12;
int transmitter_medium = 11;
int transmitter_low = 7;
int transmitter_lowest = 6;

int throttle_signal = 4;
int yaw_signal = 2;

int write_signal = 100;

void setup() {  
  // put your setup code here, to run once:\\
  pinMode(read_yaw_pin, INPUT);
  pinMode(read_throttle_pin, INPUT);

  pinMode(write_throttle_pin, OUTPUT);
  pinMode(write_yaw_pin, OUTPUT);

  //PINS FOR TRANSMITTER
  pinMode(transmitter_highest, INPUT_PULLUP);           
  pinMode(transmitter_high, INPUT_PULLUP);           
  pinMode(transmitter_medium, INPUT_PULLUP);           
  pinMode(transmitter_low, INPUT_PULLUP);           
  pinMode(transmitter_lowest, INPUT_PULLUP); 

  //PINS FOR WRITE SIGNAL MODE
  pinMode(throttle_signal, INPUT_PULLUP);           
  pinMode(yaw_signal, INPUT_PULLUP);           

  
  Serial.begin(9600);
}

void loop() {
        delay(1000); 
        Serial.println();

        write_signal = 100;

        if (digitalRead(transmitter_highest) == HIGH)
        {
          write_signal = 250;
        }
        if (digitalRead(transmitter_high) == HIGH)
        {
          write_signal = 220;
        }
        if (digitalRead(transmitter_medium) == HIGH)
        {
          write_signal = 180;
        }
        if (digitalRead(transmitter_low) == HIGH)
        
        {
          write_signal = 150;
        }
        if (digitalRead(transmitter_lowest) == HIGH)
        {
          write_signal = 130;
        }
        
        if (digitalRead(throttle_signal) == HIGH)
        {
          analogWrite(write_throttle_pin, write_signal);
          pwm_value_throttle = pulseIn(read_throttle_pin, HIGH);
          Serial.println("Throttle Signal");
          Serial.println(pwm_value_throttle);
        }
        if (digitalRead(yaw_signal) == HIGH)
        {
          analogWrite(write_yaw_pin, write_signal);
          pwm_value_yaw = pulseIn(read_yaw_pin, HIGH);
          Serial.println("Yaw Signal");
          Serial.println(pwm_value_yaw);
        }
}
