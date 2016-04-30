#pragma once

#include "object.h"

class block : public object{
public:
block(tsvector center, tsvector dim, tsvector rot) : center(center), dim(dim), rot(rot){}
	
	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_reflected(tsvector point);
	tsvector get_transmitted(tsvector point);

	bool inside(tsvector point);

#ifdef GRAPHICS
	void draw();
#endif

protected:
	tsvector center;
	tsvector rot;
	tsvector dim;
};
