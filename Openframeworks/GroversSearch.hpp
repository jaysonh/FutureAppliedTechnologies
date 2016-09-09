
#ifndef GROVERSSEARCH_HPP
#define GROVERSSEARCH_HPP

#include <stdio.h>
#include "ofMain.h"
#include "ofxQuantumSimulator.hpp"

#define NUM_BITS       8
#define MAX_ITERATIONS 9
#define downSampleRate 4

#define SPACING 20

#define NUM_INSTRUCTION_LINES 32

#define OUTPUT_LOG_LINES 15
#define TEXT_DRAW_SPEED 0.25

class GroversSearch
{
public:
    
    void init();
    void drawConsole(  );
    bool update();
    
    int mousePressed( ofVec2f mousePos );
    
private:
    void drawInstructions();
    void addToLog(string line);
    void resetAlgorithm();
    
    int instructionLineIndx;
    int instructionPos;
    
    int mIteration;
    int mMaxIterations;
    
    ofxQuantumSimulator mQuantumSim;
    int collapsedResult;
    int searchNumber;
    ofTrueTypeFont mFont;
    
    string outputLog[ OUTPUT_LOG_LINES ];
    
    string instructionLines[ NUM_INSTRUCTION_LINES ];
};

#endif