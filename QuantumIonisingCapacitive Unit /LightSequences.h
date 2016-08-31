#ifndef LIGHT_SEQUENCES_H
#define LIGHT_SEQUENCES_H

const int ledOnTime      = 250;
const int ledOnTimeDefaultSequence = 125;
const int NUM_INTRO_LEDS = 8;

bool introSequencePlaying = true;

int ledOnIndx = 0;


void playIntroSequence()
{
    if((millis() / ledOnTime <= NUM_INTRO_LEDS) % (int)(ledOnTime * NUM_INTRO_LEDS))
    {
        for(int i = 0; i < (int)(millis() / ledOnTime); i++)
        {
            digitalWrite(i + LED_PIN_START,HIGH);
        }
    }else
    {
        introSequencePlaying = false;
    }
}

void playDefaultLightSequence()
{
    int ledOn = (millis() / ledOnTimeDefaultSequence) % NUM_LEDS;

    for( int i = 0; i < NUM_LEDS; i++)
    {
        if( i == ledOn )
            digitalWrite( i + LED_PIN_START, HIGH );
        else
            digitalWrite( i + LED_PIN_START, LOW );
    }
}

void setLEDStates()
{
    // Set the state of the LEDs
    for(int i = 0; i < NUM_LEDS;i++)
    {
          if(ledOn[i] > 0 || ALL_LEDS_ON)
              digitalWrite(i + LED_PIN_START, HIGH);
          else
              digitalWrite(i + LED_PIN_START, LOW);
         
          if(ledOn[i] > 0)
              ledOn[i]--;
    }    
}

#endif
