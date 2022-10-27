#pragma once
#include <string>
#include <vector>

class Point
{
protected:
		char name[30];
		float longit;
		float latit;
		int id;
		//std::vector<Road>* roads;
		//Point* previous_point;

public:
		Point();
		~Point();
		Point(int ident, char* given_name, float longitude, float latitude);
		void set_name( char* given_name);
		void set_longit(float longitude);
		void set_latit(float latitude);
		void set_id(int ident);

		char* get_name();
		float get_longit();
		float get_latit();
		int get_id();

};

