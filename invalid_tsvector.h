#pragma once

#include "tsvector.h"

class invalid_tsvector : public tsvector {
public:
	invalid_tsvector() : tsvector(){}
