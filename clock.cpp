#include "clock.h"
#include "constant.h"

#include <cmath>

mpf_class clock::get_angle(mpf_class wavelength, mpf_class distance){
	// tau = 1 wavelength
	return cnst::tau * ((distance - floor(distance / wavelength)) / wavelength);
}

void clock::turn(mpf_class delta_angle){
	if(abs(delta_angle) > cnst::tau){
		delta_angle = delta_angle - cnst::tau * floor(delta_angle / cnst::tau);
	}
	angle = angle + delta_angle;
	if(abs(angle) > cnst::tau){
		angle = angle - cnst::tau * floor(angle / cnst::tau);
	}
}

vector2d clock::get_arrow(){
	return vector2d(cos(angle.get_d()), sin(angle.get_d()));
}

mpf_class clock::get_angle(){
	return angle;
}
