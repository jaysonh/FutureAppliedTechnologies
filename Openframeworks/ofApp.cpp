#include "ofApp.h"


/* 
 
 Very important!!
 Laser array goes in left side USB
 QSPU goes in right side
 
 
 */

//--------------------------------------------------------------
void ofApp::setup()
{
    phosRam.init();
    console.init();
     
    quantum.init();
    uvProcUnit.init();
    uvProcUnit.connectArduino();
    
    ofSetFrameRate(30);
    
    searchAlgorithm.init();
}

//--------------------------------------------------------------
void ofApp::update()
{
    console.update(uvProcUnit.getLDRValues()  );
    //uvProcUnit.update();
    
    phosRam.update(  quantum.decayDetected() );
    
    
    bool algorithmFinished = searchAlgorithm.update();
    
    if(algorithmFinished)
        phosRam.enterCalibrationMode();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofClear(0,0,0);
    
    
    
    
   // phosRam.draw();
    
    
    
    
    console.draw();
    searchAlgorithm.drawConsole();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::exit(){
 
    }

void ofApp::mouseDragged(int x, int y, int button)
{
    
    
    
}

void ofApp::mousePressed(int x, int y, int button)
{
  
}
