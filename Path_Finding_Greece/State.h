#pragma once
#include"import_output.h"
#include"Point.h"
#include"Road.h"
#include<vector>
#include <queue> 
#include<stdio.h>
#include<iostream>


class State
{
protected:
	Point* current_city;
	State* previous_state;
	std::vector<Point>* list_of_cities;
	std::vector<Road>* available_roads;
	int id_for_algo;
	Point* goal_city;
	float distance_so_far;
	int time_so_far;
public:

	
	State();
	~State();
	State(std::vector<Point>* list_points, std::vector<Road>* list_roads,  Point* cur_state , State* prev_state);

	void set_current_city(Point* current);
	void set_previous_state(State* previous);
	void set_cities(std::vector<Point>* cities);
	void set_roads(std::vector<Road>* roads);
	void set_algo_id(int);
	void set_goal(Point* goal);
	void set_distance(float dist);
	void set_time(int time);

	Point* get_current_city( ) const;
	State* get_previous_state( );
	std::vector<Point>* get_cities( );
	std::vector<Road>* get_roads( );

	bool go_to_other_side(State &cur_state, Road* certain_road);
	void print_route();


	int get_algo_id() const;
	Point* get_goal_city() const;
	float get_distance() const;
	int get_time() const;
	int getKey();
	std::vector <State*> expand();
	int getDepth()const;
	double cost() const;
	double heuristic() const;

};

bool operator > (const State& a, const State& b);
bool operator == (State a, State b);

