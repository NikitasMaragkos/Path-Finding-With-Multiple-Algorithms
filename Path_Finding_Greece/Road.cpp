#include "Road.h"

Road::Road() {
	start = 0;
	end = 0;
	distance = 0;
	time = 0;
}

Road::~Road() {

}

Road::Road(char* given_name, int strt, int ending, float dist, int tim) {
	strcpy_s(name, strlen(given_name) + 1, given_name);
	start = strt;
	end = ending;
	distance = dist;
	time = tim;
}


void Road::set_name(char* given_name) {
	strcpy_s(name, strlen(given_name) + 1, given_name);
}

void Road::set_start(int strt) {
	start = strt;
}

void Road::set_end(int ending) {
	end = ending;
}

void Road::set_distance(float dist) {
	distance = dist;
}

void Road::set_time(int tim) {
	time = tim;
}

char* Road::get_name() {
	return name;
}

int Road::get_start() {
	return start;
}

int Road::get_end() {
	return end;
}

float Road::get_distance() {
	return distance;
}

int Road::get_time() {
	return time;
}

