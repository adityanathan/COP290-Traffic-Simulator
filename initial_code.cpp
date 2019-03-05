#include <string>

using namespace std;


class Road
{
private:
    int road_id;
    int road_length;
    int road_width;
    int road_signal;
    int signal_color;

public:
    void Road(int rd_id, int rd_length, int rd_width, int rd_signal)
    {
        this->road_id=rd_id;
        this->road_length=rd_length;
        this->road_width=rd_width;
        this->road_signal=rd_signal;
        this->signal_color="red";
    }

    void get_id() { return this->road_id; }
    void get_road_length() { return this->road_length; }
    void get_road_width() { return this->road_width; }
    void get_road_signal() { return this->road_signal; } //Distance of signal from start point
    void get_signal_color() { return signal_color; }

    void set_signal_color(int sgn_color)
    {
        if(sgn_color=0 || sgn_color=1)
        {
            signal_color=sgn_color;
            //Red is 0 and Green is 1.
        }
        else
        {
            throw "Invalid Signal Color"
        }
    }
};

class Vehicle
{
private:
    int max_speed;
    int acceleration;
    string type;
    int length;
    int width;
    int pos_x;
    int pos_y;
    static int default_max_speed=0;
    static int default_acceleration=0;
public:
    void Vehicle(string vehicle_type, int vehicle_length, int vehicle_width)
    {
        max_speed=default_max_speed;
        acceleration=default_acceleration;
        type=vehicle_type;
        length=vehicle_length;
        width=vehicle_width;
    }

    void set_max_speed(int speed) { max_speed = speed; }
    void set_acceleration(int acc) { acceleration = acc; }
    void position



}
