#pragma once

#include <vector>

class light {
public:
light(tsvector origin) : origin(origin){}
	
	virtual bool is_valid() = 0;
	virtual bool interact() = 0;

	virtual int calculate() = 0;

#ifdef GRAPHICS
	virtual void draw() = 0;
#endif

protected:
	tsvector origin;
};
