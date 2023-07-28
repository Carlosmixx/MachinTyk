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

  int carspeed = 170; // Velocidad máxima ajustada

int rightdistance = 0;
int leftdistance = 0;
int middledistance = 0;


void forward() {
  motordir.write(92);//98//89
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, HIGH);
  digitalWrite(VA2, LOW);
  digitalWrite(VA3, LOW);
  digitalWrite(VA4, HIGH);
  Serial.println("Forward");
}


void left() {
  motordir.write(122);//135-112//116//121
  
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, HIGH);
  digitalWrite(VA2, LOW);
  digitalWrite(VA3, LOW);
  digitalWrite(VA4, HIGH);
  Serial.println("Left");
}

void leftplus() {
motordir.write(125);//155//125//120//119//125

  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, HIGH);
  digitalWrite(VA2, LOW);
  digitalWrite(VA3, LOW);
  digitalWrite(VA4, HIGH);
  Serial.println("Leftp");
}

void right() {
  motordir.write(47);//51//48
  
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, HIGH);
  digitalWrite(VA2, LOW);
  digitalWrite(VA3, LOW);
  digitalWrite(VA4, HIGH);
  Serial.println("Right");
}

void rightplus() {
  motordir.write(45);//47//46
  
  analogWrite(RDA, carspeed);
  analogWrite(RDB, carspeed);
  digitalWrite(VA1, HIGH);
  digitalWrite(VA2, LOW);
  digitalWrite(VA3, LOW);
  digitalWrite(VA4, HIGH);
  Serial.println("Rightp");
}

void stop() {
  
  //delay(4000);
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
  motor.write(89);
  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(3);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long time = pulseIn(eco, HIGH);
  int distance = (time * 0.0343) / 2;
  Serial.println(distance);
  return distance;
  delay(100);
}

/*bool boutto() {
  int distance = getDistance();
  if (distance != -1 && distance <= 10) {
    return true;
  }
  return false;
}*/

void adjustSpeed() {
  int distance = getDistance();
  if (distance != -1 && distance <= 60) {
    carspeed = map(distance, 0, 60, 0, carspeed);
    analogWrite(RDA, carspeed);
    analogWrite(RDB, carspeed); 
  } else if (distance <= 25) {
    stop();
    delay(100);
  } else if (distance >=25) {
  carspeed=170;
}
carspeed=170;
}
//kkkk
void advertobs() {
  stop();
//delay(400);
  motor.write(45);
  delay(425);
  rightdistance = getDistance();
  delay(515);
  motor.write(125);
  delay(515);
  leftdistance = getDistance();
  delay(525);
   motor.write(85);
  delay(525);
  middledistance= getDistance();
  delay(525);
  
  while (rightdistance>=1081 || leftdistance>=1081 || middledistance>=1081) {
    stop();
    motor.write(45);
  delay(525);
  rightdistance = getDistance();
  delay(515);
  motor.write(125);
  delay(525);
  leftdistance = getDistance();
  delay(515);
  motor.write(85);
  delay(525);
  middledistance= getDistance();
  delay(515);
  
  }
  if (rightdistance > leftdistance && middledistance <135 && rightdistance<310) {
    rightplus();
    delay(1335);
    
    
  } else if (rightdistance < leftdistance && middledistance <135 && leftdistance<310){
    leftplus();
    delay(1400);//1010//1220//1285//1315//1415//1435//1423
    
    
  } else if (middledistance<40) {
      stop();

    } 

  }
//kkkk
void detectObstacle() {
  stop();
//delay(400);
  motor.write(45);
  delay(425);
  rightdistance = getDistance();
  delay(525);
  motor.write(125);
  delay(515);
  leftdistance = getDistance();
  delay(515);
   motor.write(85);
  delay(525);
  middledistance= getDistance();
  delay(525);

  while (rightdistance>=1081 || leftdistance>=1081 || middledistance>=1081) {
    stop();
    motor.write(45);
  delay(525);
  rightdistance = getDistance();
  delay(525);
  motor.write(125);
  delay(525);
  leftdistance = getDistance();
  delay(515);
  motor.write(85);
  delay(525);
  middledistance= getDistance();
  delay(525);
  
  }
  
  if (rightdistance > leftdistance && middledistance <120 && rightdistance<300) {
    right();
    delay(1009);
    
  
  } else if (rightdistance < leftdistance && middledistance <120 && leftdistance<300){
    left();
    delay(1400);//1275//1410//1421//1427//1410
    

  } else if (middledistance<40) {
      stop();

    }

  }


void loop() {
  static unsigned long previousTime = 0;
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - previousTime;



  if (elapsedTime >= 410) {
    motor.write(85);
    forward();
    delay(360);//400
    adjustSpeed();
    delay(130);//132
    stop();
    delay(600);
    middledistance = getDistance();
    delay(535); 

    if (middledistance > 140 ) {
      stop();
      detectObstacle();
     
    } else if (middledistance < 70) {
      stop();
      advertobs();
      
    } else {
      stop();
      advertobs();
    }
    
    previousTime = currentTime;
  }

}
