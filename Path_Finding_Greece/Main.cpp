#include<stdio.h>
#include<iostream>
#include <unordered_map>
#include"import_output.h"
#include"State.h"
#include"Point.h"
#include"Road.h"
#include"Add_city.h"
#include"Add_road.h"
#include"Edit_city.h"
#include"Edit_road.h"

template <typename X> class Comparator
{
public:
	int operator() (X* p1, X* p2) const
	{
		return *p1 > * p2;
	}
};


template <typename X>
X* SEARCH(X* initial, X* goal, int* visited_points, int* expanded_points )
{
	std::priority_queue<X*, std::vector<X*>, Comparator<X> > agenda;
	std::unordered_map< int, X*> closed;
	agenda.push(initial);
	*expanded_points = *expanded_points + 1;
	while (agenda.size() > 0)
	{
		X* s = agenda.top();
		agenda.pop();
		if (closed.count(s->getKey()) == 0)
		{
			*visited_points = *visited_points + 1;
			if (*s == *goal)
				return s;
			std::pair<int, X*> k(s->getKey(), s);
			closed.insert(k);
			std::vector<X*> children = s->expand();
			for (unsigned int i = 0; i < children.size(); i++)
				if (closed.count(children[i]->getKey()) == 0)
				{
					*expanded_points = *expanded_points + 1;
					agenda.push(children[i]);
				}
		}
	}
	return NULL;
}


using namespace std;

int main() {

	State* sol;
	State initial,goal;
	int algorithm_id;
	int choice = 1;
	vector<Point> list_of_points;
	vector<Road> list_of_roads;
	char temp_file_name[30];
	char temp_point_name[30];
	char temp_road_name[30];
	float temp_longitude, temp_latitude;
	int start, end;
	int temp_start, temp_end;
	char temp_start_name[30];
	char temp_end_name[30];
	float temp_distance;
	int temp_time;
	int flag_for_edit;
	int flag_for_continue;
	int visited_points,expanded_points;



	while (choice != 0) {

		cout << "\n\n~~~~~~~~~~~~~Menu~~~~~~~~~~~~~\n\n"
			<< "1. Add City\n"
			<< "2. Add Road\n"
			<< "3. Edit City\n"
			<< "4. Edit Road\n"
			<< "5. List Cities\n"
			<< "6. List Roads\n"
			<< "7. Save to file\n"
			<< "8. Load from file\n"
			<< "9. Solve\n"
			<< "0. Quit\n"
			<< "\n\nYour choice:";
		cin >> choice;

		switch(choice) {
		case 0:
			return 0;
		case 1:
			add_city(&list_of_points);
			break;
		case 2:
			add_road(&list_of_points, &list_of_roads);
			break;
		case 3:
			edit_city(&list_of_points);
			break;
		case 4:
			edit_road(&list_of_points, &list_of_roads);
			break;
		case 5:
			for ( unsigned int i = 0; i < list_of_points.size(); i++) {
				cout << "\n"<<i<<". City: " << (list_of_points[i]).get_name() << " with latitude " << (list_of_points[i]).get_latit() << " and longitude " << (list_of_points[i]).get_longit();
			}
			break;
		case 6:
			for (unsigned int i = 0; i < list_of_roads.size(); i++) {
				int id_start = (list_of_roads[i]).get_start();
				int id_end = (list_of_roads[i]).get_end();
				cout << "\n"<<i<<". Road: " << (list_of_roads[i]).get_name() << " from " << (list_of_points[id_start]).get_name() << " to " << (list_of_points[id_end]).get_name() << " with distance "<< (list_of_roads[i]).get_distance() << " km in "<< (list_of_roads[i]).get_time() <<"m.\n" ;
			}
			break;
		case 7:
			int flag_for_save;
			cout << "Give me the name of file to save:";
			cin >> temp_file_name;
			flag_for_save = save_at_file(temp_file_name, &list_of_points, &list_of_roads);
			if (flag_for_save == 0)
				cout << "\nData saved in " << temp_file_name << "\n";
			break;
		case 8:
			int flag_for_existing_data;
			int check_for_reading;
			if (list_of_points.size() == 0 && list_of_roads.size() == 0) {
				cout << "Give me the name of the file:";
				cin >> temp_file_name;
				check_for_reading = read_from_file(temp_file_name, &list_of_points, &list_of_roads);
				if (check_for_reading != 0)
					break;
			}
			else {
				cout << "There are already cities and roads. Do you want to keep them?\n1. Yes\n2. No\nYour choice:";
				cin >> flag_for_existing_data;
				cout << "Give me the name of the file:";
				cin >> temp_file_name;
				if (flag_for_existing_data == 1) {
					check_for_reading = read_from_file(temp_file_name, &list_of_points, &list_of_roads);
					if (check_for_reading != 0)
						break;
				}
				else {
					list_of_points.clear();
					list_of_roads.clear();
					check_for_reading = read_from_file(temp_file_name, &list_of_points, &list_of_roads);
					if (check_for_reading != 0)
						break;
				}
			}
			break;
		case 9:
			cout << "\nGive the start:";
			cin >> temp_start_name;
			start = check_if_point_exists_in_list(temp_start_name, &list_of_points);
			if (start == -1) {
				cout << "\nThis city does not exist in the list.\n";
				break;
			}
			cout << "\nGive the end:";
			cin >> temp_end_name;
			end = check_if_point_exists_in_list(temp_end_name, &list_of_points);
			if (end == -1) {
				cout << "\nThis city does not exist in the list.\n";
				break;
			}
			cout << "\n0. DFS"
				<<"\n1. BFS"
				<<"\n2. Uniform Cost for distance"
				<<"\n3. Uniform Cost for time"
				<<"\n4. Best First Search for distance"
				<<"\n5. Best First Search for time"
				<<"\n6. A* for distance"
				<<"\n7. A* for time"
				<<"\nYour choice:";
			cin >> algorithm_id;
			initial.set_algo_id(algorithm_id);
			initial.set_cities(&list_of_points);
			initial.set_current_city(&(list_of_points[start]));
			initial.set_previous_state(NULL);
			initial.set_roads(&list_of_roads);
			initial.set_goal(&(list_of_points[end]));
			initial.set_distance(0);
			initial.set_time(0);
			goal.set_algo_id(algorithm_id);
			goal.set_cities(&list_of_points);
			goal.set_current_city(&(list_of_points[end]));
			goal.set_previous_state(NULL);
			goal.set_roads(&list_of_roads);
			goal.set_goal(&(list_of_points[end]));
			goal.set_distance(0);
			goal.set_time(0);
			visited_points = 0;
			expanded_points = 0;
			sol = SEARCH(&initial, &goal, &visited_points, &expanded_points);
			cout << "\nVisited points:" << visited_points << " and expanded points:" << expanded_points << "\n";
			if (sol != NULL)
				sol->print_route();			else
				cout << "\nCould not find path.\n";
			break;
		}

	}


	return 0;
}