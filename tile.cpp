#include "tile.hpp"
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
  {
    this->display=" ";
  }

  //To set the vehicle when pixel gets occupied
        void set_v(Vehicle *vehicle)
        {
                this->v = vehicle;
                if ( v ) && (is_signal==false) // if v is not null and it is not a signal line.
                {
                        this->display = *v.display;
                }
        }

        void set_signal()
        {
                this->is_signal=true;
                display
        }
};
