#include "photon.h"
#include "invalid_tsvector.h"
#include <iostream>

#ifdef GRAPHICS
#include <GL/glut.h>
#endif

using namespace std;

tsvector* photon::get_origin(){
	return origin;
}

tsvector* photon::get_direction(){
	return direction;
}

void photon::radiate(vector<object*> objects, int depth){
	//cout << "***" << depth << "***\n";
	if(!this->is_valid()){
		cout << "INVALID\n";
		return;
	}
	if(depth <= 0) {
		#ifdef GRAPHICS
		// If the ray will not radiate and hence not collide, draw it
		//cout << "RAE IS BAE\n";
		this->draw();
		#endif
		return;
	}
	mpf_class shortest_distance = 99e99_mpf;
	photon* closest_reflection = NULL;

	for(int i = 0; i < objects.size(); i++){
		photon* reflected_photon = objects[i]->get_redirected_photon(this);
		if(reflected_photon->is_valid()){
			tsvector* temp1 = reflected_photon->get_origin();
			tsvector* temp2 = this->get_origin();
			cout << temp1->to_string() << " - " << temp2->cto_string() << "\n";
			tsvector* distance_vector = new tsvector(*temp2 - *temp1);
			//tsvector distance_vector = temp4 - temp3;
			/*mpf_class distance = distance_vector.norm();
			if(distance < shortest_distance){
				shortest_distance = distance;
				closest_reflection = reflected_photon;
			}*/
		}
	}

	if(closest_reflection->is_valid()){
		#ifdef GRAPHICS
		glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
		glVertex3f(closest_reflection->get_origin().x.get_d(), closest_reflection->get_origin().y.get_d(), closest_reflection->get_origin().z.get_d());

		glEnd();
		#endif
		//cout << "MADEIT: " << shortest_distance.get_d() << "\n";
		closest_reflection->radiate(objects, depth - 1);
	} else {
		cout << "NO INTERSECTION\n";
		#ifdef GRAPHICS
		this->draw();
		#endif
	}
}

#ifdef GRAPHICS
void photon::draw(){
	if (!this->is_valid()) {
		cout << "INVALID, NOT DRAWING\n";
		return;
	}

	mpf_class ray_length = 50.0;
	tsvector destination = origin + direction * ray_length;

	//cout << origin.x.get_d() << "|" << oricgin.y.get_d() << "|" << origin.z.get_d() << "\n";
	//cout << destination.x.get_d() << "|" << destination.y.get_d() << "|" << destination.z.get_d() << "\n";

	glBegin(GL_LINES);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(origin.x.get_d(), origin.y.get_d(), origin.z.get_d());
	glVertex3f(destination.x.get_d(), destination.y.get_d(), destination.z.get_d());

	glEnd();
}
#endif
