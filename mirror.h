#pragma once

#include "object.h"

class mirror : public object{
public:
	mirror() : object() {}
	tsvector get_redirected_photon();
};
