#pragma once

#include <vector>
#include "tsvector.h"

class object {
public:
object(tsvector center) : center(center) {}
	virtual std::vector<tsvector> get_points(mpf_class density) = 0;

#ifdef GRAPHICS
	virtual void draw() = 0;
#endif
protected:
	tsvector center;
};

