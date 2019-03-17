#ifndef tile_h
#define tile_h
#include "vehicle.hpp"
using namespace std;

class tile
{
public:
  char display;
  Vehicle *v = NULL;
  bool is_signal=false;
public:
  tile()

  //To set the vehicle when pixel gets occupied
        void set_v(Vehicle *vehicle)

        void set_signal()
};

#endif
