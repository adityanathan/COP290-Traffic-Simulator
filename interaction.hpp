#ifndef interaction_h
#define interaction_h

class Road;
#include "vehicle.hpp"
#include "road.hpp"
#include <vector>
#include <time.h>
using namespace std;

	vector<int> check_movable_zone(Vehicle a,vector<vector<char>> rd);

	void interaction_update(Road *r, vector<Vehicle *> a, vector<int> sig_time);

#endif
