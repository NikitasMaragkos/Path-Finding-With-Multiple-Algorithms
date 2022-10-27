#pragma once
#include<vector>
#include<string>



class Point;
class Road;

template <typename T>
extern int check_if_point_exists_in_list(char* name, std::vector<T>* list);

int check_if_road_exists_in_list(char* name, std::vector<Road>* list);

int check_if_certain_points_exists_in_list(int start, int end, std::vector<Road>* list_of_roads);

int read_from_file(char* name_of_file, std::vector<Point>* list_of_points, std::vector<Road>* list_of_roads);

int save_at_file(char* name_of_file, std::vector<Point>* list_of_points, std::vector<Road>* list_of_roads);

float deg_to_rad(float deg);

float rad_to_deg(float rad);

float approximated_distance(float lat1, float lon1, float lat2, float lon2);
