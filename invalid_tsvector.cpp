#include "invalid_tsvector.h"

bool invalid_tsvector::is_valid(){
	return false;
}

tsvector invalid_tsvector::rotate(double tx, double ty, double tz){
	return *this;
}

mpf_class invalid_tsvector::norm(){
	return -1;
}

tsvector invalid_tsvector::normalize(){
	return *this;
}


tsvector invalid_tsvector::operator+(const tsvector& param){
	return *this;
}

tsvector invalid_tsvector::operator-(const tsvector& param){
	return *this;
}

mpf_class invalid_tsvector::operator*(const tsvector& param){
	return 0;
}

tsvector invalid_tsvector::operator*(const int& scalar){
	return *this;
}

tsvector invalid_tsvector::operator*(const double& scalar){
	return *this;
}

tsvector invalid_tsvector::operator*(const float& scalar){
	return *this;
}

tsvector invalid_tsvector::operator*(const mpf_class& scalar){
	return *this;
}

#ifdef GRAPHICS
void invalid_tsvector::draw(){}
#endif

