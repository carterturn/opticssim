#include "qed.h"
#include "constant.h"
#include <iostream>

#ifdef GRAPHICS
#include <GL/gl.h>
#endif
using namespace std;

qed::~qed(){
	for(int i = initial_photons.size()-1; i > 0; i--){
		delete initial_photons[i];
		initial_photons.erase(initial_photons.begin()+i);
	}
}

int qed::calculate(std::vector<object*> objects, mpf_class density, int depth){
	for(int i = initial_photons.size()-1; i > 0; i--){
		delete initial_photons[i];
		initial_photons.erase(initial_photons.begin()+i);
	}
	initial_photons.shrink_to_fit();

	vector<object_point> points = vector<object_point>();

	for(int i = 0; i < objects.size(); i++){
		vector<tsvector> point_set = objects[i]->get_points(density);
		for(int j = 0; j < point_set.size(); j++){
			object_point p;
			p.obj = objects[i];
			p.point = point_set[j];
			points.push_back(p);
		}
	}

	for(int i = 0; i < points.size(); i++){
		initial_photons.push_back(new photon(origin, points[i].point, wavelength, 1.0));
	}
	
	for(int i = 0; i < initial_photons.size(); i++){
		initial_photons[i]->calculate(objects, density, depth);
	}
	for(int i = initial_photons.size()-1; i > 0; i--){
		if(initial_photons[i]->is_valid()){
			drawable_photons.push_back(*initial_photons[i]);
		}
		else{
			delete initial_photons[i];
			initial_photons.erase(initial_photons.begin()+i);
		}
	}


	for(int d = 0; d < depth; d++){
		vector<photon*> photons = vector<photon*>();
		for(int i = 0; i < initial_photons.size(); i++){
			for(int j = 0; j < points.size(); j++){
				if(!((initial_photons[i]->get_destination().x == points[j].point.x)
				     && (initial_photons[i]->get_destination().y == points[j].point.y)
				     && (initial_photons[i]->get_destination().z == points[j].point.z))){
					mpf_class lambda = wavelength;
					if(points[i].obj == points[j].obj){
						lambda = wavelength * points[i].obj->get_lightspeed() / cnst::c;
					}
					photons.push_back(new photon(initial_photons[i]->get_destination(), initial_photons[i]->get_dest(), points[j].point, points[j].obj, lambda, 1.0));
				}
			}
		}

		for(int i = 0; i < photons.size(); i++){
			photons[i]->calculate(objects, density, depth);
		}

		for(int i = photons.size() - 1; i > 0; i--){
			if(photons[i]->is_valid()){
				drawable_photons.push_back(*initial_photons[i]);
				initial_photons.push_back(photons[i]);
			}
			else{
				delete initial_photons[i];
				initial_photons.erase(initial_photons.begin()+i);
			}
		}

		for(int i = initial_photons.size()-1; i > 0; i--){
			delete initial_photons[i];
			initial_photons.erase(initial_photons.begin()+i);
		}
		initial_photons.shrink_to_fit();

	}

	return 0;
}

#ifdef GRAPHICS
void qed::draw(){
	for(int i = 0; i < initial_photons.size(); i++){
		if(initial_photons[i]->is_valid()){
			if(initial_photons[i]->get_wavelength() > 600e-9_mpf){
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else if(initial_photons[i]->get_wavelength() > 400e-9_mpf){
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else{
				glColor3f(0.0f, 0.0f, 1.0f);
			}
			initial_photons[i]->draw();
		}
	}
}
#endif
