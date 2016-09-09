//
//  Quantum.h
//  QuantumTest
//
//  Created by jayson on 5/11/2015.
//
//


#pragma once

#include <stdio.h>

#include <iostream>
#include <complex>
#include <ctime>
#include <dlib/quantum_computing.h>
#include <dlib/string.h>


using namespace std;
using namespace dlib;

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

// This declares a random number generator that we will be using below
extern dlib::rand rndm;
extern long searchVal;
// ----------------------------------------------------------------------------------------

void setSearchVal(long val);

void shor_encode (
                  quantum_register& reg
                  );

// ----------------------------------------------------------------------------------------

void shor_decode (
                  quantum_register& reg
                  );

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

// This is the function we will use in Grover's search algorithm.  In this
// case the value we are searching for is 257.
bool is_key (unsigned long n);

// ----------------------------------------------------------------------------------------

template <int bits> class uf_gate;

namespace dlib {
    template <int bits>
    struct gate_traits<uf_gate<bits> >
    {
        static const long num_bits = bits;
        static const long dims = dlib::qc_helpers::exp_2_n<num_bits>::value;
    };}

template <int bits>
class uf_gate : public gate_exp<uf_gate<bits> >
{
    /*!
     This gate represents the black box function in Grover's search algorithm.
     That is, it is the gate defined as follows:
     Uf|x>|y> = |x>|y XOR is_key(x)>
     
     See the documentation for the gate_exp object for the details regarding
     the compute_state_element() and operator() functions defined below.
     !*/
public:
    uf_gate() : gate_exp<uf_gate>(*this) {}
    
    static const long num_bits = gate_traits<uf_gate>::num_bits;
    static const long dims = gate_traits<uf_gate>::dims;
    
    const qc_scalar_type operator() (long r, long c) const
    {
        unsigned long output = c;
        // if the input control bit is set
        if (is_key(output>>1))
        {
            output = output^0x1;
        }
        
        if ((unsigned long)r == output)
            return 1;
        else
            return 0;
    }
    
    template <typename exp>
    qc_scalar_type compute_state_element (
                                          const matrix_exp<exp>& reg,
                                          long row_idx
                                          ) const
    {
        unsigned long output = row_idx;
        // if the input control bit is set
        if (is_key(output>>1))
        {
            output = output^0x1;
        }
        
        return reg(output);
    }
};

// ----------------------------------------------------------------------------------------

template <int bits>
class w_gate;

namespace dlib {
    template <int bits>
    struct gate_traits<w_gate<bits> >
    {
        static const long num_bits = bits;
        static const long dims = dlib::qc_helpers::exp_2_n<num_bits>::value;
    }; }

template <int bits>
class w_gate : public gate_exp<w_gate<bits> >
{
    /*!
     This is the W gate from the Grover algorithm
     !*/
public:
    
    w_gate() : gate_exp<w_gate>(*this) {}
    
    static const long num_bits = gate_traits<w_gate>::num_bits;
    static const long dims = gate_traits<w_gate>::dims;
    
    const qc_scalar_type operator() (long r, long c) const
    {
        qc_scalar_type res = 2.0/dims;
        if (r != c)
            return res;
        else
            return res - 1.0;
    }
    
    template <typename exp>
    qc_scalar_type compute_state_element (
                                          const matrix_exp<exp>& reg,
                                          long row_idx
                                          ) const
    {
        qc_scalar_type temp = sum(reg)*2.0/dims;
        // compute this value: temp = temp - reg(row_idx)*2.0/dims + reg(row_idx)*(2.0/dims - 1.0)
        temp = temp - reg(row_idx);
        
        return temp;
    }
};
