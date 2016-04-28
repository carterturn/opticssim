#pragma once

#include <vector>
#include "material.h"
#include "tsvector.h"

class object : public material{
public:


	virtual std::vector<tsvector> get_points(mpf_class density) = 0;

	virtual tsvector get_reflected(int point) = 0;
	virtual tsvector get_transmitted(int point) = 0;

	virtual bool inside(tsvector point) = 0;
};
