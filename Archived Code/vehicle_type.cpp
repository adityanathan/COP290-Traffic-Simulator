#include "vehicle_type.hpp"
using namespace std;
class Vehicle_Type
{
private:
        int length;
        int width;
        string type;
public:
        Vehicle_Type(int len, int wid, string t)
        {
                length = len;
                width = wid;
                type = t;
        }
        int get_length() {return length;}
        int get_width() {return width;}
        int get_type() {return type;}
};
