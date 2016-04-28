#pragma once

#include <gmpxx.h>

class vector2d{
public:
vector2d(mpf_class x, mpf_class y) : x(x), y(y){}
	vector2d(){
		x = 0;
		y = 0;
	}

	vector2d operator+ (const vector2d& param);
	vector2d operator- (const vector2d& param);
	mpf_class operator* (const vector2d& param);

	vector2d operator* (const mpf_class& scalar);

	mpf_class abs();

protected:
	mpf_class x;
	mpf_class y;


};

mpf_class abs(vector2d input);

class clock{
public:
clock(mpf_class angle) : angle(angle){}

	static mpf_class get_angle(mpf_class wavelength, mpf_class distance);
	void turn(mpf_class angle);

	vector2d get_arrow();

protected:
	mpf_class angle;
};
