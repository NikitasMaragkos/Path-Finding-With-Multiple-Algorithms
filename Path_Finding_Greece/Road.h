#pragma once
#include<string>

class Road
{
 protected:
	char name[30];
	int start;
	int end;
	float distance;
	int time;

 public:
	Road();
	~Road();

	Road(char* given_name, int strt, int ending, float dist, int tim);
	void set_name(char* given_name);
	void set_start(int strt);
	void set_end(int ending);
	void set_distance(float dist);
	void set_time(int tim);

	char* get_name();
	int get_start();
	int get_end();
	float get_distance();
	int get_time();
};

