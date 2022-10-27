#include "Point.h"
#include "Road.h"
#include "import_output.h"
#include <iostream>
#include<stdio.h>
#include<math.h>
#include<cmath>
#define earth_radious_km 6371.0
#define pi 3.14159265

float deg_to_rad( float deg) {
	return deg * pi / 180;
}

float rad_to_deg(float rad) {
	return rad * 180 / pi;
}

float approximated_distance(float lat1, float lon1, float lat2, float lon2) {
	float lat1r, lon1r, lat2r, lon2r, u , v;
	lat1r = deg_to_rad(lat1);
	lon1r = deg_to_rad(lon1);
	lat2r = deg_to_rad(lat2);
	lon2r = deg_to_rad(lon2);
	u = sin((lat2r-lat1r)/2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earth_radious_km * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}
template <typename T>
int check_if_point_exists_in_list(char* name, std::vector<T>* list) {
	for (unsigned int i = 0; i < (list->size()); i++) {
		if (strcmp(name, ((*list)[i]).get_name()) == 0) {
			return i;
		}
	}
	return -1;
}

int check_if_road_exists_in_list(char* name, std::vector<Road>* list) {
	for (unsigned int i = 0; i < (list->size()); i++) {
		if (strcmp(name, ((*list)[i]).get_name()) == 0) {
			return i;
		}
	}
	return -1;
}

int check_if_certain_points_exists_in_list(int start, int end, std::vector<Road>* list_of_roads) {
	if ( (start == -1) || (end == -1)) {
		return -1;
	}
	for (unsigned int i = 0; i < (list_of_roads->size()); i++) {
		if ( (   (start == ((*list_of_roads)[i]).get_start()) && (end == ((*list_of_roads)[i]).get_end())  ) ||
			((end == ((*list_of_roads)[i]).get_start()) && (start == ((*list_of_roads)[i]).get_end()))    )
		{
			return i;
		}
	}
	return -1;


}


int read_from_file(char* name_of_file, std::vector<Point>* list_of_points, std::vector<Road>* list_of_roads) {

	FILE* file_pointer;
	int number_of_points;
	int number_of_roads;
	int number_of_characters = 30;
	int number_of_already_points = list_of_points->size();
	int number_of_already_roads = list_of_roads->size();

	int err = fopen_s(&file_pointer, name_of_file , "r");
	if (err != 0) {
		std::cout << "\nError in reading the file\n";
		return 1;
	}

	fscanf_s(file_pointer, "%d", &number_of_points);
	//list_of_points->reserve(number_of_points);
	list_of_points->resize(number_of_already_points + number_of_points);
	for (int i = number_of_already_points; i < number_of_points + number_of_already_points; i++) {
		float temp_longitude, temp_latitude;
		char temp_name[30];
		fscanf_s(file_pointer, "%s", temp_name, number_of_characters);
		fscanf_s(file_pointer, "%f", &temp_latitude);
		fscanf_s(file_pointer, "%f", &temp_longitude);
		((*list_of_points)[i]).set_id(i);
		((*list_of_points)[i]).set_name(temp_name);
		((*list_of_points)[i]).set_longit(temp_longitude);
		((*list_of_points)[i]).set_latit(temp_latitude);
		//list_of_points->push_back(new Point(i, temp_name, temp_longitude, temp_latitude));
	}

	fscanf_s(file_pointer, "%d", &number_of_roads);
	//list_of_roads->reserve(number_of_roads);
	list_of_roads->resize(number_of_already_roads + number_of_roads);
	for (int i = number_of_already_roads; i < number_of_already_roads + number_of_roads; i++) {
		float temp_distance;
		int temp_time;
		int start;
		int end;
		char temp_name[30];
		char temp_name_for_search[30];
		fscanf_s(file_pointer, "%s", temp_name, number_of_characters);
		fscanf_s(file_pointer, "%s", temp_name_for_search, number_of_characters);
		start = check_if_point_exists_in_list(temp_name_for_search, list_of_points);
		if (start == -1) {
			std::cout << "\nThe name " << temp_name_for_search << " does not exist in the list of points\n";
			fclose(file_pointer);
			return 2;
		}
		fscanf_s(file_pointer, "%s", temp_name_for_search, number_of_characters);
		end = check_if_point_exists_in_list(temp_name_for_search, list_of_points);
		if (end == -1) {
			std::cout << "\nThe name " << temp_name_for_search << " does not exist in the list of points\n";
			fclose(file_pointer);
			return 2;
		}

		fscanf_s(file_pointer, "%f", &temp_distance);
		fscanf_s(file_pointer, "%d", &temp_time);
		((*list_of_roads)[i]).set_name(temp_name);
		((*list_of_roads)[i]).set_start(start);
		((*list_of_roads)[i]).set_end(end);
		((*list_of_roads)[i]).set_distance(temp_distance);
		((*list_of_roads)[i]).set_time(temp_time);
		//list_of_roads->push_back(new Road( temp_name, start , end , temp_distance, temp_time));
	}
	std::cout<<"\n"<< number_of_points << " cities have been loaded.\n" << number_of_roads << " roads have been loaded.\n";
	fclose(file_pointer);
	return 0;

}

int save_at_file(char* name_of_file, std::vector<Point>* list_of_points, std::vector<Road>* list_of_roads) {
	FILE* file_pointer;
	int number_of_points = list_of_points->size();
	int number_of_roads = list_of_roads->size();

	int err = fopen_s(&file_pointer, name_of_file, "w");
	if (err != 0) {
		std::cout << "\nError in accessing the file\n";
		return 1;
	}

	fprintf_s(file_pointer, "%d\n", number_of_points);
	for (int i = 0; i < number_of_points; i++) {
		fprintf_s(file_pointer, "%s\n%f\n%f\n", ((*list_of_points)[i]).get_name() , ((*list_of_points)[i]).get_longit(), ((*list_of_points)[i]).get_latit());
	}
	fprintf_s(file_pointer, "%d\n", number_of_roads);
	for (int i = 0; i < number_of_roads; i++) {
		int id_start = ((*list_of_roads)[i]).get_start();
		int id_end = ((*list_of_roads)[i]).get_end();
		fprintf_s(file_pointer, "%s\n%s\n%s\n%f\n%d\n", ((*list_of_roads)[i]).get_name(), ((*list_of_points)[id_start]).get_name(), ((*list_of_points)[id_end]).get_name(), ((*list_of_roads)[i]).get_distance(), ((*list_of_roads)[i]).get_time() );
	}
	return 0;
}