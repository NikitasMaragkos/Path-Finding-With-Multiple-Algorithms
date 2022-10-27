#include"Add_road.h"

void add_road(std::vector<Point>* list_of_points, std::vector<Road>* list_of_roads) {
	char temp_road_name[30];
	char temp_start_name[30];
	char temp_end_name[30];
	float temp_distance;
	int temp_time;
	int start, end;

	std::cout << "\nGive the name of the road:\n";
	std::cin >> temp_road_name;
	std::cout << "\nGive the name of the road's start:\n";
	std::cin >> temp_start_name;
	start = check_if_point_exists_in_list(temp_start_name, list_of_points);
	if (start == -1) {
		std::cout << "\nThe city " << temp_start_name << " is not in the list\n";
		return;
	}
	std::cout << "\nGive the name of the road's end:\n";
	std::cin >> temp_end_name;
	end = check_if_point_exists_in_list(temp_end_name, list_of_points);
	if (end == -1) {
		std::cout << "\nThe city " << temp_end_name << " is not in the list\n";
		return;
	}
	std::cout << "\nGive the distance of the road:\n";
	std::cin >> temp_distance;
	std::cout << "\nGive the time for the road:\n";
	std::cin >> temp_time;

	list_of_roads->resize(list_of_roads->size() + 1);
	(*list_of_roads)[list_of_roads->size() - 1].set_name(temp_road_name);
	(*list_of_roads)[list_of_roads->size() - 1].set_start(start);
	(*list_of_roads)[list_of_roads->size() - 1].set_end(end);
	(*list_of_roads)[list_of_roads->size() - 1].set_distance(temp_distance);
	(*list_of_roads)[list_of_roads->size() - 1].set_time(temp_time);


}