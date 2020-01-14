struct motor {
  // Ports
  int EN;
  int IN1;
  int IN2;
  
  //Speed
  float analog_speed;
};

motor motor1 = {9, 8, 7, 0};



//struct motor motor2;
//motor2.EN = 1;
//motor2.IN1 = 2;
//motor2.IN2 = 3;





//potentiometer = 10;

int pressureSensor1 = A0;
int pressureSensor2 = A1;

void setup() {
  Serial.begin(9600);
  pinMode(motor1.EN, OUTPUT);
  pinMode(motor1.IN1, OUTPUT);
  pinMode(motor1.IN2, OUTPUT);
  
//  pinMode(potentiometer, INPUT);
  
  pinMode(pressureSensor1, INPUT);
  pinMode(pressureSensor2, INPUT);
}

void loop() {
  Serial.print("PressureSensor1: ");
  Serial.println(analogRead(pressureSensor1));
  Serial.print("PressureSensor2: ");
  Serial.println(analogRead(pressureSensor2));  
  if(analogRead(pressureSensor1) == 0 && analogRead(pressureSensor2) == 0) {
    motor1.analog_speed = 0;
    motor_clockwise(motor1);
  }
  else if (analogRead(pressureSensor1) != 0 && analogRead(pressureSensor2) == 0) {
    motor1.analog_speed = 150;
    motor_clockwise(motor1);
  }
  else if (analogRead(pressureSensor1) == 0 && analogRead(pressureSensor2) != 0) {
    motor1.analog_speed = -150;
    motor_counterclockwise(motor1);
  }
 delay(15);

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

