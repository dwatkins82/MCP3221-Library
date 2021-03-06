/////////////////////////////////////////////////////////////////////////////
/*!

  MCP3221.h
  I2C Driver for Microchip's MCP3221 by Ryan Edwards, Sparkys Widgets
  
  Use this library with Sparkys Widgets MinipH, MinieC, IsoIon, IsoEC, and the ADCBreakout or any thing MCP3221 related

  I invest a lot of time and resources providing open source hardware, software, and tutorials 
  Please help support my efforts by purchasing products from www.sparkyswidgets.com, donating some time 
  on documentation or you can even donate some BitCoin to 1NwPNsf6t5vpph6AYY5bg361PSppPSSgDn

*/
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCP3221_H
#define _MCP3221_H


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
	
#include <Wire.h>

#define NUMSAMPLES 20 //Combined alpha approximation plus a storage based moving average,
#define POWER 256 //we will limit ourselves to power of 2 division (i.e no floating point)
#define ALPHA 178 // pick an integer from 1-256 1 = slowest change, 256 = raw change (no filter)  

class MCP3221 {
 public:
  MCP3221(uint8_t adcAddress, int adcVRef); //Overload for only this class initialization

  int readI2CADC(void);
  float calcMillivolts(void);
  float calcMillivolts(int);
  int calcRollingAVG(void); //Standard moving average implementation
  int calcEMAVG(void); //this is our exponential moving average which approximates a rolling/moving average using only the current and previous datapoints instead of arrays of points

  void updateVRef(int adcVRef);
  int getLastADCResult();
  
 private:
 	uint8_t I2CADCAddress;
 	int _adcVRef; //this is the Vin of the MCP3221 in Millivolts
 	int _samples[NUMSAMPLES];
 	int _cnt;
 	long _rollingTotal;
 	int _lastADCResult;
};

#endif
