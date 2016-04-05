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

unsigned long time;
unsigned long over_time;
int transmissions = 0;
bool done = false;
bool can_send = true;
String to_send = "";
String last_string = "";

void setup()
{
  Serial.begin(9600);  // Start up serial
  Serial1.begin(115200);
  rfBegin(12);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)
  
  
  for(int i = 0; i<49; i++){
    to_send += 'x';
    last_string += 's';
  }
  // Send a message to other RF boards on this channel
  rfPrint("ATmega128RFA1 Dev Board Online!\r\n");
  time = micros();
}

void loop()
{
//  if (transmissions < 10000)  // If serial comes in...
//  {
//    rfWrite('x'); // ...send it out the radio.
//    transmissions++;
//  }
  if (transmissions < 50)  // If serial comes in...
  {
    rfPrint(to_send); // ...send it out the radio.
    transmissions++;
  }
  else {
    rfWrite('s');
    if(!done){
      over_time = micros() - time;
      //Serial.println(to_send);
      Serial.print("Transmissions #: ");
      Serial.println(transmissions);
      Serial.print("Time in mics: ");
      Serial.println(over_time);
      Serial.print("bps: ");
      Serial.println(8.0*transmissions*50000000.0/over_time, 4);
      done = true;
    }
  }
}
