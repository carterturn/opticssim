#pragma once

#include "convexsphere.h"
#include "mirror.h"

class convexspheremirror : public convexsphere, public mirror {
public:
	convexspheremirror(tsvector center, mpf_class radius, mpf_class height, tsvector rot) : convexsphere(center, radius, height, rot), mirror() {}
	std::vector<tsvector> get_points(mpf_class density){
		return convexsphere::get_points(density);
	}
	tsvector get_surface_normal(tsvector point){
		return convexsphere::get_surface_normal(point);
	}
	tsvector get_intersection(photon* incident_photon){
		return convexsphere::get_intersection(incident_photon);
	}
	photon* get_redirected_photon(photon* incident_photon){
		return mirror::get_redirected_photon(incident_photon);
	}
};
