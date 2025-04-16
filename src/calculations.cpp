#include "calculations.h"
#include <cmath>
#include <cstdio>

const double c = 299792458;
const double h = 6.62607015e-34;
const double k = 1.380649e-23;

double intensity(double temperature, double wavelength) {
	if (wavelength == 0 || temperature == 0) return 0.0;

	return (2 * h * c) / std::pow(wavelength, 5) * exp(-(h * c) / ((double) wavelength * k * (double) temperature));
}