#include "Point.h"
//#include "Road.h"

Point::Point()
{
	longit = 0;
	latit = 0;
	id = 0;
	
}

Point::~Point()
{
}

Point::Point(int ident, char* given_name, float longitude, float latitude){
	strcpy_s(name, strlen(given_name)+1, given_name);
	longit = longitude;
	latit = latitude;
	id = ident;
}

void Point::set_name(char* given_name) {
	strcpy_s(name, strlen(given_name) + 1, given_name);
}

void Point::set_longit(float longitude) {
	longit = longitude;
}

void Point::set_latit(float latitude) {
	latit = latitude;
}

void Point::set_id(int ident) {
	id = ident;
}

char* Point::get_name() {
	return name;
}

float Point::get_longit() {
	return longit;
}

float Point::get_latit() {
	return latit;
}

int Point::get_id() {
	return id;
}


