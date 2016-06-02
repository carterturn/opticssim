#include "mirror.h"
#include "invalid_tsvector.h"
#include <iostream>

using namespace std;

photon* mirror::get_redirected_photon(photon* incident_photon){
	tsvector intersection = this->get_intersection(incident_photon);
	if (!intersection.is_valid()) {
		cout << "OH GOD NO\n";
		invalid_tsvector invalid = invalid_tsvector();
		return new photon(invalid, invalid);
	}
	cout << intersection.x.get_d() << ":" << intersection.y.get_d() << ":" << intersection.z.get_d() << "\n";
	cout << intersection.norm().get_d() << "\n";
	tsvector surface_normal = this->get_surface_normal(intersection);
	tsvector direction = incident_photon->get_direction() - surface_normal * (incident_photon->get_direction() * surface_normal * 2);
	return new photon(intersection, direction);
}