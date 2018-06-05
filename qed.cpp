#include "qed.h"
#include "constant.h"
#include <cmath>
#include <iostream>

#ifdef GRAPHICS
#include <GL/gl.h>
#endif
using namespace std;

qed::~qed(){
	while(photons.size() > 0){
		delete photons.back();
		photons.pop_back();
	}
}

int qed::calculate(std::vector<object*> objects, mpf_class density, int depth){
	while(photons.size() > 0){
		delete photons.back();
		photons.pop_back();
	}
	photons.shrink_to_fit();

	// Generate all points in the space
	object_point * final_dest = new object_point;
	final_dest->point = destination;
	final_dest->obj = NULL;
	final_dest->clock = vector2d();
	points.push_back(final_dest);
	
	for(int i = 0; i < objects.size(); i++){
		vector<tsvector> point_set = objects[i]->get_points(density);
		for(int j = 0; j < point_set.size(); j++){
			object_point * p = new object_point;
			p->obj = objects[i];
			p->point = point_set[j];
			p->clock = vector2d();
			points.push_back(p);
		}
	}

	object_point * photon_origin = new object_point;
	photon_origin->point = origin;
	photon_origin->obj = NULL;
	photon_origin->clock = vector2d();
	
	for(int i = 0; i < points.size(); i++){
		photon * p = new photon(photon_origin, points[i], wavelength);
		photons.push_back(p);
	}
	
	for(int i = 0; i < photons.size(); i++){
		photons[i]->calculate();
	}
	
	cout << "Seed photons calculated\n";

	int start_idx = photons.size();
	int last_start_idx = 0;

	for(int d = 0; d < depth; d++){
		for(int i = last_start_idx; i < start_idx; i++){
			if(!(photons[i]->get_dest()->point == points[0]->point)){// Stop when we arrive
				for(int j = 0; j < points.size(); j++){
					if(!(photons[i]->get_dest()->obj == points[j]->obj)){
						photon * p = new photon(photons[i], points[j], wavelength);
						p->turn(photons[i]->get_angle());
						photons.push_back(p);
					
					}
				}
			}
		}

		for(int i = start_idx; i < photons.size(); i++){
			photons[i]->calculate();
		}

		cout << d << " jump photons calculated\n";
		cout << photons.size() << " generated\n";

		last_start_idx = start_idx;
		start_idx = photons.size();

	}
	
	for(int i = photons.size() - 1; i > last_start_idx; i--){
		if(!(photons[i]->get_dest()->point == destination)){
			delete photons[i];
			photons.erase(photons.begin()+i);
		}
	}

	cout << "All photon paths generated\n";
	cout << photons.size() << " generated\n";
	
	for(int i = 0; i < points.size(); i++){
		if(points[i]->clock.abs() != 0){
			points[i]->clock = points[i]->clock * (1.0 / points[i]->clock.abs());
		}
	}

	mpf_class average_probability = 0;
	for(int i = 0; i < photons.size(); i++){
		if(photons[i]->get_dest()->point == destination){
			photons[i]->set_probability((photons[i]->get_arrow()*photons[i]->get_dest()->clock), false);
		}
		average_probability += (photons[i]->get_probability()) / (mpf_class(photons.size()));
	}
	cout << average_probability.get_d() << "\n";

	for(int i = photons.size() - 1; i > 0; i--){
		if(photons[i]->get_probability() < average_probability){
			delete photons[i];
			photons.erase(photons.begin()+i);
		}
	}
	photons.shrink_to_fit();

	cout << photons.size() << " significant\n";

	cout << "Probabilities adjusted\n";

	return 0;
}

#ifdef GRAPHICS
void qed::draw(){
	int cached_photon_size = photons.size();
	for(int i = 0; i < photons.size(); i++){
		mpf_class probability = photons[i]->get_probability();
		for(int j = 0; j < photons.size(); j++){
			if(i != j){
				if(photons[j]->get_origin()->point == photons[i]->get_origin()->point
				   && photons[j]->get_dest()->point == photons[i]->get_dest()->point){
					probability += photons[j]->get_probability();
				}
			}
		}
		double prob = probability.get_d();
		glColor3f(0.0f, prob*0.1, 0.0f);
		photons[i]->draw();
	}
}
#endif
