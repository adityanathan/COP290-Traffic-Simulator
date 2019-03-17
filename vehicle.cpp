#include "vehicle.hpp"
#include <vector>
#include <string>
using namespace std;

class Vehicle
{
private:
        int length;
        int width;
        int id;
        string color;
        int max_speed;
        int acceleration; //Make sure acceleration is not greater than max_speed.
        vector<int> pos;
        vector<int> velocity;
        char display;
        bool is_accident;
        // In xml file when multiple vehicles are defined simultaneously, in the simulation they will
        //side by side. If no of vehicles exceeds road width, it will throw an error.

        //All vehicles will be spawned at the starting line.
public:
        Vehicle(int len, int wid, string col, int max_sp, int acc, char disp, int i, vector<int> position)
        {
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

        Vehicle(const Vehicle &obj)
        {
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
        int get_length() {return length;}
        int get_width() {return width;}
        int get_id() {return id;}
        string get_color() {return color;}
        int get_max_speed() {return max_speed;}
        int get_acceleration() {return acceleration;}
        vector<int> get_pos() {return pos;}
        vector<int> get_velocity() {return velocity;}
        int get_display_char() {return display;}
        int get_accident_truth() {return is_accident;}

        void set_acceleration(int acc) {acceleration=acc;}
        void set_pos(int x, int y) {pos[0]=x; pos[1]=y;}
        void set_velocity(int vx, int vy) {velocity[0]=vx; velocity[1]=vy;}

        void update(int time_step)
        {
                vx=velocity[0]+acceleration*time_step;
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
                pos[0]=pos[0]+velocity[0]*time_step;
                pos[1]=pos[1]+velocity[1]*time_step;

        }
};
