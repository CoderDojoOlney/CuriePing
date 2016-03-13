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

#ifndef __CuriePing_h__
#define __CuriePing_h__

#include "Arduino.h"

#define MAX_SENSOR_DISTANCE 100
#define US_ROUNDTRIP_CM 57
#define MAX_SENSOR_DELAY 5800
#define PING_OVERHEAD 5
#define NO_ECHO 0

class CuriePing
{
  private:
    uint8_t _triggerPin;
    uint8_t _echoPin;
    unsigned int _maxEchoTime;
    unsigned int _max_time;
    
    bool pingInit();

  public:
    CuriePing(const uint8_t triggerPin, const uint8_t echoPin);
    unsigned int ping();
};



#endif // __CuriePing_h__
