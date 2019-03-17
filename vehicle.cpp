#include "vehicle.hpp"
using namespace std;

        Vehicle::Vehicle(Road *r, int len, int wid, string col, int max_sp, int acc, char disp, int i, vector<int> position)
        {
                rd = r;
                length = len;
                width = wid;
                id = i;
                color=col;
                max_speed=max_sp;
                acceleration=acc;
                pos = position;
                velocity.push_back(max_sp);
                velocity.push_back(0);
                display = disp;
                is_accident = false;
        }

        Vehicle::Vehicle(const Vehicle &obj)
        {
                rd=obj.rd;
                length = obj.length;
                width = obj.width;
                id = obj.id;
                color = obj.color;
                max_speed = obj.max_speed;
                acceleration = obj.acceleration;
                pos = obj.pos;
                velocity = obj.velocity;
                display = obj.display;
                is_accident = obj.is_accident;
        }
        int Vehicle::get_length() {return length;}
        int Vehicle::get_width() {return width;}
        int Vehicle::get_id() {return id;}
        string Vehicle::get_color() {return color;}
        int Vehicle::get_max_speed() {return max_speed;}
        int Vehicle::get_acceleration() {return acceleration;}
        vector<int> Vehicle::get_pos() {return pos;}
        vector<int> Vehicle::get_velocity() {return velocity;}
        int Vehicle::get_display_char() {return display;}
        int Vehicle::get_accident_truth() {return is_accident;}

        void Vehicle::set_acceleration(int acc) {acceleration=acc;}
        void Vehicle::set_pos(int x, int y) {pos[0]=x; pos[1]=y;}
        void Vehicle::set_velocity(vector<int> v) {velocity[0]=v[0]; velocity[1]=v[1];}

        void Vehicle::update(int time_step)
        {
                if(acceleration>=max_speed)
                {
                        acceleration=max_speed;
                }
                int vx=velocity[0]+acceleration*time_step;
                if(vx<=0)
                {
                        acceleration=0;
                        velocity[0]=0;
                }
                else if(vx>=max_speed)
                {
                        acceleration=0;
                        velocity[0]=max_speed;
                }

                int px=pos[0]+velocity[0]*time_step;
                int py=pos[1]+velocity[1]*time_step;
                if(py>=rd->get_length())
                {
                        pos[1]=rd->get_length()-1;
                }
                else if(py<0)
                {
                        pos[1]=0;
                }

                velocity[1]=0;

        }
