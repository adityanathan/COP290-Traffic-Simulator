using namespace std;
class Road
{
private:
        int length;
        int width;
        int signal_color;
        int signal_distance;

public:

        Road(int len, int wid, int dist)
        {
                length = len;
                width = wid;
                signal_color = 0; //0 is RED and 1 is GREEN
                signal_distance = dist;
        }
        int get_length() {return length;}
        int get_width() {return width;}
        int get_sig_distance() {return signal_distance;}
        int get_signal_color() {return signal_color;}

        void set_sig_colour(int col) {signal_color = col;}
};
