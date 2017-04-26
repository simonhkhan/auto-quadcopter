#include <SPI.h>
#include <BLEPeripheral.h>
#define LED 3
#define BUTTON 4
#define BREQ 10
#define BRDY 2
#define BRST 9

int cState;
int dState;
int switchState = 0;
int ledState = 0;


BLEPeripheral blePeripheral= BLEPeripheral(BREQ, BRDY, BRST);
BLEService lightswitch = BLEService("FF10");

BLECharCharacteristic switchCharacteristic= BLECharCharacteristic("FF11", BLERead | BLEWrite);
BLEDescriptor switchDescriptor = BLEDescriptor("2901", "Switch");


BLECharCharacteristic stateCharacteristic= BLECharCharacteristic("FF12", BLENotify);
BLEDescriptor stateDescriptor = BLEDescriptor("2901", "State");

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  blePeripheral.setLocalName("LED Switch");
  blePeripheral.setDeviceName("TrialProject");
  blePeripheral.setAdvertisedServiceUuid(lightswitch.uuid());
  blePeripheral.addAttribute(lightswitch);
  blePeripheral.addAttribute(switchCharacteristic);
  blePeripheral.addAttribute(switchDescriptor);
  blePeripheral.addAttribute(stateCharacteristic);
  blePeripheral.addAttribute(stateDescriptor);
  switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);

  blePeripheral.begin();
  Serial.println(F("TrialProject"));


}

void loop() {
  // put your main code here, to run repeatedly:
  blePeripheral.poll();
  cState=digitalRead(BUTTON);
  delay(10);
  dState = digitalRead(BUTTON);
  if (cState != switchState) {
    if(cState == dState) {
      if( cState == LOW ) {
        // Button just released
      
      else {
        Serial.println("Button event, pressed.");
        if( ledState == 0 ){
        switchCharacteristic.setValue(1);
        stateCharacteristic.setValue(1);
        digitalWrite(LED_PIN, HIGH);
        ledState=1;
        }
        else {
        switchCharacteristic.setValue(0);
        stateCharacteristic.setValue(0);
        digitalWrite(LED, LOW);
        ledState=0;
        }
      }
      switchState = cState;
    }
  }

}

void switchCharacteristicWritten(BLECentral & central, BLECharacteristic & switchCharacteristic) {
  if ( switchCharacteristic.value() ){
    Serial.println(F("ON"));
    digitalWrite( LED, HIGH );
    ledState = 1;
    stateCharacteristic.setValue(1);
  }
  else {
    Serial.println(F("OFF"));
    digitalWrite( LED, LOW );
    ledState = 0;
    stateCharacteristic.setValue(0);
  }
  
}

