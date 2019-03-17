#include <vector>
using namespace std;

class Interaction
{
private:
        vector<Vehicle *> vehicles;
        Road *road_map;

public:
        Interaction(vector<Vehicle *> v, Road *r)
        {
                vehicles = v;
        }

        vector<Vehicle *> create_vehicle_list_copy(vector<Vehicle *> v)
        {
                vector<Vehicle *> ans;

                for (i=0; i<v.size(); i++)
                {
                        ans.push_back(Vehicle(v[i]));
                }
                return ans;
        }

        void collision_resolution(Vehicle *a, Vehicle *b)
        {
                if(a->pos[0] > b->pos[0])
                {
                        Vehicle *c;
                        c=a;
                        a=b;
                        b=c;
                }
                int distance_between_vehicles = vector_sub(vector_add(b->pos,b->width),a->pos);
                int relative_velocity = vector_sub(a->velocity,b->velocity);
                int relative_velocity_magnitude = (int) (Collisions.vector_magnitude(relative_velocity) + 0.5); //To prevent rounding error.
                int relative_distance_magnitude = (int) (Collision.vector_magnitude(distance_between_vehicles) + 0.5);
                if(rectangle_rectangle_collision_main(a,b,1))
                {
                        if(relative_distance_magnitude<=1)
                        {
                                a->acceleration=b->acceleration;
                                a->velocity[0]=b->velocity[0];
                        }
                        a->acceleration=(int) -1*relative_velocity_magnitude/(2*relative_distance_magnitude);
                }
        }

        void update()
        {
                vector<Vehicle *> old_state;

                if (road_map->get_signal_color()==0)
                {
                        vector<int> temp(2,0);
                        temp[0]=road_map->get_sig_distance();
                        temp[1]=road_map->get_length();
                        Vehicle signal(road_map->get_length(), 1, "signal", 0, 0, '|', temp);
                        old_state.push_back(&signal);
                        for(int i=width-1; i>=0; i--)
                        {
                                for(int j=length-1; j>=0; j++)
                                {
                                        if(!road_map[i][j])
                                        {
                                                old_state.push_back(road_map[i][j]->v);
                                        }
                                }
                        }

                        for(i=0;i<old_state.size()-1;i++)
                        {
                                for(j=i+1;j<old_state.size();j++)
                                {
                                        vector<int> t1 = Collisions.rectangle_rectangle_collision_main(old_state[i],old_state[j],1);
                                        if(t1[1]==1)
                                        {
                                                collision_resolution(old_state[i],old_state[j]);
                                        }
                                }
                        }

                        for(i=0; i<old_state.size(); i++)
                        {
                                old_state[i]->update(1);
                        }
                }
                else
                {
                        for(int i=width-1; i>=0; i--)
                        {
                                for(int j=length-1; j>=0; j++)
                                {
                                        if(!road_map[i][j])
                                        {
                                                old_state.push_back(road_map[i][j]->v);
                                        }
                                }
                        }

                        for(i=0;i<old_state.size()-1;i++)
                        {
                                for(j=i+1;j<old_state.size();j++)
                                {
                                        vector<int> t1 = Collisions.rectangle_rectangle_collision_main(old_state[i],old_state[j],1);
                                        if(t1[1]==1)
                                        {
                                                collision_resolution(old_state[i],old_state[j]);
                                        }
                                }
                        }

                        for(i=0; i<old_state.size(); i++)
                        {
                                old_state[i]->update(1);
                        }
                }

        }


};
