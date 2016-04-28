#include "clock.h"
#include <cmath>

vector2d vector2d::operator+(const vector2d& param){
	vector2d result;
	
	result.x = x + param.x;
	result.y = y + param.y;
	
	return result;
}

vector2d vector2d::operator-(const vector2d& param){
	vector2d result;
	
	result.x = x - param.x;
	result.y = y - param.y;
	
	return result;
}

mpf_class vector2d::operator*(const vector2d& param){
	vector2d result;
	
	result.x = x * param.x;
	result.y = y * param.y;
	
	return result.x + result.y;
}

vector2d vector2d::operator*(const mpf_class& scalar){
	vector2d result;
	
	result.x = x*scalar;
	result.y = y*scalar;
	
	return result;
}

mpf_class vector2d::abs(){
	return sqrt(x*x + y*y);
}

mpf_class abs(vector2d input){
	return input.abs();
}
