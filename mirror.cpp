#include "mirror.h"

using namespace std;

photon* sphere::get_redirected_photon(photon* incident_photon){
	incident_photon = incident_photon*;
	tsvector intersection = this->get_intersection(photon);
	if (!intersection.is_valid()) {
		return photon(invalid_tsvector(), invalid_tsvector());
	}
	tsvector surface_normal = this->get_surface_normal(intersection);
	return photon(intersection, incident_photon.get_direction() - surfaceNormal * (incident_photon.get_direction() * surface_normal * 2));
}