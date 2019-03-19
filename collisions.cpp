#include "collisions.hpp"
#include<vector>
#include<math.h>
using namespace std;

// vector<float> vector_convert(vector<int> a)
// {
// 	vector<float> b(2,0);
// 	b[0]=(float) a[0];
// 	b[1]=(float) a[1];
// 	return b;
// }
//

vector<int> vector_add(vector<int> a, vector<int> b)
{
        vector<int> c(2,0);
        c[0]=a[0]+b[0];
        c[1]=a[1]+b[1];
        return c;
}

vector<int> vector_sub(vector<int> a, vector<int> b)
{
        vector<int> c(2,0);
        c[0]=a[0]-b[0];
        c[1]=a[1]-b[1];
        return c;
}

// vector<int> vector_scalar_mult(vector<int> a, int b)
// {
//         vector<int> c(2,0);
//         c[0]=a[0]*b;
//         c[1]=a[1]*b;
//         return c;
// }

// double vector_magnitude(vector<int> a)
// {
//         return sqrt(a[0]*a[0]+a[1]*a[1]);
// }

bool rectangle_intersection(vector<int> pos1, vector<int> pos2, int length1, int length2, int width1, int width2)
{
	for(int i=0; i<length1; i++)
	{
		for(int j=0; j<width1; j++)
		{
			if(((pos1[0]-j) <= pos2[0]) && ((pos1[0]-j) > pos2[0]-width2) && ((pos1[1]-i) <= pos2[1]) && ((pos1[1]-i) > pos2[1]-length2))
			{
				return true;
			}
		}
	}

	return false;
}

bool rectangle_rectangle_collision_main(Vehicle *a, vector<vector<char>>)
{
	vector<int> a_velocity=a->get_velocity();

	vector<int> a_pos=a->get_pos();

	int a_length=a->get_length();

	int a_width=a->get_width();

	// vector<int> a_acc_add{(int) (a->get_acceleration()/2),0};
	// vector<int> b_acc_add{(int) (b->get_acceleration()/2),0};

	vector<int> a_new_pos=vector_add(a_pos,a_velocity);

	return is_intersection || (clause);
}
