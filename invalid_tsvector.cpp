#include "invalid_tsvector.h"

bool tsvector::is_valid(){
	return false;
}

tsvector tsvector::rotate(double tx, double ty, double tz){
	return this;
}

mpf_class tsvector::norm(){
	return -1;
}

tsvector tsvector::normalize(){
	return this;
}


tsvector tsvector::operator+(const tsvector& param){
	return this;
}

tsvector tsvector::operator-(const tsvector& param){
	return this;
}

mpf_class tsvector::operator*(const tsvector& param){
	return this;
}

tsvector tsvector::operator*(const int& scalar){
	return this;
}

tsvector tsvector::operator*(const double& scalar){
	return this;
}

tsvector tsvector::operator*(const float& scalar){
	return this;
}

tsvector tsvector::operator*(const mpf_class& scalar){
	return this;
}

#ifdef GRAPHICS
void tsvector::draw(){}
#endif
