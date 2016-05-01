#include "sphere.h"
#include "constant.h"

#ifdef GRAPHICS
#include <GL/gl.h>
#endif

using namespace std;

tsvector sphere::get_surface_normal(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());

	if(local_pos.x > 0){
		tsvector radius_vector = local_pos - tsvector(-radius, 0, 0);
		return point + (radius_vector * (1.0 / radius_vector.abs())).rotate(-rot.x.get_d(), -rot.y.get_d(), -rot.z.get_d());
	}
	if(local_pos.x < 0){
		tsvector radius_vector = local_pos - tsvector(radius, 0, 0);
		return point + (radius_vector * (1.0 / radius_vector.abs())).rotate(-rot.x.get_d(), -rot.y.get_d(), -rot.z.get_d());
	}
	return tsvector(); // If you are the center, you get a zero vector
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

bool sphere::inside(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());

	return (abs(local_pos - curve_center_left()) < radius) &&
		(abs(local_pos - curve_center_right()) < radius);
}
