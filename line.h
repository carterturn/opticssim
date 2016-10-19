#pragma once

#include "object.h"


class line : public object{
public:
line(tsvector center, tsvector rot, mpf_class length): length(length), rot(rot), object(center) {}

	std::vector<tsvector> get_points(mpf_class density);

#ifdef GRAPHICS
	void draw();
#endif
	mpf_class length;
	tsvector rot;
};
