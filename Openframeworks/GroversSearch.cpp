//
//  QuantumGroversAlgorithmVisualiser.cpp
//  QuantumTestFinal
//
//  Created by jayson on 1/12/2015.
//
//

#include "GroversSearch.hpp"

/*
 
 This is an implementation of Grovers Search algorithm
 
 Which is a quantum algorithm that searches through data sets
 
 in this example we search through all combinations of a 7 bit
 number to match the number 66 (binary rep 01000010)
 
 Each sphere represents a qubit which starts at a 50/50 state of being on and off
 
 You can see at the start the spheres flick between on and off (black and white) very quickly
 
 But as the algorithm proceeds it becomes more certain of the final answer
 
 This example can be 99% sure of the answer within 9 steps,
 
 The way
 
 
 good explanation of grovers algorithm: http://www.cs.bham.ac.uk/internal/courses/intro-mqc/current/lecture08_handout.pdf
 
 */

void GroversSearch::init()
{
    instructionLineIndx = 0;
    instructionPos  = 0;
    
    instructionLines[0] = "This project is an investigation into ";
    instructionLines[1] = "speculative computation and the creation ";
    instructionLines[2] = "of new types of software and hardware.";
    
    instructionLines[3] = " ";
    instructionLines[4] = "The system developed is a light and energy";
    instructionLines[5] = "based cybernetic system which uses the ";
    instructionLines[7] = "effects of light such as phosphoresence,";
    instructionLines[8] = "radioactive decay, laser optical amplification";
    instructionLines[9] = "and diffraction to both transmit and compute";
    instructionLines[10] = "information.";
    
    instructionLines[11] = " ";
    instructionLines[12] = "This light based computing system uses the";
    instructionLines[13] = "idea of storing and transmitting energy into";
    instructionLines[14] = "different states and frequenciesThe project ";
    instructionLines[15] = "is driven by a radioactive isotope that ";
    instructionLines[16] = "triggers a geiger counter, this process is an";
    instructionLines[17] = "effect of quantum mechanics and is the most  ";
    instructionLines[18] = "pure form of randomness that occurs in nature. ";
    instructionLines[19] = "This seeds a random number generator that is ";
    instructionLines[20] = "then used by totrigger lasers and other lights";
    instructionLines[21] = "throughout the system. In the aquarium a laser ";
    instructionLines[22] = "shines onto phosphorescent stones which act as";
    instructionLines[23] = "short term memory units that dissapate the light";
    instructionLines[24] = "energy with time";
    
    instructionLines[25] = " ";
    instructionLines[26] = "The system is running a statistical based ";
    instructionLines[27] = "search algorihthm called grovers search algorithm. ";
    instructionLines[28] = "This searches an unordered set of data for a ";
    instructionLines[29] = "single result. In this piece the algorithm is ";
    instructionLines[30] = "utilising different components of the light";
    instructionLines[31] = "based system to complete the algorithm.";

    
    for(int i = 0; i < OUTPUT_LOG_LINES; i++)
    {
        outputLog[i] = "";
    }
    mFont.load( "fonts/Courier.ttf", 15 );
    searchNumber = 66;
    resetAlgorithm();
   
}

void GroversSearch::addToLog(string line)
{
    string newLine = line + ofToString(ofRandom(0,1));
    
    int millis = ofGetElapsedTimeMillis() % 1000;
    
    string hrZeroPad = "";
    if(ofGetHours() < 10)
        hrZeroPad = " ";
    
    string minZeroPad = "";
    if(ofGetMinutes() < 10)
        minZeroPad = " ";
    
    string secZeroPad = "";
    if(ofGetSeconds() < 10)
        secZeroPad = " ";
    
    string milZeroPad = "";
    if(millis < 10)
        milZeroPad = "00";
    if(millis < 100)
        milZeroPad = "0";
    
    
    string timestamp = hrZeroPad + ofToString(ofGetHours()) + ":" + minZeroPad +ofToString(ofGetMinutes()) + ":" + secZeroPad + ofToString(ofGetSeconds()) + ":" + milZeroPad + ofToString( millis ) + ": " + line;
    
    for(int i = 0; i < OUTPUT_LOG_LINES-1; i++)
    {
        outputLog[i] = outputLog[i+1];
    }
        
    outputLog[OUTPUT_LOG_LINES-1] = timestamp;
    
    
}

void GroversSearch::resetAlgorithm()
{
    searchNumber = (int)ofRandom(0, 127);
    mMaxIterations = round((float)( (PI / 4.0) * sqrtf((float)std::pow((float)2.0, (float)NUM_BITS-1))));
    
    addToLog("Restarting search algorithm");
    addToLog("Searching for: " + ofToString(searchNumber));
    addToLog("Optimum num iterations: " + ofToString(mMaxIterations));
    
    mIteration = 0;
    
    mQuantumSim.init(NUM_BITS);
    
    setSearchVal(searchNumber);
    
    
    for(int i = 1; i < NUM_BITS; i++)
        mQuantumSim.applyNoOp(i);
    mQuantumSim.applyGatePauliX(0);
    
    
    // Apply hadamard gate to all bits
    for(int i = 0; i < NUM_BITS; i++)
        mQuantumSim.applyGateHadamard(i);
    

}

void GroversSearch::drawConsole(  )
{
    ofSetColor(255);
    
    ofPushMatrix();
    ofTranslate(-30,350);
    mFont.drawString("/**************************************************/", 50, 50 - 2 * SPACING);
    
    mFont.drawString("/*      Grovers Search Algorithm Output      ", 50, 50 - 1 * SPACING);
    mFont.drawString("*/", 649, 50 - 1 * SPACING);
    
    mFont.drawString("/*       ", 50, 50 - 0 * SPACING);
    mFont.drawString("*/", 649, 50 - 0 * SPACING);
    
    mFont.drawString("/* Searching for value: " + ofToString(searchNumber), 50, 50 + 1 * SPACING);
    mFont.drawString("*/", 649, 50 + 1 * SPACING);
    
    mFont.drawString("/* Found value:         " + ofToString(collapsedResult), 50, 50 + 2 * SPACING);
    mFont.drawString("*/", 649, 50 + 2 * SPACING);
    
    mFont.drawString("/* Iteration:            " + ofToString(mIteration) + "/" + ofToString(mMaxIterations), 50, 50 + 3 * SPACING);
    mFont.drawString("*/", 649, 50 + 3 * SPACING);
    
    mFont.drawString("/*       ", 50, 50 + 4 * SPACING);
    mFont.drawString("*/", 649, 50 +4 * SPACING);
    
    mFont.drawString("/* Output Log", 50, 50 + 5 * SPACING);
    mFont.drawString("*/", 649, 50 + 5 * SPACING);
    
    mFont.drawString("/* ----------", 50, 50 + 6 * SPACING);
    mFont.drawString("*/", 649, 50 + 6 * SPACING);
    
    for(int i = 0; i < OUTPUT_LOG_LINES; i++)
    {
        mFont.drawString("/*  " + ofToString(outputLog[i]), 50, 50 + (7 + i) * SPACING);
        mFont.drawString("*/", 649, 50   + (7 + i) * SPACING);
        
    }
    mFont.drawString("/*  ", 50, 50 + (7 + OUTPUT_LOG_LINES) * SPACING);
    mFont.drawString("*/", 649, 50   + (7 + OUTPUT_LOG_LINES) * SPACING);
    mFont.drawString("/**************************************************/", 50, 50   + (8 + OUTPUT_LOG_LINES) * SPACING);
    
    
    
    ofPopMatrix();
    
    drawInstructions();
    
    
}

void GroversSearch::drawInstructions()
{
    if(ofRandom(0,1) < TEXT_DRAW_SPEED)
    {
        instructionPos++;
        
        if(instructionPos >= instructionLines[ instructionLineIndx ].length() )
        {
            instructionLineIndx++;
            instructionPos      = 0;
            
            if(instructionLineIndx >= NUM_INSTRUCTION_LINES)
            {
                instructionLineIndx = 0;
            }
        }
    }
    
    for(int i = 0; i < instructionLineIndx; i++)
    {
        mFont.drawString( instructionLines[i], ofGetWidth()/2 + 50, 50 + i * SPACING);
       
    }
    
   
    string line = instructionLines[instructionLineIndx].substr(0,instructionPos);
    
    mFont.drawString( line, ofGetWidth()/2 + 50, 50 + instructionLineIndx * SPACING);
    
}

bool GroversSearch::update()
{
    bool algorithmFinished = false;
    int states[NUM_BITS-1];
    for(int i = 0; i < NUM_BITS-1;i++)
    {
        float prob = mQuantumSim.getProbability(i+1);
        
        states[i] =mQuantumSim.testBit(i+1);
        
        
        
        
    }
    collapsedResult = 0;
    
    for(int i = 0; i < NUM_BITS-1;i++)
        collapsedResult += states[i] * pow(2.0f, (float)i);
    ofSetColor(ofColor::black);
    //cout <<  "Current Iteration: " << ofToString(mIteration+1) << " / " << ofToString(mMaxIterations)<<endl;
    //cout << "Results: " << ofToString(collapsedResult) <<endl;
    //cout << "Searching for: " << ofToString( searchNumber ) <<endl;

    
    
     if(ofGetFrameNum() % 90==0)
     {
         addToLog("applying iteration: " + ofToString(mIteration));
         mIteration++;
         
         mQuantumSim.applyUfGate();
         mQuantumSim.applyWGate();
         
         addToLog("collapsing bits to value: " + ofToString(collapsedResult));
     
     }
     
     // Reset
     if(mIteration > mMaxIterations)
     {
         algorithmFinished=true;
         resetAlgorithm();
     }
    return algorithmFinished;
    
}

int GroversSearch::mousePressed( ofVec2f mousePos )
{
    
    return 0;
}