#include "photon.h"
#include "constant.h"
#include "tsvector.h"
#include <iostream>
#ifdef GRAPHICS
#include <GL/glut.h>
#endif

using namespace std;

bool photon::is_valid(){
	return path_valid; // path_valid is calculated while we run the photon along its path
}

int photon::calculate(vector<object*> objects, mpf_class density, int depth){
	// Normalized vector from the origin to the destination
	tsvector step_vector = (dest->point - origin->point);
	if(step_vector.abs() < cnst::epsilon){
		path_valid = false;
		return -1;
	}
	step_vector = step_vector * density * (cnst::precision / step_vector.abs());

	tsvector ray_vector;

	// While the ray_vector is shorter than the distance from destination to origin
	while(abs(ray_vector) < abs(dest->point - origin->point) && path_valid){
		ray_vector = ray_vector + step_vector; // Move forward step_vector

		// Make sure we are not inside an object we should not be inside
		for(int i = 0; i < objects.size(); i++){
			if(objects[i]->inside(origin->point + ray_vector) && !(get_origin()->obj == objects[i] && get_dest()->obj == objects[i])){
				path_valid = false;
				prob = 0.0;
				return 1;
			}
		}
	}

	mpf_class destination_turn = abs(dest->point - origin->point) / wavelength;
	turn(destination_turn);
	dest->clock = dest->clock + get_arrow();

	return 0;
}

object_point * photon::get_origin(){
	return origin;
}

object_point * photon::get_dest(){
	return dest;
}

mpf_class photon::set_probability(mpf_class probability, bool update_clock){
	if(update_clock) dest->clock = dest->clock + get_arrow()*prob*prob*-1.0;
	if(parent != NULL){
		parent->set_probability(parent->get_probability() - prob);
	}
	prob = probability;
	if(parent != NULL){
		parent->set_probability(parent->get_probability() + prob);
	}
	if(update_clock) dest->clock = dest->clock + get_arrow()*prob*prob;
	return prob;
}

mpf_class photon::get_probability(){
	return prob;
}

#ifdef GRAPHICS
void photon::draw(){

	glBegin(GL_LINES);

	glVertex3f(origin->point.x.get_d(), origin->point.y.get_d(), origin->point.z.get_d());
	glVertex3f(dest->point.x.get_d(), dest->point.y.get_d(), dest->point.z.get_d());

	// glColor3f(1.0f, 1.0f, 1.0f);
	// glVertex3f(dest->point.x.get_d(), dest->point.y.get_d(), dest->point.z.get_d());
	// glVertex3f(dest->point.x.get_d() + get_arrow().x.get_d()*get_probability().get_d(), dest->point.y.get_d() + get_arrow().y.get_d()*get_probability().get_d(), dest->point.z.get_d());

	glEnd();
}
#endif
