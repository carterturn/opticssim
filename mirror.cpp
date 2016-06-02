#include "mirror.h"
#include "invalid_tsvector.h"

using namespace std;

photon* mirror::get_redirected_photon(photon* incident_photon){
	tsvector intersection = this->get_intersection(incident_photon);
	if (!intersection.is_valid()) {
		return new photon(invalid_tsvector(), invalid_tsvector());
	}
	tsvector surface_normal = this->get_surface_normal(intersection);
	return new photon(intersection, incident_photon->get_direction() - surface_normal * (incident_photon->get_direction() * surface_normal * 2));
}