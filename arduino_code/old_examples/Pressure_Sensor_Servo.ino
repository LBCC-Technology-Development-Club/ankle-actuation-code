
#include <Servo.h> // Including the servo library.

int servoPin = 9; // The right pin of our servo goes to pin 9. Make sure it goes to an analog pin.
int posServo = 0; // Declare our initial position for our servo. This will end up to be instantaneous.
int servoDelay = 25; //Servos need a delay in order to move.

Servo myServo;

int fsrAnalogPin = A0; // FSR is connected to analog 0
int LEDpin = 11;      // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  myServo.attach(servoPin); // Similar to pinMode but for Servo (attaches servo to pin servoPin)

}

void loop() {
  // put your main code here, to run repeatedly:
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);

  if(fsrReading < 7){
    myServo.write(5);
  }

  else{
    myServo.write(55);
  }
  
  delay(110);
  
}
