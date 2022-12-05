#include <MPU6050.h>
#include <Wire.h>
#include <Stepper.h>
#include <AccelStepper.h>
#include <Servo.h>
#include <stdio.h>   // Including these headers
#include <stdlib.h>  // so that I can generate a random
#include <time.h>    // array of numbers
#include <ezBuzzer.h> // ezBuzzer library

const int stepsPerRevolution = 2038;
const int Echo = 13;
const int Trig = 12;
const int Button = 7;
const int Buzzer = 6;
const int GreenLED = 22;
const int RedLED = 23;
const int looking = 175;
const int not_looking = 0;
const int not_dead = 175;
const int dead = 0;
unsigned long currentMillis = 0;       // stores the value of millis() in each iteration of loop()
unsigned long currentMicros = 0;

const int interval = 4000; 
const int readInterval = 100;
int previousReadMillis = 0;
int lastdistance = 30;

long duration, distance, distance2, duration2;

bool wasMoving = false;

Servo LoneServo;
Servo KillerServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);         // set baud rate
  LoneServo.attach(4);
  KillerServo.attach(5);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Button, INPUT);
  pinMode(Buzzer, OUTPUT);
  LoneServo.write(looking);       // LoneServo's start position
  KillerServo.write(not_dead);        // KillerServo's start position
  delay(3000);
}
void kill(){
  KillerServo.write(dead);
}
void peek_A_Boo(){

  if((LoneServo.read() == looking)){
    if (currentMillis - previousReadMillis >= readInterval){
      if(distance - lastdistance >1){
        kill();
        previousReadMillis+=readInterval;
      }
    else{
      previousReadMillis+=readInterval;
    }
    lastdistance = distance;
  }

}}
void stuff(){
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration/58.2;
  delay(300);
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW);
  duration2 = pulseIn(Echo, HIGH);
  distance2 = duration2/58.2;
  if(distance != distance2){
    kill();
  }
}

void loop() {
  currentMillis = millis();
  currentMicros = micros();
  //turnServo();
  /*digitalWrite(Trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration/58.2;*/
  stuff();
  Serial.println("Distance1=");
  Serial.print(distance);
  Serial.println("Distance2=");
  Serial.print(distance2);  
  delay(100);
  //peek_A_Boo();
  /*if(distance - lastdistance >1){
    KillerServo.write(dead);
  }
  lastdistance = distance;*/
}
