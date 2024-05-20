#include <Servo.h>
Servo myservo;
const int inputPin = 5; // Adjust the pin according to your setup
const int inputPins = 11; // Adjust the pin according to your setup
int pos = 90;    
int precpos = 0;
int numprec = 0;
int volte = 0;
int receivedNumber = 0;

void setup() {
  pinMode(inputPin, INPUT); // Set the pin as an input
  pinMode(inputPins, INPUT); // Set the pin as an input
  Serial.begin(9600); // Start serial communication at 9600 baud
  myservo.attach(9);
}

void loop() {
  receivedNumber = 0;
  for (int i = 0; i < 8; i++) {
    receivedNumber |= digitalRead(inputPin) << i; // Read bits and reconstruct the number
    delay(100); // Adjust this delay based on the transmission speed from Nicla Vision
  }

  Serial.print("Received number: ");
  Serial.println(receivedNumber); // Print the received number
  Serial.println(numprec); // Print the received number
  Serial.println(precpos); // Print the received number
  
  if(precpos > 90){
    for (pos = precpos; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);     
  }
  }
  if(precpos < 90){
    for (pos = precpos; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);     
  }
  }
  precpos = pos;
  delay(1000);
  
  if(volte == 5){
    receivedNumber = 100;
  }
  if(receivedNumber != numprec){
    volte = 0;
    if(receivedNumber == 0){
        for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15 ms for the servo to reach the position
      }
      precpos = pos;
      delay(10000);
    }
    if(receivedNumber == 255){
        for (pos = 90; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15 ms for the servo to reach the position
      }
      precpos = pos;
      delay(10000);
    }
    numprec = receivedNumber;
  }
    volte++;
  }