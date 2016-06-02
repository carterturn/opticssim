#include "photon.h"
#include "tsvector.h"

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

bool source::is_valid(){
	return origin.is_valid() and direction.is_valid();
}

void photon::radiate(vector<object*> objects, int depth){
	if(depth <= 0) {
		// If the ray will not radiate and hence not collide, draw it
		this->draw();
		return;
	}
	double shortest_distance = INFINITY;
	tsvector closest_reflection;

	for(int i = 0; i < objects.size(); i++){
		tsvector reflected_photon = objects[i]->get_redirected_photon(this));
		if(reflected_photon.is_valid()){
			double distance = (origin - reflected_photon.origin).norm();
			if(distance < shortest_distance){
				shortest_distance = distance;
				closest_reflection = reflected_photon;
			}
		}
	}

	if(shortest_distance != INFINITY){
		#ifdef GRAPHICS
		tsvector destination = origin + direction * ray_length;
		glBegin(GL_LINES);

		glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
		glVertex3f(closest_reflection.origin.x.get_d(), closest_reflection.origin.y.get_d(), closest_reflection.origin.z.get_d());

		glEnd();
		#endif
		closest_reflection.radiate(depth - 1);
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

	double ray_length = 1000;
	tsvector destination = origin + direction * ray_length;

	glBegin(GL_LINES);

	glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
	glVertex3f(destination.x.get_d(), destination.y.get_d(), destination.z.get_d());

	glEnd();
}
#endif
