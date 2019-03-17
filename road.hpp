#ifndef road_h
#define road_h
using namespace std;
class Road
{
private:
        int length;
        int width;
        int signal_color;
        int signal_distance;
        vector<vector<tile>> road_map;

public:

        Road(int len, int wid, int dist)

        int get_length()
        int get_width()
        int get_sig_distance()
        int get_signal_color()

        void set_sig_colour(int col)

        void update(vector<Vehicle *> a)
};
#endif
//For vehicles and road.
//  width w
// ----------
//|         |
//|         |   length l
//|         |
// ----------
