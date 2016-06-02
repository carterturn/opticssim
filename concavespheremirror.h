#pragma once

#include "concavesphere.h"

class concavespheremirror : public concavesphere, public mirror {
public:
	concavespheremirror(tsvector center, mpf_class radius, mpf_class height, tsvector rot) : concavesphere(center, radius, height, rot), mirror() {}
};
