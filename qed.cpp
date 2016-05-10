#include "qed.h"
#include "constant.h"
#include <iostream>
using namespace std;

qed::~qed(){
	for(int i = initial_photons.size(); i > 0; i--){
		delete initial_photons[i];
		initial_photons.erase(initial_photons.begin()+i);
	}
}

int qed::calculate(std::vector<object*> objects, mpf_class density, int depth){
	for(int i = initial_photons.size(); i > 0; i--){
		delete initial_photons[i];
		initial_photons.erase(initial_photons.begin()+i);
	}

	vector<object_point> points = vector<object_point>();

	for(int i = 0; i < objects.size(); i++){
		vector<tsvector> point_set = objects[i]->get_points(density);
		for(int j = 0; j < point_set.size(); j++){
			object_point p;
			p.obj = objects[j];
			p.point = point_set[j];
			points.push_back(p);
		}
	}

	for(int i = 0; i < points.size(); i++){
		initial_photons.push_back(new photon(origin, points[i].point, wavelength));
		for(int j = 0; j < points.size(); j++){
			if(i != j){
				mpf_class lambda = wavelength;
				if(points[i].obj != NULL && points[i].obj->inside((points[j].point - points[i].point)* (1.0/2.0))){
					lambda = wavelength * points[i].obj->get_lightspeed() / cnst::c;
				}
				initial_photons.push_back(new photon(points[i].point, points[i].obj, points[j].point, wavelength));
			}
		}
	}

	for(int i = 0; i < initial_photons.size(); i++){
		initial_photons[i]->calculate(objects, density, depth);
	}

	for(int i = 0; i < initial_photons.size(); i++){
		if(!initial_photons[i]->is_valid()){
			delete initial_photons[i];
			initial_photons.erase(initial_photons.begin()+i);
		}
	}

	return 0;
}

#ifdef GRAPHICS
void qed::draw(){
	for(int i = 0; i < initial_photons.size(); i++){
		initial_photons[i]->draw();
	}
}
#endif
