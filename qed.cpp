#include "qed.h"
#include "constant.h"
#include <cmath>
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
	int last_start_idx = 0;

	for(int d = 0; d < depth; d++){
		for(int i = last_start_idx; i < start_idx; i++){
			if(!(photons[i]->get_dest()->point == points[0]->point)){// Stop when we arrive
				for(int j = 0; j < points.size(); j++){
					if(!(photons[i]->get_dest()->obj == points[j]->obj)){
						mpf_class lambda = wavelength;
/*						if(photons[i]->get_dest()->obj == points[j]->obj){
							lambda = wavelength * photons[i]->get_dest()->obj->get_lightspeed() / cnst::c;
						}
						if(photons[i]->get_dest()->obj != NULL){
							if(photons[i]->get_dest()->obj->get_reflected(photons[i]->get_dest()->point) * (points[j]->point - photons[i]->get_dest()->point) > 0){
								base_probability = 0;
							}
							if(photons[i]->get_dest()->obj->get_transmitted(photons[i]->get_dest()->point) * (points[j]->point - photons[i]->get_dest()->point) > 0){
								base_probability = 1;
							}
							}*/
						photon * p = new photon(photons[i]->get_dest(), points[j], lambda);
						p->turn(photons[i]->get_angle());
//						p->add_probability(base_probability, false);
						photons.push_back(p);
					
					}
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

		last_start_idx = start_idx;
		start_idx = photons.size();

	}

	cout << "Photon paths generated\n";

	for(int i = 0; i < points.size(); i++){
		points[i]->clock = points[i]->clock * (1.0 / points[i]->clock.abs());
	}

	for(int i = 0; i < photons.size(); i++){
		photons[i]->add_probability(((photons[i]->get_arrow()*photons[i]->get_probability()*photons[i]->get_probability())
					     *photons[i]->get_dest()->clock)/
					    (photons[i]->get_dest()->clock*photons[i]->get_dest()->clock), false);
	}
	
	return 0;
}

#ifdef GRAPHICS
void qed::draw(){
	for(int i = 0; i < photons.size(); i++){
		if(photons[i]->is_valid()){
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
			if(prob > 0.05){
				if(photons[i]->get_wavelength() > 600e-9_mpf){
					glColor3f(prob, 0.0f, 0.0f);
				}
				else if(photons[i]->get_wavelength() > 400e-9_mpf){
					glColor3f(0.0f, prob, 0.0f);
				}
				else{
					glColor3f(0.0f, 0.0f, prob);
				}
				photons[i]->draw();
			}
		}
	}
}
#endif
