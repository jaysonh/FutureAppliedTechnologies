//
//  OutputConsole.cpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 05/09/2016.
//
//

#include "OutputConsole.hpp"

void OutputConsole::init()
{
    mFont.load( "fonts/Courier.ttf", 15 );
}

void OutputConsole::update( int * ldrVals )
{
    
    mLDRVals = ldrVals;
    
}

void OutputConsole::draw()
{
    
    ofSetColor(255);
    
    ofPushMatrix();
    ofTranslate(-30,25);
    mFont.drawString("/****************************************************/", 50, 50 - 2 * SPACING);
    mFont.drawString("/*      PhosRam Light Sensor Array Information      ", 50, 50 - 1 * SPACING);
    mFont.drawString("  */", 649, 50 - 1 * SPACING);
    
    for(int y = 0; y < 4; y++)
    {
        
        for(int x = 0; x < 4; x++)
        {
            int i = y * 4 + x;
            
            int displayVal = mLDRVals[i] * 10 + (int)ofRandom(0,10);
            if(displayVal > 99)
                displayVal = 99;
            
            string whiteSpace = "";
            
            if(i < 10)
                whiteSpace += " ";
            if(displayVal < 10)
                whiteSpace += " ";
            
            mFont.drawString( "   L[" + ofToString( i) + "]: " + whiteSpace + ofToString(displayVal), 50 + x * 125, SPACING + 50 + y * SPACING);
        }
    }
    
    for(int y = 0; y < 6; y++)
    {
        mFont.drawString("/*                                                  */", 50, 50 + y * SPACING);

    }
    
    mFont.drawString("/****************************************************/", 50, 50 + 6 * SPACING);
    
    ofPopMatrix();
    
}
