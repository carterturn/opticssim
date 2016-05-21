#pragma once

#include "light.h"
#include "photon.h"
#include <vector>

class qed : public light{
public:
qed(tsvector origin, mpf_class wavelength) : light(origin, wavelength){
		photons = std::vector<photon*>();
}
	~qed();

	int calculate(std::vector<object*> objects, mpf_class density, int depth);

#ifdef GRAPHICS
	void draw();
#endif
protected:
	std::vector<photon*> photons;
};
