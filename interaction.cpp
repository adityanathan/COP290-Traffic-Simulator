#include "interaction.hpp"
using namespace std;

        Interaction::Interaction(Road *r)
        {
                road = r;
        }

        // vector<Vehicle *> Interaction::create_vehicle_list_copy(vector<Vehicle *> v)
        // {
        //         vector<Vehicle *> ans;
        //         Vehicle *temp;
        //         for (int i=0; i<v.size(); i++)
        //         {
        //                 temp = &Vehicle(*v[i])
        //                 ans.push_back(temp);
        //         }
        //         return ans;
        // }

        void Interaction::lane_change(Vehicle *a, Vehicle *b)
        {
                int zone_startx = b->get_pos()[0];
                int zone_endx = b->get_pos()[0]-b->get_width();
                int zone_topy_start = b->get_pos()[1];
                int zone_bottomy_start= b->get_pos()[1] - b->get_length();
                Vehicle *top; Vehicle *bottom; int flag=0;
                for(int i=zone_startx; i>=zone_endx; i--)
                {
                        for(int j=zone_topy_start; j<road->get_length(); j++)
                        {
                                if(road->road_map[i][j].v)
                                {
                                        top = road->road_map[i][j].v;
                                        flag=1;
                                        break;
                                }
                        }
                        if(flag==1) {break;}
                }

                flag=0;

                for(int i=zone_startx; i>=zone_endx; i--)
                {
                        for(int j=zone_bottomy_start; j>=0; j++)
                        {
                                if(road->road_map[i][j].v)
                                {
                                        bottom = road->road_map[i][j].v;
                                        flag=1;
                                        break;
                                }
                        }
                        if(flag==1) {break;}
                }
                bool is_lane_change_possible=false;
                int top_distance = top->get_pos()[1] - b->get_pos()[1];
                if(bottom)
                {
                        int bottom_distance = b->get_pos()[1] - top->get_pos()[1];
                        if(bottom_distance > a->get_length())
                        {
                                vector<int> v=a->get_velocity();
                                v[1]=-1;
                                a->set_velocity(v);
                                is_lane_change_possible=true;
                        }
                }

                if(top)
                {
                        if(!is_lane_change_possible && top_distance > a->get_length())
                        {
                                vector<int> v=a->get_velocity();
                                v[1]=1;
                                a->set_velocity(v);
                                is_lane_change_possible=true;
                        }
                }

                vector<int> width_temp(2,0);
                width_temp[0]=b->get_width();
                width_temp[1]=0;
                vector<int> distance_between_vehicles = vector_sub(vector_sub(b->get_pos(),width_temp),a->get_pos());
                vector<int> relative_velocity = vector_sub(a->get_velocity(),b->get_velocity());
                int relative_velocity_magnitude = (int) (vector_magnitude(relative_velocity) + 0.5); //To prevent rounding error.
                int relative_distance_magnitude = (int) (vector_magnitude(distance_between_vehicles) + 0.5);

                if(!is_lane_change_possible)
                {
                        a->set_acceleration((int) -1*relative_velocity_magnitude/(2*relative_distance_magnitude));
                }
        }

        void Interaction::collision_resolution(Vehicle *a, Vehicle *b)
        {
                if(a->get_pos()[0] > b->get_pos()[0])
                {
                        Vehicle *c;
                        c=a;
                        a=b;
                        b=c;
                }
                vector<int> width_temp(2,0);
                width_temp[0]=b->get_width();
                width_temp[1]=0;
                vector<int> distance_between_vehicles = vector_sub(vector_sub(b->get_pos(),width_temp),a->get_pos());
                vector<int> relative_velocity = vector_sub(a->get_velocity(),b->get_velocity());
                int relative_velocity_magnitude = (int) (vector_magnitude(relative_velocity) + 0.5); //To prevent rounding error.
                int relative_distance_magnitude = (int) (vector_magnitude(distance_between_vehicles) + 0.5);
                if(rectangle_rectangle_collision_main(a,b,1)[1]==1)
                {
                        if(relative_distance_magnitude<=1)
                        {
                                a->set_acceleration(b->get_acceleration());
                        }
                        vector<int> temp(2,0);
                        temp.push_back(b->get_velocity()[0]);
                        temp.push_back(a->get_velocity()[1]);
                        a->set_velocity(temp);
                        lane_change(a,b); //Lane change does deceleration automatically if necessary
                }
        }

        vector<Vehicle *> Interaction::update()
        {
                vector<Vehicle *> old_state;

                if (road->get_signal_color()==0)
                {
                        vector<int> temp(2,0);
                        temp[0]=road->get_sig_distance();
                        temp[1]=road->get_length();
                        Vehicle signal(road, road->get_length(), 1, "red", 0, 0, '|', -1, temp);
                        old_state.push_back(&signal);
                        for(int i=road->get_width()-1; i>=0; i--)
                        {
                                for(int j=road->get_length()-1; j>=0; j++)
                                {
                                        if(road->road_map[i][j].v)
                                        {
                                                old_state.push_back(road->road_map[i][j].v);
                                        }
                                }
                        }
                        bool is_collision;
                        for(int i=0;i<old_state.size()-1;i++)
                        {
                                is_collision=false;
                                for(int j=i+1;j<old_state.size();j++)
                                {
                                        vector<int> t1 = rectangle_rectangle_collision_main(old_state[i],old_state[j],1);
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

                        for(int i=0; i<old_state.size(); i++)
                        {
                                old_state[i]->update(1);
                        }
                }
                else
                {
                        for(int i=road->get_width()-1; i>=0; i--)
                        {
                                for(int j=road->get_length()-1; j>=0; j++)
                                {
                                        if(!road->road_map[i][j].v)
                                        {
                                                old_state.push_back(road->road_map[i][j].v);
                                        }
                                }
                        }

                        bool is_collision;
                        for(int i=0;i<old_state.size()-1;i++)
                        {
                                is_collision=false;
                                for(int j=i+1;j<old_state.size();j++)
                                {
                                        vector<int> t1 = rectangle_rectangle_collision_main(old_state[i],old_state[j],1);
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

                        for(int i=0; i<old_state.size(); i++)
                        {
                                old_state[i]->update(1);
                        }

                        return old_state;
                }

        }
