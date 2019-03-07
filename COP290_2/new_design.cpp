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
  bool is_signal=false;
public:
  pixel()
  {
    this->display=" ";
  }

  //To set the vehicle when pixel gets occupied
  void set_v(Vehicle *vehicle)
  {
    this->v = vehicle;   //Is this the correct way to assign the pointer
    if ( v ) && (is_signal==false) // if v is not null
    {
        this->display = *v.display;
    }
    else
    {
        this->display = " ";
    }
  }
  void set_signal()
  {
      this->is_signal=true;
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
  int signal_distance;
  vector<vector<pixel>> road_map; //Changes made.

public:
  //Constructor
  Road(int l, int w, int s, int sig_distance)
  {
    this->road_length = l;
    this->road_width = w;
    this->road_map.resize(w, vector<pixel>(l, pixel())); //Changes made.
    this->signal = s;
    this->signal_distance=sig_distance;

    for(int i=0; i < w; i++)
    {
        road_map[sig_distance][i].is_signal=true;
    }
  }

  void next_second()
  {
    for (int i = road_length-1; i>=0; i--)
    {
      vector<Vehicle> considered_v;
      for (int j = 0; j<road_width; j++)
      {
        if (this->road_map[j][i].display!=" " && this->road_map[j][i].is_signal==false)
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
        if (move_front(v->upper_right, v->width)==1)
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
      pixel temp = road_map[get<0>(upper_right)+j][get<1>(upper_right)+1];
      if (temp.v) || (temp.is_signal) //Changes made.
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
    //tuple<int,int> down_right = make_tuple(get<0>(upper_right)+length-1,get<1>(upper_right));
    int a = get<0>(upper_right);
    int b = get<1>(upper_right);
    bool right = false;
    bool left = false;
    int s=0;


    for (int j = 0; j < width; j++)
    {
      if !(road_map[a+1+j][b+1].v) && !(road_map[a+1+j][b+1].is_signal)
      {
        s=s+1;
      }
    }
    if (s==width)
    {
        s=0;
      for (int i=0; i<length; i++)
      {
        if !(road_map[a+width][b+1-i].v) && !(road_map[a+width][b+1-i].is_signal)
        {
          s=s+1;
        }
      }
      if (s==length)
      {
        right = true;
      }
    }

    if(right == false)
    {
        s=0;
        for (int j = 0; j<width; j++)
        {
          if !(road_map[a-1+j][b+1].v) && !(road_map[a-1+j][b+1].is_signal)
          {
            s=s+1;
          }
        }

        if(s==width)
        {
          s=0;
          for (int i=0; i<length; i++)
          {
            if !(road_map[a-1][b+1-i].v) && !(road_map[a-1][b+1-i].is_signal)
            {
              s=s+1;
            }
          }
          if(s==length)
          {
              left=true;
          }
        }

        if (left=true)
        {
            return 2;
        }
        else if(right=true)
        {
            return 1;
        }
        else
        {
            return 0;
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
      for(int i=0; i<road_width; i++)
      {
          cout<<"-";
      }
      cout<<endl;
      for(i=0; i<road_width; i++)
      {
          for(int j=0; j<road_length; j++)
          {
              cout<<road_map[i][j].display;
          }
          cout<<endl;
      }
      for(int i=0; i<road_width; i++)
      {
          cout<<"-";
      }
      cout<<endl;
  }

};
