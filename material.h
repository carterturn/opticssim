#pragma once

#include <gmpxx.h>

class material{
public:
material(mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : reflectance(reflectance), transmittance(transmittance), lightspeed(lightspeed){}

	mpf_class get_lightspeed(){
		return lightspeed;
	}

	mpf_class get_reflectance(){
		return reflectance;
	}

	mpf_class get_transmittance(){
		return transmittance;
	}
	
protected:
	mpf_class reflectance;
	mpf_class transmittance;

	mpf_class lightspeed;
};
