#include "sphere.h"
#include "constant.h"
#include "invalid_tsvector.h"
#include <cmath>

#ifdef GRAPHICS
#include <GL/gl.h>
#endif

using namespace std;

tsvector sphere::get_center(){
	return center;
}
mpf_class sphere::get_radius(){
	return radius;
}
mpf_class sphere::get_height(){
	return height;
}
tsvector sphere::get_rot(){
	return rot;
}

tsvector sphere::get_surface_normal(tsvector point){
	tsvector shifted = point - center;
	return tsvector(shifted.x, shifted.y, shifted.z).normalize(); // FIX THIS
}

#ifdef GRAPHICS
void sphere::draw(){
	glBegin(GL_POINTS);

	mpf_class spacing = height / 40.0;
	vector<tsvector> points = get_points(spacing);
	for(int i = 0; i < points.size(); i++){
		points[i].draw();
	}

	glEnd();
}
#endif

vector<tsvector> sphere::get_points(mpf_class spacing){
	vector<tsvector> points = vector<tsvector>();

	mpf_class spacing_radius_ratio = spacing / radius;
	mpf_class angle_spacing = atan(spacing_radius_ratio.get_d());

	mpf_class height_radius_ratio = (height / 2.0) / radius;
	for(mpf_class i = atan(-1 * height_radius_ratio.get_d()); i < atan(height_radius_ratio.get_d()); i += angle_spacing){
		for(mpf_class j = 0; j < cnst::tau; j += 1.0 / height_radius_ratio.get_d() * (atan(height_radius_ratio.get_d()) - i)){
			tsvector point = tsvector(radius, 0, 0);
			point.rotate(0, 0, i.get_d());
			point = point + curve_center_left();
			point.rotate(j.get_d(), 0, 0);
			point.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point);
		}
	}

	for(mpf_class i = atan(-1 * height_radius_ratio.get_d()); i < atan(height_radius_ratio.get_d()); i += angle_spacing){
		for(mpf_class j = 0; j < cnst::tau; j += 1.0 / height_radius_ratio.get_d() * (atan(height_radius_ratio.get_d()) - i)){
			tsvector point = tsvector(-radius, 0, 0);
			point.rotate(0, 0, i.get_d());
			point = point + curve_center_right();
			point.rotate(j.get_d(), 0, 0);
			point.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point);
		}
	}

	return points;
}

tsvector sphere::get_intersection(photon incident_photon){
	tsvector direction_unit = incident_photon.get_direction().normalize();

	// Temporary quantities saved for efficiency
	tsvector c_minus_p = center - incident_photon.get_origin();
	mpf_class temp1 = direction_unit * c_minus_p;
	mpf_class temp2 = pow(temp1.get_d(), 2) + pow(radius.get_d(), 2) - (c_minus_p * c_minus_p);

	if (temp2 < 0) {
		return invalid_tsvector();
	}

	mpf_class temp3 = sqrt(temp2);

	tsvector intersection_1 = incident_photon.get_origin() + direction_unit * (temp1 - temp3);
	tsvector intersection_2 = incident_photon.get_origin() + direction_unit * (temp1 + temp3);
	
	// Check which intersection is closer to the original point by finding the magnitude of (intersection - origin) and comparing
	// Also check that we are not going backwards
	if (temp1 - temp3 < 0 and temp1 + temp3 < 0) {
		return invalid_tsvector();
	} else if (temp1 - temp3 < 0) {
		return intersection_2;
	} else if (temp1 + temp3 < 0) {
		return intersection_1;
	} else {
		if (temp1 - temp3 < temp1 + temp3) {
			return intersection_1;
		} else {
			return intersection_2;
		}
	}
}
