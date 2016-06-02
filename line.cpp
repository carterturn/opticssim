#include "line.h"

#ifdef GRAPHICS
#include <GL/gl.h>
#endif

using namespace std;

vector<tsvector> line::get_points(mpf_class density){
	vector<tsvector> points = vector<tsvector>();

	for(mpf_class i = -length*0.5; i < length*0.5; i+=density){
		tsvector point_vector = tsvector(0, i, 0);
		point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
		points.push_back(center + point_vector);
	}

	return points;
}

tsvector line::get_surface_normal(tsvector point){
	return tsvector();
}

tsvector line::get_local_normal(tsvector point){
	return tsvector();
}

bool line::inside(tsvector point){
	return false;
}

mpf_class line::get_radius(){
	return length / 2.0;
}

#ifdef GRAPHICS
void line::draw(){
	vector<tsvector> points = get_points(length / 5.0);

	for(int i = 0; i < points.size(); i++){
		glVertex3f(points[i].x.get_d(), points[i].y.get_d(), points[i].z.get_d());
	}
}
#endif
