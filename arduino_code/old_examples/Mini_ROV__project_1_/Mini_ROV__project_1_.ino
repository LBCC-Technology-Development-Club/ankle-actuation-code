// Jonathan Walter Landers
// This code controls the JWL Mini ROV.
// For use with the ARDUINO MEGA
// Pressure sensor: determines if the ROV is rising or sinking
// RGB LED: if red - sinking, if green - rising, if blue - neutral,
// Two motors are at the back of the craft in parallel; Spin together for forward/backward movement, Spin at different rates or different directions for turning movement,
// One motor in the center of the craft; Controls the upward and downward motion of the ROV.
// Three potentiometers to control the motors


///Pressure Sensor
//modified from  http://minirov.info/ []
int PS = 1;
int previous;
int PSvalue;       
///LED
int LEDr = 22;
int LEDg = 23;
int LEDb = 24;
///Potentiometers (1 for each motor)
float PotentAa = 2;    //Analog2
float PotentBa = 3;    //Analog3
float PotentAb = 4;    //Analog4
float PotentAavalue;
float PotentBavalue;
float PotentAbvalue;
///Motor Driver a - forwards, backwards, rotate left, rotate right
int speed;
//STBYa to AIN2b is modified from http://minirov.info/ []
int STBYa = 10;                                                      
int PWMAa = 13; 
int AIN1a = 11;
int AIN2a = 12; 
int PWMBa = 9; 
int BIN1a = 8; 
int BIN2a = 7;                                                      
///Motor Driver b - up, down
int STBYb = 3;
int PWMAb = 6;
int AIN1b = 5;
int AIN2b = 4;


void setup() {
  // Unless otherwise stated, this section is modified from  http://minirov.info/ [].
  // Accessed nnnnnnnn
  Serial.begin(9600);    
  pinMode(PS,  INPUT); 
  // The LED pinModes were modified from  http://minirov.info/ [] or https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/ [].
  // Last Accessed: nnnnnnnnnnnnn
  pinMode(LEDr, OUTPUT);
  pinMode(LEDg, OUTPUT);
  pinMode(LEDb, OUTPUT);
  // The following potetiometer outputs were modified from 24 hours nnnnnnnnnnnnnnnnnnnnnnnnnn[].
  pinMode(PotentAa, INPUT);
  pinMode(PotentBa, INPUT);
  pinMode(PotentAb, INPUT);
  pinMode(STBYa, OUTPUT); 
  pinMode(PWMAa, OUTPUT); 
  pinMode(AIN1a, OUTPUT); 
  pinMode(AIN2a, OUTPUT); 
  pinMode(PWMBa, OUTPUT); 
  pinMode(BIN1a, OUTPUT);   
  pinMode(BIN2a, OUTPUT);
  pinMode(STBYb, OUTPUT); 
  pinMode(PWMAb, OUTPUT); 
  pinMode(AIN1b, OUTPUT);   
  pinMode(AIN2b, OUTPUT); 
  digitalWrite(STBYa, HIGH);
  digitalWrite(STBYb, HIGH);
  // The line below was added by Srikar Valluri [].
  previous = analogRead(PS); 
}


void loop() {
  /// Pressure Sensor
  PSvalue = analogRead(PS);       
  Serial.println(PSvalue);  
  /// LED
  // The LED () is modified from:https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/ []
  // Last Accessed: nnnnnnnnnnn    
  // 24 hours for else if and else statements nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn[]
  if(previous < (PSvalue - 5)){
    LED(255,0,0);
  }
  else if((previous - 5) > PSvalue ){                          
    LED(0,255,0);
  }
  else{
    LED(0,0,255);
  }
  /// Motors
  PotentAavalue = analogRead(PotentAa);
  Serial.println(PotentAavalue);
  PotentBavalue = analogRead(PotentBa);
  PotentAbvalue = analogRead(PotentAb);
  move(PotentAa, PotentAavalue);
  move(PotentBa, PotentBavalue);
  move(PotentAb, PotentAbvalue);
  /// Reset Pressure Sensor Value
  // Was added by Srikar Valluri [].
  previous = PSvalue;    
  delay(500);
}


// Void LED function was modified from https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/ [].
// Last Accessed:nnnnnnnnnnnnnnnnnn
void LED(int LEDrvalue, int LEDgvalue, int LEDbvalue){  
  analogWrite (LEDr, LEDrvalue);
  analogWrite (LEDg, LEDgvalue);
  analogWrite (LEDb, LEDbvalue);                       
}


void move( float potentname, float potentvalue){  
  // Joseph Jess [] turned all of the following numerical values into float values by adding .0 to the end of all integer numbers [].  
  if(potentname == PotentAa){
    if(potentvalue < 481.5){
      speed = (abs(potentvalue - 481.5)) / (321.0 / 170.0); 
      digitalWrite(AIN1a, HIGH);
      digitalWrite(AIN2a, LOW);
      analogWrite(PWMAa, speed);
    }
    if(potentvalue > 541.5){
      speed = (potentvalue - 541.5) / (321.0 / 170.0);
      digitalWrite(AIN1a, LOW);
      digitalWrite(AIN2a, HIGH);
      analogWrite(PWMAa, speed);
   }
   // The format (potentvalue > 481.5) && (potentvalue < 541.5) was edited by Srikar Valuri [].
   if((potentvalue > 481.5) && (potentvalue < 541.5)){ 
      digitalWrite(AIN1a, LOW);
      digitalWrite(AIN2a, HIGH);
      analogWrite(PWMAa, 0);
    }
  }
  if(potentname == PotentBa){
    if(potentvalue < 481.5){
      speed = (abs(potentvalue - 481.5)) / (321.0 / 170.0);
      digitalWrite(BIN1a, HIGH);
      digitalWrite(BIN2a, LOW);
      analogWrite(PWMBa, speed);
    }
    if(potentvalue > 541.5){
      speed = ( potentvalue - 541.5) / (321.0 / 170.0);
      digitalWrite(BIN1a, LOW);
      digitalWrite(BIN2a, HIGH);
      analogWrite(PWMBa, speed);
    }
    if(potentvalue > 481.5 && potentvalue < 541.5){
     digitalWrite(BIN1a, LOW);
     digitalWrite(BIN2a, HIGH);
     analogWrite(PWMBa, 0);
    }
  }
  if(potentname == PotentAb){
    if(potentvalue < 481.5){
      speed = (abs(potentvalue - 481.5)) / (321.0 / 170.0);
      digitalWrite(AIN1b, HIGH);
      digitalWrite(AIN2b, LOW);
      analogWrite(PWMAb, speed);
    }
    if(potentvalue > 541.5){
      speed = ( potentvalue - 541.5) / (321.0 / 170.0);
      digitalWrite(AIN1b, LOW);
      digitalWrite(AIN2b, HIGH);
      analogWrite(PWMAb, speed);
    }
    if(potentvalue > 481.5 && potentvalue < 541.5){
      digitalWrite(AIN1b, LOW);
      digitalWrite(AIN1b, HIGH);
      analogWrite(PWMAb,0);
    }
  }
}
