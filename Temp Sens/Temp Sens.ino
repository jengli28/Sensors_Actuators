#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
int F = 0;
float K = 0;
int counter=0;

int temp = 0;
int val = 0;
void setup(){
  Serial.begin(9600);
}
  
void loop(){
  int chk;
  chk = DHT.read(DHT11_PIN);    // READ DATA

  val = DHT.temperature;

  if (val != temp){
    Serial.print(DHT.temperature,1);
    Serial.print(" C,\t");

    F = (DHT.temperature*9/5) + 32;
    K = DHT.temperature + 273.15;
    Serial.print(F);
    Serial.print(" F,\t");
    Serial.print(K);
    Serial.print(" K,\tTime (s):");
    Serial.println(counter);
    temp = DHT.temperature;
  }
  
  counter+=1;
  delay(1000);
}