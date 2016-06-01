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
	double shortest_distance = INFINITY;
	tsvector closest_intersection;
	tsvector direction = destination - origin;

	for(int i = 0; i < objects.size(); i++){
		double intersection = abs(objects[i]->get_intersection(origin, direction));
		if(intersection != NULL and abs(intersection) < shortest_distance){
			shortest_distance = abs(intersection);
			closest_intersection = intersection;
		}
	}
	path_valid = (shortest_distance == INFINITY);

	// What now? What do we do with the resulting intersection?
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
