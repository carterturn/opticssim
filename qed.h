#pragma once

#include "light.h"
#include "photon.h"
#include <vector>



class qed : public light{
public:
qed(tsvector origin, tsvector destination, mpf_class wavelength) : origin(origin), destination(destination), light(wavelength){
		photons = std::vector<photon*>();
		points = std::vector<object_point*>();

}
	~qed();

	int calculate(std::vector<object*> objects, mpf_class density, int depth);

#ifdef GRAPHICS
	void draw();
#endif
protected:
	std::vector<photon*> photons;
	std::vector<object_point*> points; // Since there are pointers, this needs to be saved

	tsvector origin;
	tsvector destination;
};
