#pragma once

#include "object.h"

class mirror : public object{
public:
	mirror() : object() {}
	photon* get_redirected_photon(photon* incident_photon);
};
