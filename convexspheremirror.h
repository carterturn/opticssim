#pragma once

#include "convexsphere.h"

class convexspheremirror : public convexsphere, public mirror {
public:
	convexspheremirror(tsvector center, mpf_class radius, mpf_class height, tsvector rot) : convexsphere(center, radius, height, rot), mirror() {}
};
