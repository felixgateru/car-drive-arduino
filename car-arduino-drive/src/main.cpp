#include <Arduino.h>
#include <CircularBuffer.h>

#define CH1 15 // connected on pin 15
#define MOTOR_PIN_1   4
#define MOTOR_PIN_2   16
#define MOTOR_SPEED_PIN   17

 
int ch1Value;
int motor_value;

CircularBuffer<int,10> write_values; 
 
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 18000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 

void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // setting up the channel as input
  pinMode(CH1, INPUT);
  pinMode(MOTOR_PIN_1,OUTPUT);
  pinMode(MOTOR_PIN_2,OUTPUT);
  pinMode(MOTOR_SPEED_PIN,OUTPUT);

}
 
 
void loop() {
  
  // Get values for each channel

  //using a buffer to waste input times

  while(!write_values.unshift(readChannel(CH1, -100, 100, 0))){
     Serial.print("Ch1: ");
     motor_value = write_values.first();
     Serial.print(motor_value);
     if(motor_value>0){
       digitalWrite(MOTOR_PIN_1,HIGH);
       digitalWrite(MOTOR_PIN_2,LOW);
       analogWrite(MOTOR_SPEED_PIN,map(motor_value,0,100,0,255));

     }
     else if(motor_value<1){
       digitalWrite(MOTOR_PIN_1,LOW);
       digitalWrite(MOTOR_PIN_2,HIGH);
       motor_value = -motor_value;
       analogWrite(MOTOR_SPEED_PIN,map(motor_value,0,100,0,255));
     }
     write_values.clear();

  }
 
}
