#include "tile.hpp"
using namespace std;


  tile::tile()
  {
    display=' ';
  }

  //To set the vehicle when pixel gets occupied
        void tile::set_v(Vehicle *vehicle)
        {
                v = vehicle;
                if (( v ) && (is_signal==false)) // if v is not null and it is not a signal line.
                {
                        display = v->get_display_char();
                }
        }

        void tile::set_signal()
        {
                is_signal=true;
                display='|';
        }
