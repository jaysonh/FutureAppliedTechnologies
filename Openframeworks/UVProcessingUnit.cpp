//
//  UVProcessingUnit.cpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 05/09/2016.
//
//

#include "UVProcessingUnit.hpp"


////////////////////////////////////////////////////
// Close Connection                               //
////////////////////////////////////////////////////
void UVProcessingUnit::close()
{
    printf("Closing serial connection\n");
    
    // End the background thread and join it together with the main thread so that the application can close cleanly
    if(mThread != NULL)
    {
        printf("joning thread\n");
        mThread->join();
    }
    printf("thread joined\n");
    mThreadRunning =false;
    delete mThread;
}

void UVProcessingUnit::initSerial()
{
    serialConn.listDevices();
    serialConn.setup("tty.usbmodem1421", 9600);
    
    
}

void UVProcessingUnit::update()
{
    
    /*unsigned char bytesReturned[1];
    
    memset(bytesReturned, 0, 1);
    int nRead = 0;
    
    while( (nRead = serialConn.readBytes( bytesReturned, 1)) > 0){
        
        //if((int)bytesReturned[0] >=30 && (int)bytesReturned[0] <= 39 )
        
                    cout << (int)bytesReturned[0] <<endl;
    };
    */
    
    //int val =(int)serialConn.readByte();
    //std::cout << val << std::endl;;
    
    
}

////////////////////////////////////////////////////
// Initalise the QSPU                             //
////////////////////////////////////////////////////
void UVProcessingUnit::init()
{
    // Empty the list of devices
    mDeviceList.clear();
    
    // Find all the available serial devices
    DIR *dir;
    dir = opendir("/dev");
    
    std::string deviceName = "";
    
    mConnection = -1;
    
    // If serial connectios are not available
    if(dir == nullptr)
    {
        std::cout << "ofSerial buildDeviceList(): error listing devices in /dev";
    }
    // Otherwise find devices
    else
    {
        int deviceCount = 0;
        
        // Pointer to store current entry
        struct dirent *entry;
        
        // Loop through each serial device
        while((entry = readdir(dir)) != nullptr)
        {
            deviceName = (char *)entry->d_name;
            
            // If it is a serial device
            // Must be plugged into right hand side usb (port 1411 is the left)
            //if( deviceName.substr(0, deviceName.length()) == "tty.usbmodem1421" ||
            //   deviceName.substr(0, deviceName.length()) == "cu.usbmodem1421" )
            if( deviceName.substr(0, deviceName.length()) == "tty.usbmodem1421" ||
               deviceName.substr(0, deviceName.length()) == "cu.usbmodem1421" )
            {
                std::cout << "serial device[" << deviceCount << "]: " << deviceName << std::endl;
                
                // Add to list of devices
                mDeviceList.push_back("/dev/" + deviceName);
                deviceCount++;
            }
            
        }
        
        // Close the serial devices directory
        closedir(dir);
    }
}

////////////////////////////////////////////////////
// Connect to serial device                       //
////////////////////////////////////////////////////
bool UVProcessingUnit::connect(int indx, int baud)
{
    printf("Connecting to serial port: %i\n", indx);
    
    // If indx is valid
    if( indx <  mDeviceList.size() )
    {
        // Open connection
        mConnection = open( mDeviceList[indx].c_str() , O_RDWR | O_NOCTTY | O_NDELAY);
        
        if (mConnection == -1)
        {
            printf("Unable to open port.\n");
        }
        else
        {
            printf("Port opened.\n");
            
            // Set connection parameters
            struct termios options;
            
            cfsetispeed(&options, B9600);
            cfsetospeed(&options, B9600);
            
            options.c_cflag |= (CLOCAL | CREAD);
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            options.c_cflag &= ~CSIZE;
            options.c_iflag &= (tcflag_t) ~(INLCR | IGNCR | ICRNL | IGNBRK);
            options.c_oflag &= (tcflag_t) ~(OPOST);
            options.c_cflag |= CS8;
            tcsetattr(mConnection, TCSANOW, &options);
            
            // Start the update function running in the background so that it does not block the main loop
            mThread = new std::thread(&UVProcessingUnit::updateAsThread, this);
        }
    }
    
    // Return true if we connected otherwise return false
    if(mConnection == -1)
        return false;
    else
        return true;
}

////////////////////////////////////////////////////
// Find the arduino device to connect to          //
////////////////////////////////////////////////////
bool UVProcessingUnit::connectArduino()
{
    mConnected = false;
    
    // Go through all the devices and find the arduino board
    for(int i = 0; i < mDeviceList.size() ; i++)
    {
        // Connect to first arduino device
        if(mDeviceList[i].substr(0,18) == "/dev/cu.usbmodem14")
        {
            mConnected = connect(i, BAUD_RATE);
        }
    }
    
    // Display message on console
    if(mConnected)
    {
        printf("Connected to UV Processing Unit\n");
    }else{
        printf("Couldn't connect to UV Processing Unit\n");
    }
    
    return mConnected;
}

////////////////////////////////////////////////////
// Update function that runs in the background    //
////////////////////////////////////////////////////
void UVProcessingUnit::updateAsThread()
{
    mThreadRunning = true;
    
    int bitIndx = 0;
    
    // This stores our 32 bit random seed (each unsigned char is 8 bits)
    
    // Loop until the thread is closed
    while(mThreadRunning)
    {
        // Read in some data from the serial connection
        unsigned char tmp;
        
        int nRead = read(mConnection, &tmp, 1);
        
        // If there is some data to read
        if(nRead > 0  && tmp != '\n')
        {
            //mDetectedDecay=true;
            //printf("detected decay!\n");
            // Save the data in our array
            //tmpByte[bitIndx] = tmp;
            
            int val = (int)tmp;
            
            int ldrIndx = val / 10;
            
            mLDRvalues[ldrIndx] = val - ldrIndx * 10;
            
            
            
        }
        
        
        // Sleep for one second to allow other processes time to run
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }
}

int * UVProcessingUnit::getLDRValues()
{
    return mLDRvalues;
}

////////////////////////////////////////////////////
// Test if the QSPU is connected                  //
////////////////////////////////////////////////////
bool UVProcessingUnit::isConnected()
{
    return mConnected;
}