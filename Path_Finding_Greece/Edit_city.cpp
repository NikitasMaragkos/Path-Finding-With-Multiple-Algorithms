#include"Edit_city.h"

void edit_city(std::vector<Point>* list_of_points) {
	int id_of_city;
	int flag_for_edit = 1;
	char temp_point_name[30];
	float temp_latitude, temp_longitude;
	std::cout << "\nGive the name of city to edit:";
	std::cin >> temp_point_name;
	id_of_city = check_if_point_exists_in_list(temp_point_name, list_of_points);
	if (id_of_city == -1) {
		std::cout << "\nThe city " << temp_point_name << " does not exist in the list.\n";
		return;
	}
	else {
		while (flag_for_edit != 0) {
			std::cout << "\nCity: " << ((*list_of_points)[id_of_city]).get_name() << " with latitude " << ((*list_of_points)[id_of_city]).get_latit() << " and longitude " << ((*list_of_points)[id_of_city]).get_longit() << "\n";
			std::cout << "\nWhat do you want to edit?\n0.Nothing\n1.Name\n2.Latitude\n3.Longitude\nYour choice:";
			std::cin >> flag_for_edit;
			switch (flag_for_edit) {
			case 0:
				break;
			case 1:
				std::cout << "\nGive the new name:";
				std::cin >> temp_point_name;
				((*list_of_points)[id_of_city]).set_name(temp_point_name);
				break;
			case 2:
				std::cout << "\nGive the latitude:";
				std::cin >> temp_latitude;
				((*list_of_points)[id_of_city]).set_latit(temp_latitude);
				break;
			case 3:
				std::cout << "\nGive the longitude:";
				std::cin >> temp_longitude;
				((*list_of_points)[id_of_city]).set_longit(temp_longitude);
				break;
			}
		}
	}
}