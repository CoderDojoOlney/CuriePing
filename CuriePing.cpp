/*****************************************************************************/
// Simple driver for the HC-SR04 ultrasonic sensor on the Arduino 101
// Inspired by NewPing, but written using high level calls
// Author: Anthony Abbot
// Date: 13 March 2016
// 
// This code has been developed for use by the Olney Coder Dojo club
//
// Class to utilise the HC-SR04 ultrasonic sensor
//
/*****************************************************************************/

#include "CuriePing.h"

CuriePing::CuriePing(const uint8_t triggerPin, const uint8_t echoPin)
  : _triggerPin{triggerPin},
  _echoPin{echoPin}
{
  pinMode(_echoPin, INPUT);     
  pinMode(_triggerPin, OUTPUT); 
  _maxEchoTime = (MAX_SENSOR_DISTANCE + 1) * US_ROUNDTRIP_CM;   
}

unsigned int CuriePing::ping()
{
  if (!pingInit())
    return NO_ECHO;

  while (digitalRead(_echoPin))                // Wait for the ping echo.
    if (micros() > _max_time) return NO_ECHO;   // Stop the loop and return NO_ECHO (false) if we're beyond the set maximum distance.

  return (micros() - (_max_time - _maxEchoTime) - PING_OVERHEAD) / US_ROUNDTRIP_CM; 
  
  
}

bool CuriePing::pingInit()
{
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(4); 
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(10); 

  // Still busy with last one
  if (digitalRead(_echoPin))
    return false;

  _max_time = micros() + _maxEchoTime + MAX_SENSOR_DELAY; // Maximum time we'll wait for ping to start (most sensors are <450uS, the SRF06 can take up to 34,300uS!)
  while (!digitalRead(_echoPin))                       // Wait for ping to start.
    if (micros() > _max_time) return false;               // Took too long to start, abort.

  _max_time = micros() + _maxEchoTime;
  return true;
}


