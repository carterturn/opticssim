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
	tsvector step_vector = (destination - origin);
	if(step_vector.abs() < cnst::epsilon){
		path_valid = false;
		return -1;
	}
	step_vector = step_vector * density * (cnst::precision / step_vector.abs());

	tsvector ray_vector;

	// While the ray_vector is shorter than the distance from destination to origin
	while(abs(ray_vector) < abs(destination - origin) && path_valid){
		ray_vector = ray_vector + step_vector; // Move forward step_vector

		// Make sure we are not inside an object we should not be inside
		for(int i = 0; i < objects.size(); i++){
			if(objects[i]->inside(origin + ray_vector) && !(get_origin() == objects[i] && get_dest() == objects[i])){
				path_valid = false;
				return 1;
			}
		}
	}

	mpf_class destination_turn = abs(destination - origin) / wavelength;
	turn(destination_turn);

	return 0;
}

object * photon::get_origin(){
	return origin_object;
}

object * photon::get_dest(){
	return dest_object;
}

tsvector photon::get_destination(){
	return destination;
}

#ifdef GRAPHICS
void photon::draw(){

	glBegin(GL_LINES);

	glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
	glVertex3f(destination.x.get_d(), destination.y.get_d(), destination.z.get_d());

	glEnd();
}
#endif
