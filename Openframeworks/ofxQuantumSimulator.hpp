//
//  ofxQuantumSimulator.hpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 07/09/2016.
//
//

#ifndef ofxQuantumSimulator_hpp
#define ofxQuantumSimulator_hpp


#include "Quantum.hpp"
#include "ofxQuantumTypes.h"

#define NUM_BITS 8

class ofxQuantumSimulator
{
    
public:
    
    ofxQuantumSimulator();
    
    void init(int numBits);
    
    
    // Get the dlib quantum register
    QuantumRegister * getQuantumRegister();
    
    void setState(  int bitIndx, int state  );
    
    void resetBits();
    
    // Apply gates to bits
    void applyGatePauliX(   int bitIndx  );
    void applyGatePauliY(   int bitIndx  );
    void applyGatePauliZ(   int bitIndx  );
    void applyGateHadamard( int bitIndx  );
    void applyGateCnot(     int cntlBit,
                       int trgtBit  );
    void applyNoOp(         int bitIndx  );
    void applyUfGate();
    void applyWGate();
    
    int           testBit(int bitIndx);
    int           measureBit(int bitIndx);
    double        getProbability(int bitIndx);
    int           getNumBits();
    QubitStateMat getScalar(int bitIndx);
    
    void          resetOperations();
    void          runOperations();
    
private:
    void applyOperation(gate<1> * operationToApply, int bitIndx);
    
    QuantumRegister mRegister;
    
    
    
    gate<1> mOperationX = quantum_gates::x();
    gate<1> mOperationY = quantum_gates::y();
    gate<1> mOperationZ = quantum_gates::z();
    gate<1> mOperationH = quantum_gates::hadamard();
    gate<1> mOperationN = quantum_gates::noop();
    gate<1> * mOpsToApply[NUM_BITS];
    
    
    int mNumBits;
    
};

#endif /* ofxQuantumSimulator_hpp */
