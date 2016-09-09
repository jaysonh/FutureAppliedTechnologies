#include "Quantum.hpp"

dlib::rand rndm;
long searchVal = 253;

void setSearchVal(long val)
{
    searchVal = val;
}

bool is_key (unsigned long n)
{
    return n == searchVal;
    //return n == 259;
    //return n == 257;
}

void shor_encode (
                  quantum_register& reg
                  )
/*!
 requires
 - reg.num_bits() == 1
 ensures
 - #reg.num_bits() == 9
 - #reg == the Shor error coding of the input register
 !*/
{
    DLIB_CASSERT(reg.num_bits() == 1,"");
    
    quantum_register zeros;
    zeros.set_num_bits(8);
    reg.append(zeros);
    
    using namespace dlib::quantum_gates;
    const gate<1> h = hadamard();
    const gate<1> i = noop();
    
    // Note that the expression (h,i) represents the tensor product of the 1 qubit
    // h gate with the 1 qubit i gate and larger versions of this expression
    // represent even bigger tensor products.  So as you see below, we make gates
    // big enough to apply to our quantum register by listing out all the gates we
    // want to go into the tensor product and then we just apply the resulting gate
    // to the quantum register.
    
    // Now apply the gates that constitute Shor's encoding to the input register.
    (cnot<3,0>(),i,i,i,i,i).apply_gate_to(reg);
    (cnot<6,0>(),i,i).apply_gate_to(reg);
    (h,i,i,h,i,i,h,i,i).apply_gate_to(reg);
    (cnot<1,0>(),i,cnot<1,0>(),i,cnot<1,0>(),i).apply_gate_to(reg);
    (cnot<2,0>(),cnot<2,0>(),cnot<2,0>()).apply_gate_to(reg);
}


void shor_decode (
                  quantum_register& reg
                  )
/*!
 requires
 - reg.num_bits() == 9
 ensures
 - #reg.num_bits() == 1
 - #reg == the decoded qubit that was in the given input register
 !*/
{
    DLIB_CASSERT(reg.num_bits() == 9,"");
    
    using namespace dlib::quantum_gates;
    const gate<1> h = hadamard();
    const gate<1> i = noop();
    
    // Now apply the gates that constitute Shor's decoding to the input register
    
    (cnot<2,0>(),cnot<2,0>(),cnot<2,0>()).apply_gate_to(reg);
    (cnot<1,0>(),i,cnot<1,0>(),i,cnot<1,0>(),i).apply_gate_to(reg);
    
    (toffoli<0,1,2>(),toffoli<0,1,2>(),toffoli<0,1,2>()).apply_gate_to(reg);
    
    (h,i,i,h,i,i,h,i,i).apply_gate_to(reg);
    
    (cnot<6,0>(),i,i).apply_gate_to(reg);
    (cnot<3,0>(),i,i,i,i,i).apply_gate_to(reg);
    (toffoli<0,3,6>(),i,i).apply_gate_to(reg);
    
    // Now that we have decoded the value we don't need the extra 8 bits any more so
    // remove them from the register.
    for (int i = 0; i < 8; ++i)
        reg.measure_and_remove_bit(0,rndm);
}