//
//  ofxQuantumSimulator.cpp
//  FutureAppliedTechnologiesShowcase
//
//  Created by Jayson Haebich on 07/09/2016.
//
//

#include "ofxQuantumSimulator.hpp"



ofxQuantumSimulator::ofxQuantumSimulator()
{
    mRegister.set_num_bits(NUM_BITS);
    
    
}

void ofxQuantumSimulator::init(int numBits)
{
    
    mRegister.set_num_bits(NUM_BITS);
    
    mNumBits = numBits;
}

int ofxQuantumSimulator::getNumBits()
{
    return mNumBits;
}

QuantumRegister * ofxQuantumSimulator::getQuantumRegister()
{
    return & mRegister;
}

void ofxQuantumSimulator::applyUfGate()
{
    (uf_gate<NUM_BITS>()).apply_gate_to(mRegister);
    
}

void ofxQuantumSimulator::applyWGate()
{
    
    (w_gate<NUM_BITS-1>(),mOperationN).apply_gate_to(mRegister);
}


double ofxQuantumSimulator::getProbability(int bitIndx)
{
    return mRegister.probability_of_bit(bitIndx);
}

void ofxQuantumSimulator::applyGatePauliX(int bitIndx)
{
    applyOperation(&mOperationX, bitIndx);
}

void ofxQuantumSimulator::applyGatePauliY(int bitIndx)
{
    applyOperation(&mOperationY, bitIndx);
}


void ofxQuantumSimulator::applyGatePauliZ( int bitIndx )
{
    applyOperation(&mOperationZ, bitIndx);
    
}


void ofxQuantumSimulator::applyNoOp( int bitIndx  )
{
    applyOperation(&mOperationN, bitIndx );
}
void ofxQuantumSimulator::setState( int bitIndx, int state )
{
    if( mRegister.measure_bit(bitIndx, rndm) != state)
    {
        applyGatePauliX(bitIndx);
    }
}

void ofxQuantumSimulator::resetOperations()
{
    //cout << "reseting operationgs\n";
    for(int i = 0; i < NUM_BITS;i++)
    {
        mOpsToApply[i] = &mOperationN;
    }
}

void ofxQuantumSimulator::runOperations()
{
    //printf("running operations\n");
    
    //for(int i = 0; i < 10;i++)
    //    cout << "op[" << i << "]: " << mOpsToApply[i] << endl;
    
    (
     *mOpsToApply[7],
     *mOpsToApply[6],
     *mOpsToApply[5],
     *mOpsToApply[4],
     *mOpsToApply[3],
     *mOpsToApply[2],
     *mOpsToApply[1],
     *mOpsToApply[0]).apply_gate_to(mRegister);
}
void ofxQuantumSimulator::applyOperation(gate<1> * operationToApply, int bitIndx)
{
    
    //cout << "applying operation on bit " << bitIndx << ": " << operationToApply <<endl;
    resetOperations();
    
    
    
    
    mOpsToApply[bitIndx] = operationToApply;
    
    
    
    runOperations();
    
    
}

void ofxQuantumSimulator::applyGateCnot(int control_bit, int target_bit)
{
    gate<1>  cnotGate = quantum_gates::cnot2(control_bit);
    
    applyOperation(&cnotGate, target_bit);
    
    
    
    
    
}

void ofxQuantumSimulator::applyGateHadamard(int bitIndx)
{
    applyOperation(&mOperationH, bitIndx);
    
}

QubitStateMat ofxQuantumSimulator::getScalar(int bitIndx)
{
    for(int i = 0; i < mRegister.state_vector().size() && i < std::pow((float)2, (float)mNumBits); i++)
    {
        printf("%i: %f %f\n", i, mRegister.state_vector()(i).real(), mRegister.state_vector()(i).imag());
        
    }
    
    return mRegister.state_vector();
}

// Measureing the bit forces it into a state
int ofxQuantumSimulator::measureBit(int bitIndx)
{
    return mRegister.measure_bit(bitIndx,rndm);
}

// Test bit measures the state of the bit without effecting its probability, this is technically not part of the specification
// for quantum computing but is useful for visualising bits during quantum operations
int ofxQuantumSimulator::testBit(int bitIndx)
{
    if(rndm.get_random_float() < getProbability(bitIndx))
        return 1;
    else
        return 0;
}
void ofxQuantumSimulator::resetBits()
{
    mRegister.zero_all_bits();
}
