
#include "DFRobot_DF2301Q.h"

#define sensorPin A0

#define enA 5
#define in1 6
#define in2 7

#define Bulb 13

DFRobot_DF2301Q_I2C asr;

void setup() 
{
  Serial.begin(115200);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(Bulb, OUTPUT);    
  digitalWrite(Bulb, LOW);  

  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
  asr.setVolume(7);
  asr.setMuteMode(0);
  asr.setWakeTime(50);
  uint8_t wakeTime = 0;
  wakeTime = asr.getWakeTime();
  Serial.print("wakeTime = ");
  Serial.println(wakeTime);
  asr.playByCMDID(1);
  
}

void loop() {

  Serial.print("Analog output: ");
  Serial.println(readSensor());
  delay(500);
  analogWrite(5, 100); //ENA pin

  uint8_t CMDID = asr.getCMDID();
  //Serial.println(CMDID);
  switch (CMDID) {
    case 103:                                                  //If the command is “Turn on the light”
      digitalWrite(Bulb, HIGH);                                 //Turn on the LED
      Serial.println("received'Turn on the light',command flag'103'");  //Serial transmits "received"Turn on the light",command flag"103
      break;

    case 104:                                                  //If the command is “Turn off the light”
      digitalWrite(Bulb, LOW);                                  //Turn off the LED
      Serial.println("received'Turn off the light',command flag'104'");  //The serial transmits "received"Turn off the light",command flag"104""
      break;

    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");  //Printing command ID
        Serial.println(CMDID);
      }
  }
  delay(300);
}

//  This function returns the analog data to calling function

int readSensor() {

  unsigned int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor

  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data

  if (outputValue > 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(20);
  }

    
  else
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(20);
  }

    

  return outputValue;             // Return analog moisture value

}
