#include "matrix.hh"

// Discrete Gaussian distribution:
// Discrete version of the Gaussian distribution
// used for sampling the noise term in a lattice-based encryption scheme.
// (make it harder to decrypt) 

int rand_dgauss(double stddev) {
    static std::default_random_engine engine;
    static std::binomial_distribution<int> dist(2 * std::ceil(stddev) + 1, 0.5);
    int x = dist(engine) - dist(engine);
    return x;
}

// First matrix constructor
// returns a n x n matrix filled with zeros

Matrix::Matrix(int n)
    : n(n)
{
    mat = std::vector<std::vector<int>>(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = 0;
        }
    }
}


// Second matrix constructor
// We directly create the n x n matrix A (used to generate the public key)
// We use small entries (-1, 0 or 1) to ensure that the lattice is hard to solve
// We use the discrete Gaussian distribution as it's a common choice to generate A 

Matrix::Matrix(int n, double stddev)
    : n(n)
{
    mat = std::vector<std::vector<int>>(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand_dgauss(stddev);
        }
    }
}

void Matrix::set_val(int n, int i, int j)
{
    mat[i][j] = n;
}

int Matrix::get_n() { return n; }
int Matrix::at(int i, int j) { return mat[i][j]; }