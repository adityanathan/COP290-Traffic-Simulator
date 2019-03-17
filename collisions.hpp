#ifndef collisions_h
#define collisions_h
#include "vehicle.hpp"
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

        vector<int> vector_add(vector<int> a, vector<int> b);

        vector<int> vector_sub(vector<int> a, vector<int> b);

        vector<int> vector_scalar_mult(vector<int> a, int b);

        double vector_magnitude(vector<int> a);

        vector<int> vector_component(vector<int> a, vector<int> direction_vector);

        vector<int> line_line_intersection(vector<int> a, vector<int> b, vector<int> c, vector<int> d);

        vector<vector<int>> points_to_check(vector<int> pos, vector<int> x, vector<int> y, vector<int> displacement);

        vector<int> rectangle_rectangle_vertex_collision (Vehicle *obj1, Vehicle *obj2, int time);

        vector<int> rectangle_rectangle_collision_main(Vehicle *obj1, Vehicle *obj2, int time);
#endif
