#include <iostream>
#include "AD.h"

int main() {
	scalar<double> a(1), b(2);
	var<double> x(1), y(1), z(1);
	VAL<double> v;
	AD<double> F, G, H, T;
	gNode<double> U;

	F = (1.0 + 2.0) / ((x * x) / ((x + y) * z) + 1.0);
	F.disp();

	U = 1.0;

	G = U + 1.0;
	G.disp(1);

	cout << endl;

	U = x;
	G.disp(1);

	cout << endl;

	U = F;
	G.disp(1);

	cout << endl;
	T = F + 1.0;
	T.disp(1);

	cout << endl;
	H = copyAD(G);
	H.disp(1);

	return 0;
}
