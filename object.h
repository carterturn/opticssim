#pragma once

#include <vector>

class object : public material{
public:


	std::vector<tsvector> get_points(mpf_class density);

	virtual tsvector get_reflected(int point) = 0;
	virtual tsvector get_transmitted(int point) = 0;
	virtual tsvector get_absorbed(int point) = 0;
}
