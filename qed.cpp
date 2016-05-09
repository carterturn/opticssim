#include "qed.h"

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

	mpf_class number_points = 0;
	for(int i = 0; i < objects.size(); i++){
		vector<tsvector> initial_targets = objects[i]->get_points(density);
		number_points += initial_targets.size();
		for(int j = 0; j < initial_targets.size(); i++){
			initial_photons.push_back(new photon(origin, NULL, initial_targets[j], wavelength));
		}
	}

	for(int i = 0; i < initial_photons.size(); i++){
		initial_photons->calculate(objects, density, depth);
	}

	for(int i = 0; i < initial_photons.size(); i++){
		initial_photons->propagate_probability(1.0_mpf / number_points);
	}

	return 0;
}

#ifdef GRAPHICS
void qed::draw(){
	for(int i = 0; i < initial_photons.size(); i++){
		initial_photons->draw();
	}
}
#endif
