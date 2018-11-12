/********************************************************************************
Author: Bradford Henson
Date: 3/30/2018
Version: 1.0.0
License: USE AT YOUR OWN RISK
-------------------------------------



********************************************************************************/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
 
String command = ""; // Stores response of the HC-06 Bluetooth device

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motorOne = AFMS.getMotor(1);
Adafruit_DCMotor *motorTwo = AFMS.getMotor(2);
Adafruit_DCMotor *motorThree = AFMS.getMotor(3);
Adafruit_DCMotor *motorFour = AFMS.getMotor(4);

/********************************************************************************

                            FUNCTIONS SECTION

********************************************************************************/
void moveBackward(){
  motorOne->run(FORWARD);
  motorTwo->run(FORWARD);
  motorThree->run(FORWARD);
  motorFour->run(FORWARD);  
}

void moveForward(){
  motorOne->run(BACKWARD);
  motorTwo->run(BACKWARD);
  motorThree->run(BACKWARD);
  motorFour->run(BACKWARD);  
}

void turnRight(){
  motorOne->run(BACKWARD);
  motorTwo->run(FORWARD);
  motorThree->run(FORWARD);
  motorFour->run(BACKWARD);
  delay(100);
  motorOne->run(RELEASE);
  motorTwo->run(RELEASE);
  motorThree->run(RELEASE);
  motorFour->run(RELEASE); 
}

void turnLeft(){
  motorOne->run(FORWARD);
  motorTwo->run(BACKWARD);
  motorThree->run(BACKWARD);
  motorFour->run(FORWARD);
  delay(100);
  motorOne->run(RELEASE);
  motorTwo->run(RELEASE);
  motorThree->run(RELEASE);
  motorFour->run(RELEASE); 
}

void stopMovement(){
  motorOne->run(RELEASE);
  motorTwo->run(RELEASE);
  motorThree->run(RELEASE);
  motorFour->run(RELEASE);  
}

/********************************************************************************

                            SETUP SECTION

********************************************************************************/
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  Serial.println("Type AT commands!");
  
  // The HC-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
 int i = 150; 
 motorOne->setSpeed(i);
 motorTwo->setSpeed(i);
 motorThree->setSpeed(i);
 motorFour->setSpeed(i);
}
/********************************************************************************

                                EVENT LOOP

********************************************************************************/ 
void loop() {
  
  if (mySerial.available()) {
    while(mySerial.available()) { // While there is more to be read, keep reading.
      command += (char)mySerial.read();
    }
    
    Serial.println(command);
    if(command == "u") moveForward();
    if(command == "d") moveBackward();
    if(command == "r") turnRight();
    if(command == "l") turnLeft();
    if(command == "s") stopMovement();
    command = ""; // No repeats
  }
  
  // Read user input if available.
  if (Serial.available()){
    delay(10); // The delay is necessary to get this working!
    mySerial.write(Serial.read());

  }


}









