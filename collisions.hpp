#ifndef collisions_h
#define collisions_h
#include "vehicle.hpp"
#include <cmath>
#include <climits>
#include <vector>
#include<math.h>
using namespace std;

	vector<int> vector_add(vector<int> a, vector<int> b);

	vector<int> vector_sub(vector<int> a, vector<int> b);

	bool rectangle_intersection(vector<int> pos1, vector<int> pos2, int length1, int length2, int width1, int width2);

	bool rectangle_rectangle_collision_main(Vehicle *a, Vehicle *b);
#endif
