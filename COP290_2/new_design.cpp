#include <tuple>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
//The Road class with functions to handle all the updates related to the status of pixels on the road
//everywhere in tuple, in accessign arrays first coordinate denotes y distance from top to bottom
//second coordinate denotes x distance from left to right
//length is along x axis, width is along y axis

//Pixels with attributes to get related vehicles



///////WARNING: To do {
    /* Making sure that when a vehicle moves ahead the pixel values behindd it are set to zero if there is no vehicle behind it */

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
  void set_v(Vehicle *vehicle)
  {
    this->v = vehicle;   //Is this the correct way to assign the pointer
    if ( v ) // if v is not null
    {
        this->display = *v.display;
    }
    else
    {
        this->display = " ";
    }
  }
};

class Vehicle
{
private:
  int length;
  int width;
  char display;
  string color;
  string type;

public:
  tuple<int,int> upper_right;  //gives the position of its upper right corner on pixel map
  //int speed;                For Future Use
  //int acc;

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

class Road
{
public:
  int road_length;
  int road_width;
  int signal; //0 for red, 1 for green
  vector<vector<pixel>> road_map; //Changes made.

public:
  //Constructor
  Road(int l, int w, int s)
  {
    this->road_length = l;
    this->road_width = w;
    this->road_map.resize(w, vector<pixel>(l, pixel())); //Changes made.
    this->signal = s;
  }

  void next_second()
  {
    for (int i = road_length-1; i>=0; i--)
    {
      vector<Vehicle> considered_v;
      for (int j = 0; j<road_width; j++)
      {
        if (this->road_map[j][i].display!=" ")
        {
          tuple<int,int> temp = (this->road_map[j][i].v->upper_right);
          if (temp == make_tuple(j,i))
          {
            considered_v.push_back(this->road_map[j][i].v); //Pushing all valid vehicles on the road into this list.
          }
        }
      }

      random_shuffle(considered_v.begin(), considered_v.end());

      for (int k = 0; k<considered_v.size(); k++)
      {
        Vehicle *v = considered_v.get(k);
        if (move_front(v->upper_right, v->length, v->width)==1)
        {
          do_move_front(v);
        }
        else if (lane_change(v->upper_right, v->length, v->width)!=0)
        {
          do_lane_change(v, lane_change(v->upper_right, v->length, v->width));
        }
      }
    }

  }

  int move_front(tuple<int,int> upper_right, int width)
  {
    int ans = 1;
    for (int j=0; j<width; j++)
    {
      if (road_map[get<0>(upper_right)+j][get<1>(upper_right)+1].v) //Changes made.
      {
        ans = 0;
        break;
      }
    }
    return ans;
    // 1 for yes, move front 0 for no, can't move move_front
    // int because lane_change will have three options 0-no, 2-left(up along y axis), 1-right(down along y axis)
  }

  int lane_change(tuple<int,int> upper_right, int length, int width)//only one pixel top or bottom
  {
    int ans = 1;
    //tuple<int,int> down_right = make_tuple(get<0>(upper_right)+length-1,get<1>(upper_right));
    int a = get<0>(upper_right);
    int b = get<1>(upper_right);

    for (int j = 0; j < width; j++)
    {
      if !(road_map[a+1+j][b+1].v)
      {
        ans = 2;
        break
      }
    }
    if (ans==1)
    {
      for (int i=0; i<length; i++)
      {
        if !(road_map[a+width][b+1-i].v)
        {
          ans = 2;
          break;    //Confusing
        }
      }
    }

    if (ans==2)
    {
        //int a = get<0>(upper_right);
        //int b = get<1>(upper_right);

        for (int j = 0; j<width; j++)
        {
          if (road_map[a-1+j][b+1].v!=NULL)
          {
            ans = 0;
          }
        }

        if (ans==2)
        {
          for (int i=0; i<length; i++)
          {
            if road_map[a-1][b+1-i].v!=NULL
            {
              ans = 0;
              break;
            }
          }
        }
    }

    return ans;
  }

  void do_move_front(Vehicle *v)
  {
    int a = get<0>(upper_right);
    int b = get<1>(upper_right);

    tuple<int,int> pos = make_tuple(a,b+1);
    v->update(pos);

    int c = a
    int d = b - v->length +1;

    for (int j=0; j<width; j++)
    {
      this->road_map[a+j][b+1].set_v(v);
      this->road_map[c+j][d].set_v(NULL);
    }
  }

  void do_lane_change(Vehicle *v, int r_or_l)
  {
    if (r_or_l == 1)
    {
      int a = get<0>(v->upper_right);
      int b = get<1>(v->upper_right);

      tuple<int,int> pos = make_tuple(a+1,b+1);
      v->update(pos);

      for (int j = 0; j < width; j++)
      {
        this->road_map[a+1+j][b+1].set_v(v);
        this->road_map[a+j][b-length+1].set_v(NULL);
      }

      for (int i=0; i<length; i++)
      {
        this->road_map[a+width][b+1-i].set_v(v);
        this->road_map[a][b-i].set_v(NULL);
      }
    }
    else if (r_or_l == 2)
    {
      int a = get<0>(v->upper_right);
      int b = get<1>(v->upper_right);

      tuple<int,int> pos = make_tuple(a-1,b+1);
      v->update(pos);

      for (int j = 0; j<width; j++)
      {
        this->road_map[a-1+j][b+1].set_v(v);
        this->road_map[a+j][b-length+1].set_v(NULL);
      }
      for (int i=0; i<length; i++)
      {
        this->road_map[a-1][b+1-i].set_v(v);
        this->road_map[a+width-1][b-i].set_v(NULL);
      }
    }
  };

  void on_screen()
  {

  }

};
