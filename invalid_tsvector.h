#pragma once

#include "tsvector.h"

class invalid_tsvector : public tsvector {
public:
	invalid_tsvector() : tsvector(){}

	tsvector rotate(double tx, double ty, double tz);
	mpf_class norm();
	tsvector normalize();
	bool is_valid();
	
	tsvector operator+ (const tsvector& param);
	tsvector operator- (const tsvector& param);
	mpf_class operator* (const tsvector& param);

	tsvector operator* (const int& scalar);
	tsvector operator* (const double& scalar);
	tsvector operator* (const float& scalar);
	tsvector operator* (const mpf_class& scalar);

#ifdef GRAPHICS
	void draw();
#endif
};