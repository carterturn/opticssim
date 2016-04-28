#pragma once

#include <vector>

class light {
public:
light(tsvector origin, mpf_class wavelength) : origin(origin), freq(wavelength){}
	
	virtual bool is_valid() = 0;
	virtual bool interact() = 0;

	virtual int calculate(std::vector<*object> objects) = 0;

#ifdef GRAPHICS
	virtual void draw() = 0;
#endif

protected:
	tsvector origin;
	mpf_class wavelength;
};
