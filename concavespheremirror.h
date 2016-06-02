#pragma once

#include "concavesphere.h"
#include "mirror.h"

class concavespheremirror : public concavesphere, public mirror {
public:
concavespheremirror(tsvector center, mpf_class radius, mpf_class height, tsvector rot) : concavesphere(center, radius, height, rot), mirror() {}
	std::vector<tsvector> get_points(mpf_class density){
		return concavesphere::get_points(density);
	}
	tsvector get_surface_normal(tsvector point){
		return concavesphere::get_surface_normal(point);
	}
	tsvector get_intersection(photon* incident_photon){
		return concavesphere::get_intersection(incident_photon);
	}
	photon* get_redirected_photon(photon* incident_photon){
		return mirror::get_redirected_photon(incident_photon);
	}
};
