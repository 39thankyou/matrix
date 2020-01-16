#include"matrix_structure.h"
#include"adjacent_list.h"
#include"vector_matrix.h"
using namespace std;

int main()
{
	adjacent_list_matrix<int> r1(3,1);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 1; j++)
			r1.get(i, j) = 1;
	vector_matrix<int> r2(1, 3);
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 3; j++)
			r2.get(i, j) = 1;
	cout << r1 << endl;
	cout << r2 << endl;
	r1*=r2;
	cout << r1;
	system("pause");
}