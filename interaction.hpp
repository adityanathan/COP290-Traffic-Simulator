#ifndef interaction_h
#define interaction_h

class Road;
#include "vehicle.hpp"
#include "collisions.hpp"
#include "road.hpp"
#include <vector>
using namespace std;

	void collision_resolution(int i, int j, vector<Vehicle *> vh);

	void interaction_update(Road* road, vector<Vehicle *> a);

#endif
