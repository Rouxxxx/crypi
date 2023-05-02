#include "../math/math.hh"
#include <cstdlib>

int main()
{
    // Matrix dimension : large enough to make it hard to solve, 
    // but small enough to be able to compute it
    int n = 256;


    // modulus of the sheme : same considerations as with n
    // k has to be a multiple of 8
    int k = 256;
    int q = pow(2, k) + 1;

    std::cout << "Computing A...";
    Matrix A(n, 3.2);
    std::cout << "A computed !\n";


    std::cout << "Computing s...";
    Random_vector s(n, -k, k);
    std::cout << "s computed !\n";

    // Generate identity matrix of size n w n
    Matrix basis(n);
    for (int i = 0; i < n; i++) {
        basis.set_val(1, i, i);
    }

    std::cout << "Computing projection...";
    std::vector<int> new_s = s.project_onto_basis(basis);
    std::cout << "projection computed !\n";

    return 0;
}