#ifndef VECTOR_HH
#define VECTOR_HH

#include <vector>
#include <random>
#include <iostream>

#include "matrix.hh"

class Random_vector
{
    public:
        Random_vector(int n, int min_val, int max_val);
        int get_n();
        int at(int i);
        std::vector<int> project_onto_basis(Matrix basis);
    
    private:
        std::vector<int> vec;
        const int n;
};

#endif