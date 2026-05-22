#include <Servo.h>
Servo myservo;
int currentPos = 90;
int targetPos = 90;  
const int trigPin1 = 9, echoPin1 = 10;
const int trigPin2 = 5, echoPin2 = 6;
unsigned long lastMoveTime = 0;
const int stepSpeed = 15;                     
void setup() {
  pinMode(trigPin1, OUTPUT); pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); pinMode(echoPin2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(3);
  myservo.write(currentPos);
}
void loop() {
  // distances
  float d1 = getDist(trigPin1, echoPin1);
  float d2 = getDist(trigPin2, echoPin2);

  if (d1 < 20 && d2 > 20) {
    targetPos = 0;   
    digitalWrite(LED_BUILTIN, HIGH);
  } 
  else if (d2 < 20 && d1 > 20) {
    targetPos = 180; // Go to 180
    digitalWrite(LED_BUILTIN, HIGH);
  } 
  else if (d2 > 20 && d1 > 20){
    targetPos = 90;  
    digitalWrite(LED_BUILTIN, (d1 < 20 && d2 < 20)); 
  }
  else {
    targetPos = currentPos;  // Go to center if both or none
    digitalWrite(LED_BUILTIN, (d1 < 20 && d2 < 20)); 
  }

  if (millis() - lastMoveTime > stepSpeed) {
    if (currentPos < targetPos) {
      currentPos++;
      myservo.write(currentPos);
    } 
    else if (currentPos > targetPos) {
      currentPos--;
      myservo.write(currentPos);
    }
    lastMoveTime = millis(); // Reset timer
  }
}

float getDist(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH, 25000) * 0.0343 / 2;
}
