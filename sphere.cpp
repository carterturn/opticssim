#include "sphere.h"
#include "constant.h"
#include <cmath>

#ifdef GRAPHICS
#include <GL/gl.h>
#endif

using namespace std;

tsvector sphere::get_surface_normal(tsvector point){
	return (get_local_normal(point) + point);
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

mpf_class sphere::get_radius(){
	return radius;
}

vector<tsvector> sphere::get_points(mpf_class spacing){
	vector<tsvector> points = vector<tsvector>();

	mpf_class spacing_radius_ratio = spacing / radius;
	double angle_spacing = atan(spacing_radius_ratio.get_d());

	mpf_class height_radius_ratio = (height / 2.0) / radius;
	for(double i = atan(-1 * height_radius_ratio.get_d()); i < atan(height_radius_ratio.get_d()); i += angle_spacing){
		for(double j = 0; j < cnst::tau; j += 1.0 / height_radius_ratio.get_d() * (atan(height_radius_ratio.get_d()) - i)){
			tsvector point = tsvector(radius, 0, 0);
			point.rotate(0, 0, i);
			point = point + curve_center_left();
			point.rotate(j, 0, 0);
			point.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point);
		}
	}

	for(double i = atan(-1 * height_radius_ratio.get_d()); i < atan(height_radius_ratio.get_d()); i += angle_spacing){
		for(double j = 0; j < cnst::tau; j += 1.0 / height_radius_ratio.get_d() * (atan(height_radius_ratio.get_d()) - i)){
			tsvector point = tsvector(-radius, 0, 0);
			point.rotate(0, 0, i);
			point = point + curve_center_right();
			point.rotate(j, 0, 0);
			point.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point);
		}
	}

	return points;
}

tsvector sphere::get_intersection(tsvector point, tsvector direction){
	tsvector direction_unit = direction * (1.0 / abs(direction));

	// Temporary quantities saved for efficiency
	tsvector c_minus_p = center - point;
	double temp1 = direction_unit * c_minus_p;
	double temp2 = pow(direction_unit * c_minus_p, 2) + pow(radius, 2) - (c_minus_p * c_minus_p);

	if (temp2 < 0) {
		return NULL;
	}

	double temp3 = sqrt(temp2);

	tsvector intersection_1 = point + direction_unit * (temp1 - temp3);
	tsvector intersection_2 = point + direction_unit * (temp1 + temp3);
	
	// Check which intersection is closer to the original point by finding the magnitude of (intersection - point) and comparing
	if (abs(temp1 - temp2) < abs(temp1 + temp2)) {
		return intersection_1;
	} else {
		return intersection_2;
	}
}
