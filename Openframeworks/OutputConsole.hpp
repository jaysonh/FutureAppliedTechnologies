//
//  OutputConsole.hpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 05/09/2016.
//
//

#ifndef OutputConsole_hpp
#define OutputConsole_hpp

#include <stdio.h>
#include "ofMain.h"

#define SYSTEM_INFO_LOG_NUM_LINES  20
#define SEARCH_ALGORITHM_NUM_LINES 20

#define SPACING 20
class OutputConsole
{
public:
    
    void init();
    void update( int * ldrVals );
    void draw();
    
private:
    
    ofTrueTypeFont mFont;
    
    string mSysInfoLog[   SYSTEM_INFO_LOG_NUM_LINES  ];
    string mSearchAlgLog[ SEARCH_ALGORITHM_NUM_LINES ];
    
    int * mLDRVals;
    
};

#endif /* OutputConsole_hpp */
