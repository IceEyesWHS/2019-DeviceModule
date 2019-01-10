/*    Arduino Long Range Wireless Communication using HC-12
                      Example 01
   by Dejan Nedelkovski, www.HowToMechatronics.com
*/
#include <SoftwareSerial.h>
   double dist;
   String output;
const int numReadings = 30;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
double average = 0;                // the average
int adjustedAvg = 0;
int inputPin = A0;
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
void loop() {
      // If Serial monitor has data
   // Send that data to HC-12
   /*dist = (analogRead(0)+102)/23.5;
   if(analogRead(0) == 1023){
    dist = 0;
   }


    Serial.print(dist);
    Serial.println(" centimeters");
    */
    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  //modify the average to be scaled


  average = (average+81)/23.95;
  if(average > 45){
    average = 0;
  }
  // send it to the computer as ASCII digits
 adjustedAvg = (int)(average*100);
  Serial.println(adjustedAvg);
  HC12.println(adjustedAvg);
  delay(10);        // delay in between reads for stability

   /* for(int i = 0; i<1024; i++){
        delay(100);

     Serial.println(i);
     HC12.println(i);*/
    
}
/*public double getAverage();
  {
    double sum = 0;
    for(int i = 0; i<20; i++)
      {
        sum +=i;
        
        
      }
  }*/
