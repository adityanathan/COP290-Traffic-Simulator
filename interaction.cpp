#include <vector>
#include "Collision.h"
#include "Road.h"
using namespace std;
using namespace Collision;
class Interaction
{
private:
        vector<Vehicle *> vehicles;
        Road *road;

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

        void lane_change(Vehicle *a, Vehicle *b)
        {
                int zone_startx = b->pos[0];
                int zone_endx = b->pos[0]-b->width;
                int zone_topy_start = b->pos[1];
                int zone_bottomy_start= b->pos[1] - b->length;
                Vehicle *top; Vehicle *bottom; int flag=0;
                for(int i=zone_start; i>=zone_end; i--)
                {
                        for(int j=zone_topy_start; j<road->get_length(); j++)
                        {
                                if(road->road_map[i][j].v)
                                {
                                        top = v;
                                        flag=1;
                                        break;
                                }
                        }
                        if(flag==1) {break;}
                }

                flag=0;

                for(i=zone_start; i>=zone_end; i--)
                {
                        for(j=zone_bottomy_start; j>=0; j++)
                        {
                                if(road->road_map[i][j].v)
                                {
                                        bottom = v;
                                        flag=1;
                                        break;
                                }
                        }
                        if(flag==1) {break;}
                }

                int top_distance = top->pos[1] - b->pos[1];
                int bottom_distance = b->pos[1] - top->pos[1];

                if(bottom_distance > a->length)
                {
                        vector<int> v=a->get_velocity();
                        v[1]=-1;
                        a->set_velocity(v);
                }
                else if(top_distance > a->length)
                {
                        vector<int> v=a->get_velocity();
                        v[1]=1;
                        a->set_velocity(v);
                }
                else
                {
                        a->acceleration=(int) -1*relative_velocity_magnitude/(2*relative_distance_magnitude);
                }



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
                int relative_velocity_magnitude = (int) (Collision.vector_magnitude(relative_velocity) + 0.5); //To prevent rounding error.
                int relative_distance_magnitude = (int) (Collision.vector_magnitude(distance_between_vehicles) + 0.5);
                if(Collisions.rectangle_rectangle_collision_main(a,b,1))
                {
                        if(relative_distance_magnitude<=1)
                        {
                                a->acceleration=b->acceleration;
                        }
                        a->velocity[0]=b->velocity[0];
                        lane_change(a,b); //Lane change does deceleration automatically if necessary
                }
        }

        void update()
        {
                vector<Vehicle *> old_state;

                if (road->get_signal_color()==0)
                {
                        vector<int> temp(2,0);
                        temp[0]=road->get_sig_distance();
                        temp[1]=road->get_length();
                        Vehicle signal(road->get_length(), 1, "signal", 0, 0, '|', temp);
                        old_state.push_back(&signal);
                        for(int i=width-1; i>=0; i--)
                        {
                                for(int j=length-1; j>=0; j++)
                                {
                                        if(road->road_map[i][j].v)
                                        {
                                                old_state.push_back(road->road_map[i][j].v);
                                        }
                                }
                        }
                        bool is_collision;
                        for(i=0;i<old_state.size()-1;i++)
                        {
                                is_collision=false;
                                for(j=i+1;j<old_state.size();j++)
                                {
                                        vector<int> t1 = Collisions.rectangle_rectangle_collision_main(old_state[i],old_state[j],1);
                                        if(t1[1]==1)
                                        {
                                                collision_resolution(old_state[i],old_state[j]);
                                                is_collision=true;
                                        }
                                }
                                if(!is_collision)
                                {
                                        int a = old_state[i]->get_acceleration();
                                        old_state[i]->set_acceleration(a+1);
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
                                        if(!road->road_map[i][j].v)
                                        {
                                                old_state.push_back(road->road_map[i][j].v);
                                        }
                                }
                        }

                        bool is_collision;
                        for(i=0;i<old_state.size()-1;i++)
                        {
                                is_collision=false;
                                for(j=i+1;j<old_state.size();j++)
                                {
                                        vector<int> t1 = Collisions.rectangle_rectangle_collision_main(old_state[i],old_state[j],1);
                                        if(t1[1]==1)
                                        {
                                                collision_resolution(old_state[i],old_state[j]);
                                                is_collision=true;
                                        }
                                }
                                if(!is_collision)
                                {
                                        int a = old_state[i]->get_acceleration();
                                        old_state[i]->set_acceleration(a+1);
                                }
                        }

                        for(i=0; i<old_state.size(); i++)
                        {
                                old_state[i]->update(1);
                        }
                }

        }


};
