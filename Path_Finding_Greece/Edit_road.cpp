#include"Edit_road.h"

void edit_road(std::vector<Point>* list_of_points, std::vector<Road>* list_of_roads) {
	int id_of_road;
	int flag_for_edit = 1;
	int flag_for_continue = 1;
	int start, end, temp_start, temp_end, temp_time;
	float temp_distance;
	char temp_road_name[30], temp_start_name[30], temp_end_name[30];
	std::cout << "\n0.Quit\n1.Give the name of road to edit.\n2.Give the name of start and end\nYour choice:";
	std::cin >> flag_for_edit;

	switch (flag_for_edit) {
	case 0:
		break;
	case 1:
		std::cout << "\nGive the name of road to edit:";
		std::cin >> temp_road_name;
		id_of_road = check_if_road_exists_in_list(temp_road_name, list_of_roads);
		if (id_of_road == -1) {
			std::cout << "\nThe road " << temp_road_name << " does not exist in the list.\n";
			break;
		}
		else {
			while (flag_for_continue != 0) {
				start = (*list_of_roads)[id_of_road].get_start();
				end = (*list_of_roads)[id_of_road].get_end();
				std::cout << "\nThe road " << (*list_of_roads)[id_of_road].get_name() << " starts from " << (*list_of_points)[start].get_name() << " and ends to " << (*list_of_points)[end].get_name() << " with distance " << (*list_of_roads)[id_of_road].get_distance() << "km and time " << (*list_of_roads)[id_of_road].get_time() << " m.\n";
				std::cout << "What do you want to edit?\n0.Nothing\n1.Name\n2.Start\n3.End\n4.Distance\n5.Time\nYour choice:";
				std::cin >> flag_for_continue;
				switch (flag_for_continue) {
				case 0:
					break;
				case 1:
					std::cout << "\nGive new name for road:";
					std::cin >> temp_road_name;
					(*list_of_roads)[id_of_road].set_name(temp_road_name);
					break;
				case 2:
					std::cout << "\nGive new name for the start:";
					std::cin >> temp_start_name;
					temp_start = check_if_point_exists_in_list(temp_start_name, list_of_points);
					if (temp_start == -1) {
						std::cout << "\nThere is no city with this name is list.\n";
						break;
					}
					(*list_of_roads)[id_of_road].set_start(temp_start);
					break;
				case 3:
					std::cout << "\nGive new name for the end:";
					std::cin >> temp_end_name;
					temp_end = check_if_point_exists_in_list(temp_end_name, list_of_points);
					if (temp_end == -1) {
						std::cout << "\nThere is no city with this name is list.\n";
						break;
					}
					(*list_of_roads)[id_of_road].set_end(temp_end);
					break;
				case 4:
					std::cout << "\nGive new distance in km:";
					std::cin >> temp_distance;
					(*list_of_roads)[id_of_road].set_distance(temp_distance);
					break;
				case 5:
					std::cout << "\nGive new time in minutes:";
					std::cin >> temp_time;
					(*list_of_roads)[id_of_road].set_time(temp_time);
					break;
				}
			}
		}
		break;
	case 2:
		std::cout << "\nGive the start point name of road to edit:";
		std::cin >> temp_start_name;
		std::cout << "\nGive the end point name of road to edit:";
		std::cin >> temp_end_name;
		temp_start = check_if_point_exists_in_list(temp_start_name, list_of_points);
		temp_end = check_if_point_exists_in_list(temp_end_name, list_of_points);
		id_of_road = check_if_certain_points_exists_in_list(temp_start, temp_end , list_of_roads);
		if (id_of_road == -1) {
			std::cout << "\nThe road " << temp_start_name<<" to " << temp_end_name << " does not exist in the list.\n";
			break;
		}
		else {
			while (flag_for_continue != 0) {
				start = (*list_of_roads)[id_of_road].get_start();
				end = (*list_of_roads)[id_of_road].get_end();
				std::cout << "\nThe road " << (*list_of_roads)[id_of_road].get_name() << " starts from " << (*list_of_points)[start].get_name() << " and ends to " << (*list_of_points)[end].get_name() << " with distance " << (*list_of_roads)[id_of_road].get_distance() << "km and time " << (*list_of_roads)[id_of_road].get_time() << " m.\n";
				std::cout << "What do you want to edit?\n0.Nothing\n1.Name\n2.Start\n3.End\n4.Distance\n5.Time\nYour choice:";
				std::cin >> flag_for_continue;
				switch (flag_for_continue) {
				case 0:
					break;
				case 1:
					std::cout << "\nGive new name for road:";
					std::cin >> temp_road_name;
					(*list_of_roads)[id_of_road].set_name(temp_road_name);
					break;
				case 2:
					std::cout << "\nGive new name for the start:";
					std::cin >> temp_start_name;
					temp_start = check_if_point_exists_in_list(temp_start_name, list_of_points);
					if (temp_start == -1) {
						std::cout << "\nThere is no city with this name is list.\n";
						break;
					}
					(*list_of_roads)[id_of_road].set_start(temp_start);
					break;
				case 3:
					std::cout << "\nGive new name for the end:";
					std::cin >> temp_end_name;
					temp_end = check_if_point_exists_in_list(temp_end_name, list_of_points);
					if (temp_end == -1) {
						std::cout << "\nThere is no city with this name is list.\n";
						break;
					}
					(*list_of_roads)[id_of_road].set_end(temp_end);
					break;
				case 4:
					std::cout << "\nGive new distance in km:";
					std::cin >> temp_distance;
					(*list_of_roads)[id_of_road].set_distance(temp_distance);
					break;
				case 5:
					std::cout << "\nGive new time in minutes:";
					std::cin >> temp_time;
					(*list_of_roads)[id_of_road].set_time(temp_time);
					break;
				}
			}
		}
		break;
	}
}