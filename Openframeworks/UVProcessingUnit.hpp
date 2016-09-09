//
//  UVProcessingUnit.hpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 05/09/2016.
//
//

#ifndef UVProcessingUnit_hpp
#define UVProcessingUnit_hpp

#include "ofMain.h"

// Includes
#include <string>
#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <thread>         // std::thread
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include <vector>
#include <dirent.h>

// serial error codes
#define SERIAL_NO_DATA 	-2
#define SERIAL_ERROR	-1

// Transmission rate for connection to QSPU
#define BAUD_RATE       9600

#define NUM_LDRS        12

class UVProcessingUnit
{
public:
    
    void updateAsThread();
    bool isConnected();
    bool connectArduino();
    void init();
    void close();
    void update();
    void initSerial();
    
    int * getLDRValues();
    
private:
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // Private methods
    //////////////////////////////////////////////////////////////////////////////////////////
    
    // Connect to a serial device
    bool connect(int indx, int baudRate);
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // Private Variables
    //////////////////////////////////////////////////////////////////////////////////////////
    
    std::thread * 			  mThread;			// Thread object
    std::vector <std::string> mDeviceList;	    // List of available serial devices
    unsigned long int         mSeed;			// Current seed
    int                       mConnection;		// Which serial port to connect to
    bool                      mConnected;		// Connection status
    bool                      mDetectedDecay;
    bool                      mThreadRunning;
    
    int                       mLDRvalues[ NUM_LDRS ];

    
    ofSerial serialConn;
};
#endif /* UVProcessingUnit_hpp */
