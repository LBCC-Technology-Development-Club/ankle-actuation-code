 // Motor A

int enA = 9;
int in1 = 8;
int in2 = 7;
int x = 1;
int dT = 4000;

void setup() {
  // put your setup code here, to run once:

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(x != 0){

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 255);

  delay(dT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, 230);

  delay(dT/1.5);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 200);

  delay(dT/2);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, 175);

  delay(dT/2.5);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 150);

  delay(dT/3);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, 100);

  delay(dT/3.5);

  x = 0; 

  }

 analogWrite(enA, 0);


}
