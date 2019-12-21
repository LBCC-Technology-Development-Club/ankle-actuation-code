#include <motor.h>

struct motor motor1;
motor1.EN = 9;
motor1.IN1 = 8;
motor1.IN2 = 7;


struct motor motor2;
motor2.EN = 1;
motor2.IN1 = 2;
motor2.IN2 = 3;





potentiometer = 10;

pressureSensor1 = 6;
pressureSensor2 = 5;

void setup() {
  pinMode(motor1.EN, OUTPUT);
  pinMode(motor1.IN1, OUTPUT);
  pinMode(motor1.IN2, OUTPUT);
  
  pinMode(potentiometer, INPUT);
  
  pinMode(pressureSensor1, INPUT);
  pinMode(pressureSensor2, INPUT);
}

void loop() {
  
  if(analogRead(pressureSensor1) == 0 && analogRead(pressureSensor2) == 0) {
    motor1.analog_speed = 0;
    motor_clockwise(motor1);
  }
  else if (analogRead(pressureSensor1) != 0 && analogRead(pressureSensor2) == 0) {
    motor1.analog_speed = 150;
    motor_clockwise(motor1);
  }
  else if (analogRead(pressureSensor1) != 0 && analogRead(pressureSensor2) != 0) {
    motor1.analog_speed = 0;
    motor_clockwise(motor1);
  }
 

}

void motor_clockwise(struct motor motor) {
  digitalWrite(motor.IN1, HIGH);
  digitalWrite(motor.IN2, LOW);
  analogWrite(motor.EN, motor.analog_speed);
}

void motor_counterclockwise(struct motor motor) {
  digitalWrite(motor.IN1, LOW);
  digitalWrite(motor.IN2, HIGH);
  analogWrite(motor.EN, motor.analog_speed);
}

