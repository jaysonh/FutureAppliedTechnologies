#ifndef RANDOMSEEDCREATOR_H
#define RANDOMSEEDCREATOR_H

#include "defines.h"

unsigned char geigerRandomSeed = 0;

// Stores which we have saved upto 
int currentBit = 0;
int bits[NUM_BITS];

// Stores which pulse we have saved to
int currentPulseTimeIndx;
int lastPulse = 0;
unsigned long geigerPulseTimes[NUM_GEIGER_PULSE_TIMES_PER_BIT];


void initBit()
{
  currentPulseTimeIndx=0;
  currentBit = 0;
        
  for(int i = 0; i < NUM_BITS; i++)
  {
      bits[i] = -1;
  }
}


void setRandomSeed()
{
    geigerRandomSeed = 0;
    
    for(int i = 0; i < NUM_BITS; i++)
    {
        //Serial.print(bits[i]);
        geigerRandomSeed += (1 << i) * bits[i];
    }
    
    //Serial.println(geigerRandomSeed);
    Serial.write(geigerRandomSeed);
     
}


void setBit(int bitIndx)
{
    long diff1 = geigerPulseTimes[1] - geigerPulseTimes[0];
    long diff2 = geigerPulseTimes[2] - geigerPulseTimes[1];

    /*for(int i = 0; i < 3; i++)
      Serial.println(geigerPulseTimes[i]);
    Serial.print("diff1: ");
    Serial.println(diff1);
    Serial.print("diff2: ");
    Serial.println(diff2);
    */
    if(diff1 >= diff2)
    {
        bits[currentBit] = 0;
    }else
    {
        bits[currentBit] = 1;
    }
    
    currentBit++;

    if(currentBit >= NUM_BITS)
    { 
        setRandomSeed();

        initBit();
    }
}

void addPulse(unsigned long pulseTime)
{
    if(pulseTime != lastPulse)
    {
        lastPulse = pulseTime;
        //Serial.print("Adding pulsetime: ");
        //Serial.print(pulseTime);
        //Serial.print(" lastpulse: ");
        //Serial.println(geigerPulseTimes[currentPulseTimeIndx]);
        geigerPulseTimes[currentPulseTimeIndx] = pulseTime;
    
        currentPulseTimeIndx++;
    
        if(currentPulseTimeIndx >= NUM_GEIGER_PULSE_TIMES_PER_BIT)
        {
            setBit(currentBit);
            currentPulseTimeIndx = 0;
        }
    }
}

#endif

