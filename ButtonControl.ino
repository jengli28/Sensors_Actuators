int ledpinR=11;// initialize pin 11
int ledpinG=10;// initialize pin 10
int inpin=7;// initialize pin 7
int val;// define val
int i = 0;
void setup()
{
pinMode(ledpinR,OUTPUT);// set LED pin as “output”
pinMode(ledpinG,OUTPUT);
pinMode(inpin,INPUT);// set button pin as “input”
digitalWrite(ledpinR,LOW); // turn of
}

void makeBlink(int x){
      int deynum = x * 1000;
      digitalWrite(ledpinR,HIGH);
      delay(deynum); // wait for i seconds
      digitalWrite(ledpinR,LOW); // turn off
      digitalWrite(ledpinG,HIGH);
      delay(deynum);
      digitalWrite(ledpinG,LOW);
      }

void loop()
{
  val=digitalRead(inpin);// read the level value of pin 7 and assign if to val

  if(val==HIGH)// check if the button is pressed, if yes....
    { 
      i+=1; // incrememnt i +1
       makeBlink(i);
    }
   
  
  if (i == 5){
    i = 0;
    }
}
