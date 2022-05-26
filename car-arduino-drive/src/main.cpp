#include <Arduino.h>
#include <CircularBuffer.h>

#define CH1 15 // connected on pin 15

 
int ch1Value;

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
}
 
 
void loop() {
  
  // Get values for each channel


  while(!write_values.unshift(readChannel(CH1, -100, 100, 0))){
     Serial.print("Ch1: ");
     Serial.print(write_values.first());
     write_values.clear();

  }
 
}
