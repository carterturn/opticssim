#pragma once

#include <gmpxx.h>

class material{
public:
material(mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : reflectance(reflectance), transmittance(transmittance), lightspeed(lightspeed){}

	mpf_class get_lightspeed(){
		return lightspeed;
	}
	
protected:
	mpf_class reflectance;
	mpf_class transmittance;

	mpf_class lightspeed;
};
