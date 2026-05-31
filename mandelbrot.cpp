#include "mandelbrot.h"
using namespace std;

int mandelbrot(double x, double y, int maxIter) 
{
	complex<double> c(x,y);
	complex<double> z(0.0, 0.0);

	int iter = 0;

	while (abs(z) <= 2.0 && iter < maxIter)
	{
		z = z * z + c;
		iter++;
	}
	return iter;
}