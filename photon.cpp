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

int photon::calculate(){
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

	glEnd();
}
#endif
