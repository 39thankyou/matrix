#include <tuple>
#include "vector_matrix.h"

using namespace std;

int main() {
    vector_matrix<double> matrix1{{{1}, {2}, {3}, {4}}};
    vector_matrix<double> matrix2{{{1, 2, 3, 4}}};
    cout << "matrix1: \n" << matrix1 << endl;
    cout << "matrix2: \n" << matrix2 << endl;
    cout << "------------------------------\n";
    cout << "matrix1 + matrix2: \n" << matrix1 + matrix2 << endl;
    cout << "------------------------------\n";
    cout << "matrix1 - matrix2: \n" << matrix1 - matrix2 << endl;
    cout << "------------------------------\n";
    cout << "matrix1 * matrix2: \n" << matrix1 * matrix2 << endl;
    cout << "------------------------------\n";
    cout << "matrix2 * matrix1: \n" << matrix2 * matrix1 << endl;
    cout << "------------------------------\n";
    cout << "matrix1 rotation:\n";
    matrix1.rotation_matrix();
    cout << matrix1 << endl;
}