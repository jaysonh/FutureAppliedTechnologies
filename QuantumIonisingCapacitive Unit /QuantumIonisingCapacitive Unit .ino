#include "randomSeedCreator.h"
#include "defines.h"
#include "LightSequences.h"

void setup() 
{
    // Open a serial connection at 9600 baud for outputing random seed
    Serial.begin( OUTPUT_BAUD_RATE );
  
    // Enable pin that receives data from geiger counter
    pinMode(GEIGER_INPUT_PIN, INPUT);
  
    // Enable pin to detect on/off switch
    pinMode(3, INPUT);

    // Enable pins to control LEDs and turn them off by default
    for(int i = LED_PIN_START; i < LED_PIN_START + NUM_LED_PINS;i++)
    {
        pinMode(i, OUTPUT);

        digitalWrite(i, LOW);
    }
}

void loop() 
{
    if(introSequencePlaying)
    {
        playIntroSequence();  
    }else
    {
        // Get pulse message from geiger counter
        int geigerPulse = digitalRead(GEIGER_INPUT_PIN);

        // If geiger counter has pulsed then flash the leds
        if(geigerPulse != 1  )
        {
            for(int i = 0; i < NUM_LEDS;i++)
                ledOn[i] = LED_ON_TIME;
            
            Serial.println(1);  
            //addPulse(millis());
        }
        // Otherwise play default light sequence (lights spinning)
        else
        {
            playDefaultLightSequence();
        }
    }

    setLEDStates();
    
}
