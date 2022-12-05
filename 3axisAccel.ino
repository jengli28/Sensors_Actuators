/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

int pin4 = 4; // LED Pins -> Far Left
int pin5 = 5; 
int pin6 = 6;
int pin7 = 7; // LED Pins -> Center
int pin8 = 8;
int pin9 = 9;
int pin10 = 10; // LED Pins -> Far Right

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() 
{
  pinMode(pin4,OUTPUT); // define digital pin as output
  pinMode(pin5,OUTPUT); 
  pinMode(pin6,OUTPUT); 
  pinMode(pin7,OUTPUT); 
  pinMode(pin8,OUTPUT); 
  pinMode(pin9,OUTPUT); 
  pinMode(pin10,OUTPUT); 

  digitalWrite(pin4,LOW); // initialize LEDs to be llow
  digitalWrite(pin5,LOW);
  digitalWrite(pin6,LOW);
  digitalWrite(pin7,LOW);
  digitalWrite(pin8,LOW);
  digitalWrite(pin9,LOW);
  digitalWrite(pin10,LOW);

  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
  
  checkSettings();
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}

float calc_xy_angles(float x, float y, float z){
   // Using x y and z from accelerometer, calculate x and y angles
   float x_val, y_val, z_val, result;
   unsigned short x2, y2, z2; //24 bit

   // Lets get the deviations from our baseline
   x_val = x-9.70;
   y_val = y-1.14;
   z_val = z+3.20;

   // Work out the squares
   x2 = (unsigned short)(x_val*x_val);
   y2 = (unsigned short)(y_val*y_val);
   z2 = (unsigned short)(z_val*z_val);

   //X Axis
   result=sqrt(y2+z2);
   result=x_val/result;
   float accel_angle_x = atan(result);

   return accel_angle_x;

   /*//Y Axis
   result=sqrt(x2+z2);
   result=y_val/result;
   accel_angle_y = atan(result);
   */
}

void loop()
{
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  /*
  Serial.print(" Xraw = ");
  Serial.print(rawAccel.XAxis);
  Serial.print(" Yraw = ");
  Serial.print(rawAccel.YAxis);
  Serial.print(" Zraw = ");
  Serial.println(rawAccel.ZAxis);
  */  

  /*Serial.print(" Xnorm = ");
  Serial.print(normAccel.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(normAccel.YAxis);
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis);
  */

  float maxAccel = 19.6;
  float twoThirds = 19.6 * (2/3);
  float oneThird = 19.6 * (1/3);
  float center = 9.70;
  float X_accel = normAccel.XAxis;
  float Y_accel = normAccel.YAxis;
  float Z_accel = normAccel.ZAxis;

  float X_angle = calc_xy_angles(X_accel,Y_accel,Z_accel);
  Serial.print("X_angle = ");
  Serial.println(X_angle);  
  if ( X_accel >= maxAccel){
    digitalWrite(pin4,LOW);
    digitalWrite(pin5,LOW);
    digitalWrite(pin6,LOW);
    digitalWrite(pin7,LOW);
    digitalWrite(pin8,LOW);
    digitalWrite(pin9,LOW);
    digitalWrite(pin10,HIGH);
  }
  else if ( X_accel < maxAccel &&  X_accel >= 16.3){
    digitalWrite(pin4,LOW);
    digitalWrite(pin5,LOW);
    digitalWrite(pin6,LOW);
    digitalWrite(pin7,LOW);
    digitalWrite(pin8,LOW);
    digitalWrite(pin9,HIGH);
    digitalWrite(pin10,LOW);
  }
  else if ( X_accel < 16.3 &&  X_accel >= 13){
    digitalWrite(pin4,LOW);
    digitalWrite(pin5,LOW);
    digitalWrite(pin6,LOW);
    digitalWrite(pin7,LOW);
    digitalWrite(pin8,HIGH);
    digitalWrite(pin9,LOW);
    digitalWrite(pin10,LOW);
  }
  else if ( X_accel < 9.9 &&  X_accel >= 8.0){
    digitalWrite(pin4,LOW);
    digitalWrite(pin5,LOW);
    digitalWrite(pin6,LOW);
    digitalWrite(pin7,HIGH);
    digitalWrite(pin8,LOW);
    digitalWrite(pin9,LOW);
    digitalWrite(pin10,LOW);
  }
  else if ( X_accel < 8.0 &&  X_accel >= 0){
    digitalWrite(pin4,LOW);
    digitalWrite(pin5,LOW);
    digitalWrite(pin6,HIGH);
    digitalWrite(pin7,LOW);
    digitalWrite(pin8,LOW);
    digitalWrite(pin9,LOW);
    digitalWrite(pin10,LOW);
  }
  else if ( X_accel < 0 &&  X_accel >= -10){
    digitalWrite(pin4,LOW);
    digitalWrite(pin5,HIGH);
    digitalWrite(pin6,LOW);
    digitalWrite(pin7,LOW);
    digitalWrite(pin8,LOW);
    digitalWrite(pin9,LOW);
    digitalWrite(pin10,LOW);
  }
  else if ( X_accel <= -maxAccel){
    digitalWrite(pin4,HIGH);
    digitalWrite(pin5,LOW);
    digitalWrite(pin6,LOW);
    digitalWrite(pin7,LOW);
    digitalWrite(pin8,LOW);
    digitalWrite(pin9,LOW);
    digitalWrite(pin10,LOW);
  }


  delay(1000);
}
