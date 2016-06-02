#include "photon.h"
#include "invalid_tsvector.h"
#include <cmath>

#ifdef GRAPHICS
#include <GL/glut.h>
#endif

using namespace std;

tsvector photon::get_origin(){
	return origin;
}

tsvector photon::get_direction(){
	return direction;
}

bool photon::is_valid(){
	return origin.is_valid() and direction.is_valid();
}

void photon::radiate(vector<object*> objects, int depth){
	if(depth <= 0) {
		#ifdef GRAPHICS
		// If the ray will not radiate and hence not collide, draw it
		this->draw();
		#endif
		return;
	}
	mpf_class shortest_distance = INFINITY;
	photon* closest_reflection = new photon(invalid_tsvector(), invalid_tsvector());

	for(int i = 0; i < objects.size(); i++){
		photon* reflected_photon = objects[i]->get_redirected_photon(this);
		if(reflected_photon->is_valid()){
			mpf_class distance = (origin - reflected_photon->get_origin()).norm();
			if(distance < shortest_distance){
				shortest_distance = distance;
				closest_reflection = reflected_photon;
			}
		}
	}

	if(shortest_distance != INFINITY){
		#ifdef GRAPHICS
		glBegin(GL_LINES);

		glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
		glVertex3f(closest_reflection->get_origin().x.get_d(), closest_reflection->get_origin().y.get_d(), closest_reflection->get_origin().z.get_d());

		glEnd();
		#endif
		closest_reflection->radiate(objects, depth - 1);
	} else {
		#ifdef GRAPHICS
		this->draw();
		#endif
	}
}

#ifdef GRAPHICS
void photon::draw(){
	if (!this->is_valid()) {
		return;
	}

	mpf_class ray_length = 1000;
	tsvector destination = origin + direction * ray_length;

	glBegin(GL_LINES);

	glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
	glVertex3f(destination.x.get_d(), destination.y.get_d(), destination.z.get_d());

	glEnd();
}
#endif
