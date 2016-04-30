#pragma once

#include <gmpxx.h>

class material{
public:
material(mpf_class reflectance, mpf_class transmittance) : reflectance(reflectance), transmittance(transmittance){}
protected:
	mpf_class reflectance;
	mpf_class transmittance;
};
