#include "mirror.h"
#include <iostream>

using namespace std;

photon* mirror::get_redirected_photon(photon* incident_photon){
	tsvector* intersection = this->get_intersection(incident_photon);
	if (!intersection->is_valid()) {
		cout << "OH GOD NO\n";
		return NULL;
	}
	cout << intersection->to_string() << "\n";
	cout << intersection->norm().get_d() << "\n";
	tsvector* surface_normal = this->get_surface_normal(intersection);
	tsvector* direction = *(incident_photon->get_direction()) - surface_normal * (incident_photon->get_direction() * surface_normal * 2);

	return new photon(intersection, direction);
}