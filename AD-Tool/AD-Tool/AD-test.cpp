#include <iostream>
#include "AD.h"

int main() {
	sym::scalar<double> a(1), b(2);
	sym::var<double> x(1), y(1), z(1);
	sym::VAL<double> v;
	sym::AD<double> F, G, H, T;
	sym::pNode<double> U;

	F = (1.0 + 2.0) / ((x * x) / ((x + y) * z) + 1.0);
	F.disp();

	U = 1.0;

	G = U + 1.0;
	G.disp(1);

	std::cout << std::endl;

	U = x;
	G.disp(1);

	std::cout << std::endl;
	
	U = F;
	G.disp(1);

	std::cout << std::endl;
	T = F + 1.0;
	T.disp(1);

	std::cout << std::endl;
	H = copyAD(G);
	H.disp(1);
	

	return 0;
}
