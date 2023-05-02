#include "vector.hh"

Random_vector::Random_vector(int n, int min_val, int max_val)
    : n(n)
{
    vec = std::vector<int>(n);

    std::random_device rd;                                          // obtain a random seed from hardware
    std::mt19937 gen(rd());                                     // seed the generator
    std::uniform_int_distribution<> distrib(min_val, max_val);// set boundaries


    for (int i = 0; i < n; i++) {
        vec[i] = distrib(gen);
    }
}

// project a vector onto the ideal lattice basis
std::vector<int> Random_vector::project_onto_basis(Matrix basis)
{
    int basis_n = basis.get_n();
    std::vector<int> result(vec.size(), 0);

    for (int i = 0; i < basis_n; i++) {
        int dot_product = 0;

        for (int j = 0; j < basis_n; j++) {
            dot_product += vec[j] * basis.at(i, j);
        }
        for (int j = 0; j < basis_n; j++) {
            result[j] += dot_product * basis.at(i, j);
        }
    }
    return result;
}

int Random_vector::get_n() { return n; }
int Random_vector::at(int i) { return vec[i]; }