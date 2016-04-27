#pragma once

#include <vector>

class light {

	virtual bool is_valid() = 0;

#ifdef GRAPHICS
	void draw();
#endif

protected:
	std::vector<*light> next_light;
};
