#pragma once

#include <vector>

class light {
public:
	virtual bool is_valid() = 0;

	virtual int calculate() = 0;

#ifdef GRAPHICS
	void draw();
#endif
};
