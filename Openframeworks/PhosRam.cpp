//
//  PhosRam.cpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 05/09/2016.
//
//

#include "PhosRam.hpp"


void PhosRam::init()
{
    mEtherdream.setup();
    mEtherdream.setPPS( LASER_PPS );
    
    mCorners[0] = ofVec2f( 114.0 / 800.0,  27.0 / 600.0);
    mCorners[1] = ofVec2f( 794.0 / 800.0,  31.0 / 600.0);
    mCorners[2] = ofVec2f( 776.0 / 800.0, 563.0 / 600.0);
    mCorners[3] = ofVec2f(  94.0 / 800.0, 537.0 / 600.0);
    
    mCalibrationScan = 0.0;
    
    mode = MODE_CALIBRATION;
}

void PhosRam::update( bool decayDetected)
{
    mIldaFrame.clear();
    mIldaFrame.addPoly();
    mIldaFrame.getLastPoly().color = ofFloatColor(1.0,1.0,1.0);
    
    
    if(mode ==  MODE_CALIBRATION)
    {
        ofVec2f src[4];
        src[0] = ofVec2f( 0,   0   );
        src[1] = ofVec2f( 1.0, 0   );
        src[2] = ofVec2f( 1.0, 1.0 );
        src[3] = ofVec2f( 0,   1.0 );
            
        ofMatrix4x4 h = findHomography( src, mCorners );
        
        if(mCalibrationScan < PI)
        {
            
            if(bootMode == 0)
            {
                ofVec3f p1 = ofVec3f(0.0, abs( sin( mCalibrationScan ) ), 0 ) ;
                ofVec3f p2 = ofVec3f(1.0, abs( sin( mCalibrationScan ) ), 0 )  ;
                
                p1 = p1 * h;
                p2 = p2 * h;
                
                
                mIldaFrame.getLastPoly().lineTo( p1.x, p1.y );
                mIldaFrame.getLastPoly().lineTo( p2.x, p2.y );
            }else if (bootMode == 1)
            {
                float t = 0.5 * abs( sin( mCalibrationScan ) );
                ofVec3f p1 = ofVec3f(0.5-t,0.5-t,0 );
                ofVec3f p2 = ofVec3f(0.5+t,0.5-t,0 );
                ofVec3f p3 = ofVec3f(0.5+t,0.5+t,0 );
                ofVec3f p4 = ofVec3f(0.5-t,0.5+t,0 );
                
                
                p1 = p1 * h;
                p2 = p2 * h;
                p3 = p3 * h;
                p4 = p4 * h;
                
                
                mIldaFrame.getLastPoly().lineTo( p1.x, p1.y );
                mIldaFrame.getLastPoly().lineTo( p2.x, p2.y );
                
                mIldaFrame.getLastPoly().lineTo( p3.x, p3.y );
                mIldaFrame.getLastPoly().lineTo( p4.x, p4.y );
                mIldaFrame.getLastPoly().lineTo( p1.x, p1.y );
            }
            mCalibrationScan += 0.025;
            
            if(mCalibrationScan > PI)
            {
                mode = MODE_RUNNING;
                mCalibrationScan = 0.0;
                
                bootMode = abs(bootMode-1);
            }
        }
        
    }else if( mode == MODE_RUNNING)
    {
        if( decayDetected )
        {
            float w = ofRandom(0, 0.1);
            float randX = ofRandom(0,1-w);
            float randY = ofRandom(0,1);
            
                
            mIldaFrame.getLastPoly().lineTo(randX, randY);
            mIldaFrame.getLastPoly().lineTo(randX+w, randY);
        }
    }
    
    mIldaFrame.update();
    
    mEtherdream.setPoints(mIldaFrame);
    
    
    
    
}

void PhosRam::draw()
{
    mIldaFrame.draw( 0, 0, ofGetWidth(), ofGetHeight()  );
}

ofMatrix4x4 PhosRam::findHomography(ofVec2f src[4], ofVec2f dst[4])
{
    
    ofMatrix4x4 homography;
    
    // create the equation system to be solved
    //
    // from: Multiple View Geometry in Computer Vision 2ed
    //       Hartley R. and Zisserman A.
    //
    // x' = xH
    // where H is the homography: a 3 by 3 matrix
    // that transformed to inhomogeneous coordinates for each point
    // gives the following equations for each point:
    //
    // x' * (h31*x + h32*y + h33) = h11*x + h12*y + h13
    // y' * (h31*x + h32*y + h33) = h21*x + h22*y + h23
    //
    // as the homography is scale independent we can let h33 be 1 (indeed any of the terms)
    // so for 4 points we have 8 equations for 8 terms to solve: h11 - h32
    // after ordering the terms it gives the following matrix
    // that can be solved with gaussian elimination:
    
    float P[8][9]={
        {-src[0].x, -src[0].y, -1,   0,   0,  0, src[0].x*dst[0].x, src[0].y*dst[0].x, -dst[0].x }, // h11
        {  0,   0,  0, -src[0].x, -src[0].y, -1, src[0].x*dst[0].y, src[0].y*dst[0].y, -dst[0].y }, // h12
        
        {-src[1].x, -src[1].y, -1,   0,   0,  0, src[1].x*dst[1].x, src[1].y*dst[1].x, -dst[1].x }, // h13
        {  0,   0,  0, -src[1].x, -src[1].y, -1, src[1].x*dst[1].y, src[1].y*dst[1].y, -dst[1].y }, // h21
        
        {-src[2].x, -src[2].y, -1,   0,   0,  0, src[2].x*dst[2].x, src[2].y*dst[2].x, -dst[2].x }, // h22
        {  0,   0,  0, -src[2].x, -src[2].y, -1, src[2].x*dst[2].y, src[2].y*dst[2].y, -dst[2].y }, // h23
        
        {-src[3].x, -src[3].y, -1,   0,   0,  0, src[3].x*dst[3].x, src[3].y*dst[3].x, -dst[3].x }, // h31
        {  0,   0,  0, -src[3].x, -src[3].y, -1, src[3].x*dst[3].y, src[3].y*dst[3].y, -dst[3].y }, // h32
    };
    
    gaussian_elimination(&P[0][0],9);
    
    // gaussian elimination gives the results of the equation system
    // in the last column of the original matrix.
    // opengl needs the transposed 4x4 matrix:
    homography = ofMatrix4x4( P[0][8],P[3][8],0,P[6][8], // h11  h21 0 h31
        P[1][8],P[4][8],0,P[7][8], // h12  h22 0 h32
        0      ,      0,0,0,       // 0    0   0 0
        P[2][8],P[5][8],0,1);      // h13  h23 0 h33
    
    
    return homography;
}

void PhosRam::gaussian_elimination(float *input, int n){
    // ported to c from pseudocode in
    // http://en.wikipedia.org/wiki/Gaussian_elimination
    
    float * A = input;
    int i = 0;
    int j = 0;
    int m = n-1;
    while (i < m && j < n){
        // Find pivot in column j, starting in row i:
        int maxi = i;
        for(int k = i+1; k<m; k++){
            if(fabs(A[k*n+j]) > fabs(A[maxi*n+j])){
                maxi = k;
            }
        }
        if (A[maxi*n+j] != 0){
            //swap rows i and maxi, but do not change the value of i
            if(i!=maxi)
                for(int k=0;k<n;k++){
                    float aux = A[i*n+k];
                    A[i*n+k]=A[maxi*n+k];
                    A[maxi*n+k]=aux;
                }
            //Now A[i,j] will contain the old value of A[maxi,j].
            //divide each entry in row i by A[i,j]
            float A_ij=A[i*n+j];
            for(int k=0;k<n;k++){
                A[i*n+k]/=A_ij;
            }
            //Now A[i,j] will have the value 1.
            for(int u = i+1; u< m; u++){
                //subtract A[u,j] * row i from row u
                float A_uj = A[u*n+j];
                for(int k=0;k<n;k++){
                    A[u*n+k]-=A_uj*A[i*n+k];
                }
                //Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
            }  
            
            i++;  
        }  
        j++;  
    }  
    
    //back substitution  
    for(int i=m-2;i>=0;i--){  
        for(int j=i+1;j<n-1;j++){  
            A[i*n+m]-=A[i*n+j]*A[j*n+m];  
            //A[i*n+j]=0;  
        }  
    }  
}


void PhosRam::enterCalibrationMode()
{
    mode = MODE_CALIBRATION; 
}
