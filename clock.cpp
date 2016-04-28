#include "clock.h"

mpf_class clock::get_angle(mpf_class wavelength, mpf_class distance){
	// tau = 1 wavelength
	return tau * ((distance - floor(distance / wavelength)) / wavelength);
}
