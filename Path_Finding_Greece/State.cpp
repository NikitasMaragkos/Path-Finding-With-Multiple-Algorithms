#include "State.h"
#include<stack>

State::State() {

}

State::~State() {

}

State::State(std::vector<Point>* list_points, std::vector<Road>* list_roads, Point* cur_state, State* prev_state) {
	current_city = cur_state;
	previous_state = prev_state;
	list_of_cities = list_points;
	available_roads = list_roads;
}

void State::set_current_city(Point* cur_state) {
	current_city = cur_state;
}

void State::set_previous_state(State* prev_state) {
	previous_state = prev_state;
}

void State::set_cities(std::vector<Point>* list_points) {
	list_of_cities = list_points;
}

void State::set_roads(std::vector<Road>* av_roads) {
	available_roads = av_roads;
}

void State::set_algo_id(int algorithm_id) {
	id_for_algo = algorithm_id;
}

void State::set_goal(Point* goal) {
	goal_city = goal;
}

void State::set_distance(float dist) {
	distance_so_far = dist;
}

void State::set_time(int time) {
	time_so_far = time;
}

Point* State::get_current_city() const{
	return current_city;
}

State* State::get_previous_state() {
	return previous_state;
}

std::vector<Point>* State::get_cities() {
	return list_of_cities;
}

std::vector<Road>* State::get_roads() {
	return available_roads;
}

int State::getKey() {
	return current_city->get_id();
}

Point* State::get_goal_city() const{
	return goal_city;
}

int State::get_algo_id() const{
	return id_for_algo;
}

float State::get_distance() const {
	return distance_so_far;
}

int State::get_time() const {
	return time_so_far;
}

int State::getDepth() const{
	int counter = 0;
	State* prev_city;
	prev_city = previous_state;
	while (prev_city != NULL) {
		counter++;
		prev_city = prev_city->get_previous_state();
	}
	return counter;
}

double State::cost() const {
	int id_of_algorithm = this->get_algo_id();
	if ( (id_of_algorithm == 2) || (id_of_algorithm == 4) || (id_of_algorithm == 6)) {
		return this->get_distance();
	}
	else if ((id_of_algorithm == 3) || (id_of_algorithm == 5) || (id_of_algorithm == 7)) {
		return this->get_time();
	}
}

double State::heuristic() const {
	int id_of_algorithm = this->get_algo_id();
	float lat1 = (this->get_current_city())->get_latit();
	float lon1 = (this->get_current_city())->get_longit();
	float lat2 = (this->get_goal_city())->get_latit();
	float lon2 = (this->get_goal_city())->get_longit();
	if ((id_of_algorithm == 4) || (id_of_algorithm == 6)) {
		return approximated_distance(lat1, lon1, lat2, lon2);
	}
	else if ( (id_of_algorithm == 5) || (id_of_algorithm == 7)) {
		return approximated_distance(lat1, lon1, lat2, lon2)/(130 *60);
	}
}

bool State::go_to_other_side(State &cur_state, Road* certain_road) {
	int cur_id = cur_state.getKey();
	int start_id = certain_road->get_start();
	int end_id = certain_road->get_end();
	float distance_to_be_added = certain_road->get_distance();
	int time_to_be_added = certain_road->get_time();
	float distance_so_far = this->get_distance();
	int time_so_far = this->get_time();
	if (cur_id == start_id) {
		cur_state = *this;
		cur_state.set_previous_state(this);
		Point* next = &((*(cur_state.get_cities()))[end_id]);
		cur_state.set_current_city(next);
		cur_state.set_distance(distance_so_far + distance_to_be_added );
		cur_state.set_time(time_so_far + time_to_be_added);
		//cur_state.set_current_city( (*(cur_state.get_cities()))[end_id]  );
		//Point* next =  (cur_state.list_of_cities)[end_id] );
		return true;
	}
	if (cur_id == end_id) {
		cur_state = *this;
		cur_state.set_previous_state(this);
		Point* next = &((*(cur_state.get_cities()))[start_id]);
		cur_state.set_current_city(next);
		cur_state.set_distance(distance_so_far + distance_to_be_added);
		cur_state.set_time(time_so_far + time_to_be_added);
		//cur_state.set_current_city( (*(cur_state.get_cities()))[end_id]  );
		//Point* next =  (cur_state.list_of_cities)[end_id] );
		return true;
	}
	return false;


}

std::vector<State*> State::expand() {
	std::vector<State*> children;
	State* child;
	for (int i = 0; i < (this->get_roads())->size(); i++) {
		child = new State(*this);
		if (  go_to_other_side(*child ,  &(*available_roads)[i] ) ){
		//if (go_to_other_side(*child, &(this->get_roads[i])   )  ) {
		//if(1){
			children.push_back(child);
		}
		else
			delete child;
	}
	return children;
}

void State::print_route() {
	char *name;
	State* prev = this->get_previous_state();
	float distance = this->get_distance();
	int time = this->get_time();
	std::stack<char*> route;
	name = ((*list_of_cities)[this->getKey()]).get_name();
	route.push(name);
	//std::cout << name;
	while (prev != NULL) {
		name = ((*list_of_cities)[prev->getKey()]).get_name();
		route.push(name);
		//std::cout << "<-" <<name;
		prev = prev->get_previous_state();
	}
	std::cout << "\nDistance: " << distance << " km, Time: " << time << " minutes, in " << route.size() << " moves: " << route.top();
	route.pop();
	while(!route.empty()) {
		char *name1 = route.top();
		std::cout << "->"<< name1;
		route.pop();
	}
}

bool operator > (const State& a, const State& b)
{
	int id_of_algorithm = a.get_algo_id();
	if ( id_of_algorithm == 0/*DFS*/)
		return b.getDepth() > a.getDepth();
	if (id_of_algorithm == 1/*BFS*/)
		return a.getDepth() > b.getDepth();
	if ( (id_of_algorithm == 2)  || (id_of_algorithm == 3)/*UNIFORM COST*/)
		return a.cost() > b.cost();
	if ((id_of_algorithm == 4)  || (id_of_algorithm == 5)/*BEST FIRST SEARCH*/)
		return a.heuristic() > b.heuristic();
	if ((id_of_algorithm == 6)  || (id_of_algorithm == 7)/*ALPHA STAR*/)
		return a.heuristic() + a.cost() > b.heuristic() + b.cost();
}

bool operator == (State a, State b)
{
	return ( a.getKey() == b.getKey() );
}

