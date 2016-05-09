#include "photon.h"
#include "constant.h"
#include "tsvector.h"
#include <iostream>
#ifdef GRAPHICS
#include <GL/glut.h>
#endif

using namespace std;

photon::~photon(){
	for(int i = 0; i < next_nodes.size(); i++){
		delete next_nodes[i];
	}
}

bool photon::is_valid(){
	return path_valid; // path_valid is calculated while we run the photon along its path
}



int photon::calculate(vector<object*> objects, mpf_class density, int depth){
	for(int i = next_nodes.size(); i > 0; i--){ // Iterating backwards makes more efficient
		delete next_nodes[i];
		next_nodes.erase(next_nodes.begin()+i);
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
						mpf_class source_lightspeed = cnst::c;
						if(get_origin() != NULL) source_lightspeed = get_origin()->get_lightspeed();
						mpf_class adjusted_wavelength = wavelength * (objects[i]->get_lightspeed() / source_lightspeed);
						// Apply speed-of-light change if appropriate
						if(objects[i]->inside(ray_vector - step_vector) !=
						   objects[i]->inside((next_targets[j] - destination)* density * (cnst::precision / sqrt(step_vector * step_vector)))){
							adjusted_wavelength = wavelength;
						}
						next_nodes.push_back(new photon(destination, objects[i], next_targets[j], adjusted_wavelength));
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

	for(int i = 0; i < next_nodes.size(); i++){
		next_nodes[i]->turn(destination_turn);
	}
	for(int i = 0; i < next_nodes.size(); i++){
		next_nodes[i]->calculate(objects, density, next_depth[i]);
	}
	
	return 0;
}

int photon::propagate_probability(mpf_class probability){
	// Divide by the number of nodes
	for(int i = 0; i < next_nodes.size(); i++){
		if(next_nodes[i]->is_valid()){
			next_nodes[i]->propagate_probability(probability / next_nodes.size());
		}
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

	for(int i = 0; i < next_nodes.size(); i++){
		if(next_nodes[i]->is_valid()){
			next_nodes[i]->draw();
		}
	}
}
#endif
