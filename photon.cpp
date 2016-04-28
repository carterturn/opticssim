#include "photon.h"
#include "constant.h"
#include "tsvector.h"

#ifdef GRAPHICS
#include <GL/glut.h>
#endif

using namespace std;

photon::~photon(){
	for(int i = 0; i < next_bundles.size(); i++){
		delete next_bundles[i];
	}
}

bool photon::is_valid(){
	return path_valid; // path_valid is calculated while we run the photon along its path
}



int photon::calculate(vector<object*> objects){

	// Normalized vector from the origin to the destination
	tsvector step_vector = (destination - origin);
	step_vector = step_vector * (cnst::precision / sqrt(step_vector * step_vector));

	tsvector ray_vector;

	// While the ray_vector is shorter than the distance from destination to origin
	while(abs(ray_vector) < abs(destination - origin) && path_valid){
		ray_vector = ray_vector + step_vector; // Move forward step_vector

		for(int i = 0; i < objects.size(); i++){
			if(objects[i]->inside(origin + ray_vector)){
				path_valid = false;
				break;
			}
		}

		
	}

}

#ifdef GRAPHICS
void photon::draw(){

	glBegin(GL_LINES);

	glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
	glVertex3f(destination.x.get_d(), destination.y.get_d(), destination.z.get_d());

	glEnd();

	for(int i = 0; i < next_bundles.size(); i++){
		next_bundles[i]->draw();
	}
}
#endif
