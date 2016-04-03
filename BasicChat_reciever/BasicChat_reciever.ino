/*
  ATmega128RFA1 Dev Board Basic Chat
  by: Jim Lindblom
      SparkFun Electronics
  date: July 3, 2012
  License: Beerware. Feel free to use, reuse, and modify this code
  as you please. If you find it useful, you can buy me a beer.
  This code sets up the ATmega128RFA1's wireless transciever in
  the most basic way possible to serve as a serial gateway.
  Serial into the ATmega128RFA1's UART0 will go out the RF radio.
  Data into the RF radio will go out the MCU's UART0.
*/

#include "RadioFunctions.h"

int index = 0;
bool done = false;
unsigned long time;
unsigned long over_time;

void setup()
{
  Serial.begin(9600);  // Start up serial
  Serial1.begin(115200);
  rfBegin(11);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)
  
  // Send a message to other RF boards on this channel
  rfPrint("ATmega128RFA1 Dev Board Online!\r\n");
  index = 0;
  time = micros();
}

void loop()
{
  if (rfAvailable())  // If data receievd on radio...
  {
    char c = rfRead();
    if(c == 'x'){
      index++;
      done = false;
    }
    if(c == 's'){
      if(!done){
        Serial.print("Time in mics: ");
        Serial.println(micros() - time);
        Serial.print("Packets received: ");
        Serial.println(index);
        Serial.print("Success rate: ");
        Serial.println(index/10000.0, 6); 
        index = 0;
        done = true;
      }
      time = micros();
    }
    
  }
}
