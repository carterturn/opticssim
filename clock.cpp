#include "clock.h"
#include "constant.h"

mpf_class clock::get_angle(mpf_class wavelength, mpf_class distance){
	// tau = 1 wavelength
	return cnst::tau * ((distance - floor(distance / wavelength)) / wavelength);
}
