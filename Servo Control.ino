int servopin=9;// select digital pin 9 for servomotor signal line
float myangle;// initialize angle variable
int pulsewidth;// initialize width variable
float val;
int potpin = 0; // initialize analog 0 as pin for potentiometer
float pot_val; // going to be used after conversion
float new_ang;
float temp;
void servopulse(int servopin,float myangle)// define a servo pulse function
{
pulsewidth=(myangle*11)+500;// convert angle to 500-2480 pulse width
digitalWrite(servopin,HIGH);// set the level of servo pin as “high”
delayMicroseconds(pulsewidth);// delay microsecond of pulse width
digitalWrite(servopin,LOW);// set the level of servo pin as “low”
delay(20-pulsewidth/1000);
}

void setup()
{
pinMode(servopin,OUTPUT);// set servo pin as “output”
Serial.begin(9600);// connect to serial port, set baud rate at “9600”
Serial.println("servo=o_seral_simple ready" ) ;
}
void loop()// convert number 0 to 9 to corresponding 0-180 degree angle, LED blinks corresponding number of time
{
val=Serial.read();// read serial port value
pot_val = analogRead(potpin); // read the value of potpin

Serial.println(pot_val);
temp = 0.17595308;
new_ang = temp*pot_val;
Serial.println(new_ang);
servopulse(servopin,new_ang);// use the pulse function
delay(10);
}