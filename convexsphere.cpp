#include "convexsphere.h"

#ifdef GRAPHICS
#include <GL/gl.h>
#endif

using namespace std;

tsvector convexsphere::get_surface_normal(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());

	if(local_pos.x > 0){
		tsvector radius_vector = local_pos - tsvector(-radius, 0, 0);
		return point + radius_vector * (1.0 / radius_vector.abs());
	}
	if(local_pos.x < 0){
		tsvector radius_vector = local_pos - tsvector(radius, 0, 0);
		return point + radius_vector * (1.0 / radius_vector.abs());
	}
	return tsvector(); // If you are the center, you get a zero vector
}

#ifdef GRAPHICS
void convexsphere::draw(){
	glBegin(GL_POINTS);

	mpf_class spacing = height / 40.0;
	vector<tsvector> points = get_points(spacing);
	for(int i = 0; i < points.size(); i++){
		points[i].draw();
	}

	glEnd();
}
#endif

vector<tsvector> convexsphere::get_points(mpf_class spacing){
	vector<tsvector> points = vector<tsvector>();

	mpf_class spacing_radius_ratio = spacing / radius;
	double angle_spacing = atan(spacing_radius_ratio.get_d());

	mpf_class height_radius_ratio = (height / 2.0) / radius;
	for(double i = atan(-1 * height_radius_ratio.get_d()); i < atan(height_radius_ratio.get_d()); i += angle_spacing){
		tsvector point = tsvector(radius, 0, 0);
		point.rotate(0, 0, i);
		point = point + curve_center_left();
		points.push_back(center + point);
	}

	for(double i = atan(-1 * height_radius_ratio.get_d()); i < atan(height_radius_ratio.get_d()); i += angle_spacing){
		tsvector point = tsvector(-radius, 0, 0);
		point.rotate(0, 0, i);
		point = point + curve_center_right();
		points.push_back(center + point);
	}

	return points;
}

bool convexsphere::inside(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());

	return (abs(local_pos - curve_center_left()) < radius) &&
		(abs(local_pos - curve_center_right()) < radius);
}

tsvector convexsphere::curve_center_left(){
	mpf_class height_radius_ratio = (height / 2.0) / radius;
	return tsvector(radius * -cos(asin(height_radius_ratio.get_d())), 0, 0);
}

tsvector convexsphere::curve_center_right(){
	return curve_center_left() * -1.0;
}
