//
//  PhosRam.hpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 05/09/2016.
//
//

#ifndef PhosRam_hpp
#define PhosRam_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxEtherDream.h"



#define LASER_PPS 25000

#define MODE_CALIBRATION 0
#define MODE_RUNNING     1

class PhosRam
{
public:
    
    void init();
    void update(  bool decayDetected );
    void draw();
    
    
    void enterCalibrationMode();

private:
    
    int mode;
    int bootMode;
    void gaussian_elimination(float *input, int n);
    ofMatrix4x4 findHomography(ofVec2f src[4], ofVec2f dst[4]);
    ofxIlda::Frame mIldaFrame;
    ofxEtherdream mEtherdream;
    
    ofVec2f mCorners[4];
    
    float mCalibrationScan;
};
#endif /* PhosRam_hpp */
