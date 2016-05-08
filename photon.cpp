#include "photon.h"
#include "constant.h"
#include "tsvector.h"
#include <iostream>
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



int photon::calculate(vector<object*> objects, mpf_class density, int depth){
	for(int i = next_bundles.size(); i > 0; i--){ // Iterating backwards makes more efficient
		delete next_bundles[i];
		next_bundles.erase(next_bundles.begin()+i);
		next_depth.erase(next_depth.begin()+i);
	}
	
	// Normalized vector from the origin to the destination
	tsvector step_vector = (destination - origin);
	if(step_vector.abs() < cnst::epsilon){
		path_valid = false;
		return -1;
	}
	step_vector = step_vector * density * (cnst::precision / sqrt(step_vector * step_vector));

	tsvector ray_vector;

	// While the ray_vector is shorter than the distance from destination to origin
	while(abs(ray_vector) < abs(destination - origin) && path_valid){
		ray_vector = ray_vector + step_vector; // Move forward step_vector
		if(abs(ray_vector) >= abs(destination - origin)){
			if(depth > 0){
				for(int i = 0; i < objects.size(); i++){
					vector<tsvector> next_targets = objects[i]->get_points(density);
					for(int j = 0; j < next_targets.size(); j++){
						next_bundles.push_back(new photon(destination, objects[i], next_targets[j], wavelength));
						// Limit internal reflections/refractions
						if(objects[i] == get_origin() && depth > 1) next_depth.push_back(0);
						else next_depth.push_back(depth - 1);
					}
				}
			}
		}

		for(int i = 0; i < objects.size(); i++){
			if(objects[i]->inside(origin + ray_vector) && (objects[i] != get_origin())){
				path_valid = false;
				return 1;
			}
		}
		
	}

	mpf_class destination_turn = abs(destination - origin) / wavelength;
	turn(destination_turn);

	for(int i = 0; i < next_bundles.size(); i++){
		next_bundles[i]->turn(destination_turn);
	}
	for(int i = 0; i < next_bundles.size(); i++){
		next_bundles[i]->calculate(objects, density, next_depth[i]);
	}
	
	return 0;
}

object * photon::get_origin(){
	return origin_object;
}

#ifdef GRAPHICS
void photon::draw(){

	glBegin(GL_LINES);

	glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
	glVertex3f(destination.x.get_d(), destination.y.get_d(), destination.z.get_d());

	glEnd();

	for(int i = 0; i < next_bundles.size(); i++){
		if(next_bundles[i]->is_valid()){
			next_bundles[i]->draw();
		}
	}
}
#endif
