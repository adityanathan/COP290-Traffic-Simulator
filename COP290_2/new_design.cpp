#include <tuple>
//The Road class with functions to handle all the updates related to the status of pixels on the road
class Road
{
public:
  int road_length;
  int road_width;
  int signal; //0 for red, 1 for green
  pixel road_map [road_width][road_length];

public:
  //Constructor
  Road(int l, int w, int s)
  {
    this->road_length = l;
    this->road_width = w;
    for (int i = 0; i<l; i++)
    {
      for(int j = 0; j<w; j++)
      {
        this->road_map[j][i] = pixel();
      }
    }
    this->signal = s;

  }

  void next_second()
  {

  }

  bool move_front(int upper_right, int length, int width);

  bool lane_change();

  void on_screen()
  {

  }

};


//Pixels with attributes to get related vehicles
class pixel
{
public:
  char display;
  Vehicle *v = NULL;

public:
  pixel()
  {
    this->display=" ";
  }

  //To set the vehicle when pixel gets occupied
  void set_v(Vehicle *v)
  {
    this->v = v;   //Is this the correct way to assign the pointer
    this->display = *v.display;
  }
};

class Vehicle
{
private:
  int length;
  int width;
  tuple<int,int> upper_right;  //gives the position of its upper right corner on pixel map
  //int speed;                For Future Use
  //int acc;
  char display;
  string color;
  string type;

public:
  Vehicle(int l, int w, tuple<int,int> pos, string c, string t, char d)
  {
    this->length = l;
    this->width = w;
    this->upper_right = pos;
    this->color = c;
    this->type = t;
    this->display = d;
  }

  void update(tuple<int,int> pos)
  {
    upper_right = pos;
  }


};
