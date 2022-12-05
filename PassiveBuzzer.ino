int potpin=0;// initialize analog pin 0
int buzzer=8;// select digital IO pin for the buzzer
float x=0;
float y=0;
float T=0;
float d=0;
void setup() {
  Serial.begin(9600);// set baud rate at 9600{ 
  pinMode(buzzer,OUTPUT);// set digital IO pin pattern, OUTPUT to be output 
  } 
void loop() {
  unsigned char i,j;//define variable
  while(1) {
    x=analogRead(potpin);// read the analog value from the sensor and assign it to val
    y = (9940*x)/1023 + 60;
    T = 1000000/y ;
    d = T/2; 
    for(i=0;i<80;i++) {// output a frequency sound
      digitalWrite(buzzer,HIGH);// sound
      delayMicroseconds(d);//delay1ms 
      digitalWrite(buzzer,LOW);//not sound
      delayMicroseconds(d);//ms delay 
      }

  Serial.print("Frequency is ");     
  Serial.print(y);// display value of val
  Serial.println(" Hz");
  delay(10);// wait for 0.01 second 
    }
  
  

  
} 
