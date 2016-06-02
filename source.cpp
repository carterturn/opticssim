#include "source.h"
#include "tsvector.h"

#ifdef GRAPHICS
#include <GL/glut.h>
#endif

using namespace std;

tsvector source::get_origin(){
	return origin;
}

mpf_class source::get_intensity(){
	return intensity;
}

bool source::is_valid(){
	return origin.is_valid();
}

void source::radiate(vector<object*> objects, int depth){
	if(depth <= 0) {
		return;
	}

	for (int i = 0; i < intensity; i++) {
		photon(origin, tsvector(rand(), rand(), rand()).normalize()).radiate(objects, depth - 1);
	}
}

#ifdef GRAPHICS
void source::draw(){
	if (!this->is_valid()) {
		return;
	}
	
	glBegin(GL_LINES);

	origin.draw();

	glEnd();
}
#endif
