using namespace std;
class Road
{
private:
        int length;
        int width;
        int signal_color;
        int signal_distance;

public:
        vector<vector<tile>> road_map;
        
        Road(int len, int wid, int dist)
        {
                length = len;
                width = wid;
                signal_color = 0; //0 is RED and 1 is GREEN
                signal_distance = dist;
                this->road_map.resize(wid, vector<pixel>(len, pixel()));
        }
        int get_length() {return length;}
        int get_width() {return width;}
        int get_sig_distance() {return signal_distance;}
        int get_signal_color() {return signal_color;}

        void set_sig_colour(int col) {signal_color = col;}

        void update(vector<Vehicle *> a)
        {
                road_map.resize(wid, vector<pixel>(len, tile()));
                for(int i=0; i<a.size(); i++)
                {
                        for(int j=0;j<a[i]->length;j++)
                        {
                                for(int k=0;k<a[i]->width;k++)
                                {
                                        road_map[j][k].set_v(a[i]);
                                }
                        }
                }
        }

        void display()
        {
                update();

                for(int i=0; i<width; i++)
                {
                        cout<<"-";
                }
                cout<<endl;
                for(i=0; i<width; i++)
                {
                        for(int j=0; j<length; j++)
                                cout<<road_map[i][j].display;
                        cout<<endl;
                }
                for(i=0; i<width; i++)
                {
                        cout<<"-";
                }
                cout<<endl;
                cout<<endl;
        }
};
//For vehicles and road.
//  width w
// ----------
//|         |
//|         |   length l
//|         |
// ----------
