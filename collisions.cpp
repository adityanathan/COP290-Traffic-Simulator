
#include <vector>
using namespace std;

class Collisions
{
public:
        static vector<int> vector_add(vector<int> a, vector<int> b)
        {
                vector<int> c(2,0);
                c[0]=a[0]+b[0];
                c[1]=a[1]+b[1];
                return c;
        }

        static vector<int> vector_sub(vector<int> a, vector<int> b)
        {
                vector<int> c(2,0);
                c[0]=a[0]-b[0];
                c[1]=a[1]-b[1];
                return c;
        }

        static vector<int> vector_scalar_mult(vector<int> a, int b)
        {
                vector<int> c(2,0);
                c[0]=a[0]*b;
                c[1]=a[1]*b;
                return c;
        }

        static vector<int> vector_component(vector<int> a, vector<int> direction_vector)
        {
                int mag = (direction_vector[0]*direction_vector[0]) + (direction_vector[1]*direction_vector[1]);
                vector<int> ans(2,0);
                ans[0]=a[0]*direction_vector[0]/mag;
                ans[1]=a[1]*direction_vector[1]/mag;
                return ans;
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

        static vector<int> point_rectangle_intersection(vector<int> pt, vector<int> pt_displacement, Vehicle *vh)
        {
                vector<int> ans(2,0);

                vector<int> pt_displaced = vector_add(pt,pt_displacement);
                vector<int> l; l.push_back(0); l.push_back(-1*(vh->length));
                vector<int> w; w.push_back(-1*(vh->width)); w.push_back(0);
                vector<int> a = vh->pos;
                vector<int> b = vector_add(a,l);
                vector<int> c = vector_add(b,w);
                vector<int> d = vector_add(a,w);
                int t; int s=0;

                vector<int> x = line_line_intersection(pt,pt_displaced,a,b);
                if (x[1]==1)
                {
                        s=1; t=x[0];
                }

                x = line_line_intersection(pt,pt_displaced,b,c);
                if (x[1]==1)
                {
                        s=1; t=min(x[0], t);
                }

                x = line_line_intersection(pt,pt_displaced,c,d);
                if (x[1]==1)
                {
                        s=1; t=min(x[0], t);
                }

                x = line_line_intersection(pt,pt_displaced,a,d);
                if (x[1]==1)
                {
                        s=1; t=min(x[0], t);
                }

                if(s==1)
                {
                        ans[1]=1;
                        ans[0]=t;
                        return ans;
                }

                return ans;
        }

        static vector<vector<int>> points_to_check(vector<int> pos, vector<int> x, vector<int> y, vector<int> displacement)
        {
                vector<vector<int>> ans;
                int c1 = vector_component(displacement, x);
                int c2 = vector_component(displacement, y);
                //x and y are the orthonormal vectors along the basis.
                //I'm splitting displacement into it's rectangular coordinates.

                if (c1>0)
                {
                        ans.push_back(pos);
                        ans.push_back(vector_sub(pos,y));
                }
                else
                {
                        ans.push_back(vector_sub(pos,x));
                        ans.push_back(vector_sub(vector_sub(pos,x),y));
                }

                if(c2>0)
                {
                        if(c1>0)
                        {
                                ans.push_back(vector_sub(pos,x));
                        }
                        else
                        {
                                ans.push_back(pos);
                        }
                }
                else
                {
                        if(c1>0)
                        {
                                ans.push_back(vector_sub(vector_sub(pos,x),y));
                        }
                        else
                        {
                                ans.push_back(vector_sub(pos,y));
                        }
                }

                return ans;
        }

        static vector<int> rectangle_rectangle_vertex_collision (Vehicle *obj1, Vehicle *obj2, int time)
        {
                vector<int> ans(2,0);

                vector<int> relative_velocity_obj1_wrt_obj2 = vector_sub(obj1->velocity,obj2->velocity);
                vector<int> displacement = vector_scalar_mult(relative_velocity_obj1_wrt_obj2, time);

                vector<int> x1; x1.push_back(obj1->length);x1.push_back(0);
                vector<int> y1; y1.push_back(0); y1.push_back(obj1->width);

                vector<vector<int>> vertices = points_to_check(obj1->pos, x1, y1, displacement);

                vector<int> x2; x2.push_back(obj2->length);x2.push_back(0);
                vector<int> y2; y2.push_back(0); y2.push_back(obj2->width);

                int t = INT_MAX; int temp; int flag;

                for(i=0; i<vertices.size(); i++)
                {
                        temp = point_rectangle_intersection(vertices[i],relative_velocity_obj1_wrt_obj2, obj2);
                        if (temp[1]==1)
                        {
                                t=min(t,temp[0]);
                                flag=1;
                        }
                }

                if(flag==1)
                {
                        ans[0]=t;
                        ans[1]=1;
                }

                return ans;
        }

        static vector<int> rectangle_rectangle_collision_main(Vehicle *obj1, Vehicle *obj2, int time)
        {
                vector<int> ans(2,0);
                vector<int> t1 = rectangle_rectangle_vertex_collision(obj1, obj2, time);
                vector<int> t2 = rectangle_rectangle_vertex_collision(obj2, obj1, time);

                if(t1[1]==0 && t2[1]==0)
                {
                        return ans;
                }
                else
                {
                        ans[1]=1;
                        if(t1[1]==0)
                        {
                                ans[0]=t2[0];
                        }
                        if(t2[1]==0)
                        {
                                ans[0]=t1[0];
                        }
                        ans[0]=min(t1[0],t2[0]);

                        return ans;
                }
        }
};
