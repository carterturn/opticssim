#include "qed.h"
#include "constant.h"
#include <iostream>

#ifdef GRAPHICS
#include <GL/gl.h>
#endif
using namespace std;

qed::~qed(){
	for(int i = photons.size()-1; i > 0; i--){
		delete photons[i];
		photons.erase(photons.begin()+i);
	}
}

int qed::calculate(std::vector<object*> objects, mpf_class density, int depth){
	for(int i = photons.size()-1; i > 0; i--){
		delete photons[i];
		photons.erase(photons.begin()+i);
	}
	photons.shrink_to_fit();

	vector<object_point> points = vector<object_point>();

	// Generate all points in the space
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
		photons.push_back(new photon(origin, NULL, points[i].point, points[i].obj, wavelength, 1.0));
	}
	
	for(int i = 0; i < photons.size(); i++){
		photons[i]->calculate(objects, density, depth);
	}
	for(int i = photons.size()-1; i > 0; i--){
		if(!photons[i]->is_valid()){
			delete photons[i];
			photons.erase(photons.begin()+i);
		}
	}

	photons.shrink_to_fit();
	int start_idx = photons.size();

	for(int d = 0; d < depth; d++){
	cout << start_idx << "\n";
		for(int i = 0; i < start_idx; i++){
			for(int j = 0; j < points.size(); j++){
				if(!((photons[i]->get_destination().x == points[j].point.x)
				     && (photons[i]->get_destination().y == points[j].point.y)
				     && (photons[i]->get_destination().z == points[j].point.z))){
					mpf_class lambda = wavelength;
					if(photons[i]->get_dest() == points[j].obj){
						lambda = wavelength * points[j].obj->get_lightspeed() / cnst::c;
					}
					photons.push_back(new photon(photons[i]->get_destination(), photons[i]->get_dest(), points[j].point, points[j].obj, lambda, 1.0));
				}
			}
		}

		for(int i = start_idx; i < photons.size(); i++){
			photons[i]->calculate(objects, density, depth);
		}

		for(int i = photons.size() - 1; i > start_idx; i--){
			if(!photons[i]->is_valid()){
				delete photons[i];
				photons.erase(photons.begin()+i);
			}
		}

		photons.shrink_to_fit();
		start_idx = photons.size();

	}

	return 0;
}

#ifdef GRAPHICS
void qed::draw(){
	for(int i = 0; i < photons.size(); i++){
		if(photons[i]->is_valid()){
			if(photons[i]->get_wavelength() > 600e-9_mpf){
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else if(photons[i]->get_wavelength() > 400e-9_mpf){
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else{
				glColor3f(0.0f, 0.0f, 1.0f);
			}
			photons[i]->draw();
		}
	}
}
#endif
