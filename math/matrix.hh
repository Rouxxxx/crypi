#ifndef MATRIX_HH
#define MATRIX_HH

#include <vector>
#include <cmath>
#include <random>
#include <iostream>

class Matrix
{
    public:
        Matrix(int n);
        Matrix(int n, double stddev);
        void set_val(int n, int i, int j);
        int get_n();
        int at(int i, int j);
    private:
        std::vector<std::vector<int>> mat;
        const int n;
};

// Matrix's pretty print
inline std::ostream& operator<<(std::ostream& os, Matrix& mat)
{
    int n = mat.get_n();
    for (int i = 0; i < n; i++)
    {
        os << mat.at(i, 0);
        for (int j = 1 ; j < n; j++)
        {
            os << " " << mat.at(i, j);
        }
        os << std::endl;
    }
    return os;
}

#endif