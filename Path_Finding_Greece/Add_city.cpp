#include"Add_city.h"

void add_city( std::vector<Point>* list_of_points) {
	char temp_point_name[30];
	float temp_latitude,temp_longitude;
	while (1) {
		std::cout << "\nGive the name of the city:\n";
		std::cin >> temp_point_name;
		int checker = check_if_point_exists_in_list(temp_point_name, list_of_points);
		if (checker != -1) {
			std::cout <<"\n"<< temp_point_name << " with latitude:"
				<< ((*list_of_points)[checker]).get_latit()
				<< " and longitude:" << ((*list_of_points)[checker]).get_longit()
				<< " is already in the list.\n";
			break;
		}
		std::cout << "\nGive the latitude of the City:\n";
		std::cin >> temp_latitude;
		std::cout << "\nGive the longitude of the City:\n";
		std::cin >> temp_longitude;
		break;
	}
	list_of_points->resize(list_of_points->size() + 1);
	((*list_of_points)[list_of_points->size() - 1]).set_id(list_of_points->size() - 1);
	((*list_of_points)[list_of_points->size() - 1]).set_name(temp_point_name);
	((*list_of_points)[list_of_points->size() - 1]).set_longit(temp_longitude);
	((*list_of_points)[list_of_points->size() - 1]).set_latit(temp_latitude);

	}