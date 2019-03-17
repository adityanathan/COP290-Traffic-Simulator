#ifndef interaction_h
#define interaction_h

class Road;
#include "vehicle.hpp"
#include "road.hpp"
#include "collisions.hpp"
#include "road.hpp"
#include <vector>
using namespace std;

class Interaction
{
private:
        Road *road;

public:
        Interaction(Road *r);

        vector<Vehicle *> create_vehicle_list_copy(vector<Vehicle *> v);

        void lane_change(Vehicle *a, Vehicle *b);

        void collision_resolution(Vehicle *a, Vehicle *b);

        vector<Vehicle *> update();


};
#endif
