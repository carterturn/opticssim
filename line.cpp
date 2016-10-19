#include "line.h"

#ifdef GRAPHICS
#include <GL/gl.h>
#endif

using namespace std;

vector<tsvector> line::get_points(mpf_class density){
	vector<tsvector> points = vector<tsvector>();

	for(mpf_class i = -length*0.5; i < length*0.5; i+=density){
		tsvector point_vector = tsvector(0, i, 0);
		point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
		points.push_back(center + point_vector);
	}

	return points;
}

#ifdef GRAPHICS
void line::draw(){
	vector<tsvector> points = get_points(length / 5.0);

	for(int i = 0; i < points.size(); i++){
		glVertex3f(points[i].x.get_d(), points[i].y.get_d(), points[i].z.get_d());
	}
}
#endif
