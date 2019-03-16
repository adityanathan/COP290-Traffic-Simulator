
#include <vector>
using namespace std;

class Collisions
{
public:
        static void rrStraightCollisions (Vehicle *obj1, Vehicle *obj2)
        {
                int t1 = rrVertexCollisionStraight(Vehicle *obj1, Vehicle *obj2);
                int t2 = rrVertexCollisionStraight(Vehicle *obj2, Vehicle *obj1);

        }

        static vector<int> line_line_intersection(vector<int> a, vector<int> b, vector<int> c, vector<int> d)
        {
                vector<int> a(2,0);

                int tc1 = b[0]-a[0];
                int tc2 = b[1]-a[1];
                int sc1 = c[0]-d[0];
                int sc2 = c[1]-d[1];
                int con1 = c[0]-a[0];
                int con2 = c[1]-a[1];

                int det = tc2*sc1 - tc1*sc2;

                if (det==0)
                {
                        return a
                }

                int s = (tc2*con1 - tc1*con2)/det;

                if (s<0 || s>1)
                {
                        return a;
                }

                int t;
                if (tc1!=0)
                {
                        t = (con1-s*sc1)/tc1;
                }
                else
                {
                        t = (con2-s*sc2)/tc2;
                }

                if (t<0 || t>1)
                {
                        return a;
                }

                a[0]=t;
                a[1]=1;
                return a;
        }
};
