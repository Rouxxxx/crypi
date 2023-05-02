#include "matrix.hh"

int rand_dgauss(double stddev) {
    static std::default_random_engine engine;
    static std::binomial_distribution<int> dist(2 * std::ceil(stddev) + 1, 0.5);
    int x = dist(engine) - dist(engine);
    return x;
}

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

int Matrix::get_n() { return n; }
int Matrix::get_value(int i, int j) { return mat[i][j]; }