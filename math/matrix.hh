#ifndef MATRIX_HH
#define MATRIX_HH

#include <vector>
#include <cmath>
#include <random>
#include <iostream>

class Matrix
{
    public:
        Matrix(int n, double stddev);
        int get_n();
        int get_value(int i, int j);
    private:
        std::vector<std::vector<int>> mat;
        const int n;
};

inline std::ostream& operator<<(std::ostream& os, Matrix& mat)
{
    int n = mat.get_n();
    for (int i = 0; i < n; i++)
    {
        os << mat.get_value(i, 0);
        for (int j = 1 ; j < n; j++)
        {
            os << " " << mat.get_value(i, j);
        }
        os << std::endl;
    }
    return os;
}

#endif