#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxQuantum.hpp"
#include "UVProcessingUnit.hpp"
#include "OutputConsole.hpp"
#include "PhosRam.hpp"
#include "GroversSearch.hpp"

#define LASER_OFFSET 2
#define NUM_LASERS   4


#define PATTERN_X_RESOLUTION 5
#define PATTERN_Y_RESOLUTION 30

#define LASER_EFFECT_TIME 30.0

#define SELECT_THRESH 50.0


/*
 
 // What happens:
 
 Recalibration sequence
    - laser scans across rocks (back and fourth)
    - Each laser diode scans back and foith once at a time to make calculations
 
 
 
 Elements on screen:
 - console displaying system information such as
        - Output of 16 ldrs for tank
        - rate of radiation
        - UVProcessingUnit information
 - search algorithm output and debugging
 
 - information about project
 
 
 
 QSPU and usb-ethernet adapter on power cable side usb port
 arduino mega on other side
 
 */
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void mousePressed(int x, int y, int button);
    
    void mouseDragged(int x, int y, int button);
		void keyPressed(int key);
        void exit();
    
private:
    
    
     ofxQuantum quantum;
     ofArduino	laserArray;
    
     UVProcessingUnit uvProcUnit;
     OutputConsole    console;
     GroversSearch    searchAlgorithm;
     PhosRam          phosRam;
    
};
