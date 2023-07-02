#include <Servo.h>
Servo motor;
Servo motordir;

const int eco = 12;
const int trigger = 13;
const int RDA = 3;
const int RDB = 1;
const int VA1 = 6;
const int VA2 = 7;
const int VA3 = 8;
const int VA4 = 9;


const int carspeed = 150; // Adjusted maximum speed

int rightdistance = 0;
int leftdistance = 0;
int middledistance = 0;

// Function to move the robot forward
void forward() {
  motordir.write(89);
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, HIGH);
  digitalWrite(VA2, LOW);
  digitalWrite(VA3, LOW);
  digitalWrite(VA4, HIGH);
  Serial.println("Forward");
}

// Function to move the robot backward
void back() {
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, LOW);
  digitalWrite(VA2, HIGH);
  digitalWrite(VA3, HIGH);
  digitalWrite(VA4, LOW);
  Serial.println("Back");
}

// Function to turn the robot left
void left() {
  motordir.write(130); // Ayuda a mover las direccionales hacia la izquierda
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, LOW);
  digitalWrite(VA2, HIGH);
  digitalWrite(VA3, LOW);
  digitalWrite(VA4, HIGH);
  Serial.println("Left");
}

// Function to turn the robot right
void right() {
  motordir.write(80); // Ayuda a mover las direccionales hacia la izquierda
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, HIGH);
  digitalWrite(VA2, LOW);
  digitalWrite(VA3, HIGH);
  digitalWrite(VA4, LOW);
  Serial.println("Right");
}

// Function to stop the robot
void stop() {
  digitalWrite(RDA, LOW);
  digitalWrite(RDB, LOW);
  Serial.println("Stop");
}

void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(RDA, OUTPUT);
  pinMode(RDB, OUTPUT);
  pinMode(VA1, OUTPUT);
  pinMode(VA2, OUTPUT);
  pinMode(VA3, OUTPUT);
  pinMode(VA4, OUTPUT);
  motor.attach(10);
  motordir.attach(11);
  motor.write(88);
  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long time = pulseIn(eco, HIGH);
  int distance = (time * 0.034) / 2;
  return distance;
}

bool boutto() {
  int distance = getDistance();
  if (distance != -1 && distance <= 10) {
    return true;
  }
  return false;
}

void slowvelocity() {
  int distance = getDistance();
  if (distance != -1 && distance <= 30) {
    int speed = map(distance, 0, 30, 0, carspeed);
    analogWrite(RDA, speed);
    analogWrite(RDB, speed);
  }
}

void randomTurn() {
  int way = random(0, 3);
  if (way == 0) {
    left();
    delay(200);
    slowvelocity();
  } else if (way == 1) {
    right();
    delay(200);
    slowvelocity();
  } else {
  back();
  delay(190);
  }
}

void loop() {
  
  middledistance = getDistance();

  if (middledistance <= 9) {
    stop();
    
  } else {
  forward();
  delay(200);
  }

motor.write(165);
  rightdistance = getDistance();
  delay(500);
  
  motor.write(20);
  leftdistance = getDistance();
  delay(500);
  
  if (rightdistance > leftdistance) {
    right();
    delay(300);
    slowvelocity();
    
  } else if (rightdistance < leftdistance) {
    left();
    delay(300);
    slowvelocity();
  } else if ((rightdistance <= 8) && (leftdistance <= 8)) {
    stop();
    
  } else {
    forward();
    delay(300);
  }

if (rightdistance <= 10 && leftdistance <= 10 && middledistance <= 10) {
back();
delay(100);
}

  if (boutto()) {
    stop();
   
  }

  slowvelocity();
}