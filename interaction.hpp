#ifndef interaction_h
#define interaction_h

#include "vehicle.hpp"
#include "road.hpp"
#include <vector>
using namespace std;

class Interaction
{
private:
        vector<Vehicle *> vehicles;
        Road *road_map;

public:
        Interaction(vector<Vehicle *> v, Road *r)

        vector<Vehicle *> create_vehicle_list_copy(vector<Vehicle *> v)

        void collision_resolution(Vehicle *a, Vehicle *b)

        void update()


};
#endif
