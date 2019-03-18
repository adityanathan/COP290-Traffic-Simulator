#include "interaction.hpp"
using namespace std;

void collision_resolution(int i, int j, vector<Vehicle *> vh)
{
	Vehicle *a = vh[i];
	Vehicle *b = vh[j];
	bool pointers_shifted=false;
	if(a->get_pos()[0] > b->get_pos()[0])
        {
                Vehicle *c;
                c=a;
                a=b;
                b=c;
		pointers_shifted=true;
        }
	//Code written with the assumption that b is ahead of a.
	bool lane_change_done=false;
	if(a->get_acceleration()>=0 || a->get_acceleration()<0)
	{
		if(a->can_go_right())
		{
			Vehicle a_copy = *a;
			bool is_possible=true;

			a_copy.set_velocity(a_copy.get_velocity()[0],-1);

			for(int i=0;i<vh.size();i++)
			{
				if(rectangle_rectangle_collision_main(&a_copy,vh[i]));
				{
					is_possible=false;
					break;
				}
			}

			if(is_possible)
			{
				a->set_velocity(a->get_velocity()[0],-1);
				lane_change_done=true;
			}
		}
		else if(a->can_go_left())
		{
			Vehicle a_copy = *a;
			bool is_possible=true;

			a_copy.set_velocity(a_copy.get_velocity()[0],1);

			for(int i=0;i<vh.size();i++)
			{
				if(rectangle_rectangle_collision_main(&a_copy,vh[i]));
				{
					is_possible=false;
					break;
				}
			}

			if(is_possible)
			{
				a->set_velocity(a->get_velocity()[0],1);
				lane_change_done=true;
			}
		}
	}

	if(!lane_change_done)
	{
		lane_change_done=false;

		if(a->can_go_right())
		{
			Vehicle a_copy = *a;
			a_copy.set_acceleration(b->get_acceleration());
			bool is_possible=true;

			a_copy.set_velocity(a_copy.get_velocity()[0],-1);

			for(int i=0;i<vh.size();i++)
			{
				if(rectangle_rectangle_collision_main(&a_copy,vh[i]));
				{
					is_possible=false;
					break;
				}
			}

			if(is_possible)
			{
				a->set_velocity(a->get_velocity()[0],-1);
				lane_change_done=true;
			}
		}
		else if(a->can_go_left())
		{
			Vehicle a_copy = *a;
			a_copy.set_acceleration(b->get_acceleration());
			bool is_possible=true;

			a_copy.set_velocity(a_copy.get_velocity()[0],1);

			for(int i=0;i<vh.size();i++)
			{
				if(rectangle_rectangle_collision_main(&a_copy,vh[i]));
				{
					is_possible=false;
					break;
				}
			}

			if(is_possible)
			{
				a->set_velocity(a->get_velocity()[0],1);
				lane_change_done=true;
			}
		}
	}

	if(!lane_change_done)
	{
		a->set_pos(b->get_pos()[0] - b->get_width(), a->get_pos()[1]);
		a->set_velocity(b->get_velocity());
		if(b->get_acceleration()>0)
		{
			a->set_acceleration(b->get_acceleration());
		}
		else
		{
			a->set_acceleration(0);
		}
	}
}

void interaction_update(Road* road, vector<Vehicle *> a)
{
	vector<Vehicle *> ans;
	vector<bool> sig_collision_truth(a.size(),false);

        if (road->get_signal_color()==0)
        {
		vector<int> temp(2,0);
		temp[0]=road->get_sig_distance();
                temp[1]=road->get_length()-1;
		Vehicle signal(road, road->get_length(), 1, "red", 0, 0, '|', -1, temp);
		for(int i=0;i<a.size();i++)
		{
			int velx = (a[i]->get_velocity()[0]);
			int ax = floor(a[i]->get_acceleration()/2);
			bool clause = (a[i]->get_pos()[0] < road->get_sig_distance()) && (a[i]->get_pos()[0]+velx+ax >=road->get_sig_distance());
			// if(rectangle_rectangle_collision_main(&signal,a[i]) || clause )
			if(clause)
			{
				sig_collision_truth[i]=true;
				a[i]->set_pos(road->get_sig_distance()-1, a[i]->get_pos()[1]);
				a[i]->set_velocity(0,0);
				a[i]->set_acceleration(0);

			}
		}
	}

	vector<bool> is_collision(a.size(),false);
        for(int i=0;i<a.size();i++)
        {

                is_collision[i]=false;
                for(int j=0;j<a.size();j++)
                {
			if(a[i]->get_pos()[0]<=a[j]->get_pos()[0] && i!=j)
			if(rectangle_rectangle_collision_main(a[i],a[j]))
			{
	                        {
	                                collision_resolution(i,j,a);
	                                is_collision[i]=true;
	                        }
			}
                }
        }

	// for(int i=0; i<a.size(); i++)
	// {
	// 	int acc = a[i]->get_acceleration();
	// 	bool check_collision_again=false;
	// 	if(!is_collision[i] && !sig_collision_truth[i])
	// 	{
	// 		// if (!(road->get_signal_color()==0 && (a[i]->get_pos()[0] + 1)==road->get_sig_distance()
	// 			a[i]->set_acceleration(acc+1);
	// 			for(int j=0; j<a.size(); j++)
	// 			{
	// 				if(i!=j && rectangle_rectangle_collision_main(a[i],a[j]))
	// 				{
	// 		                        {
	// 		                                check_collision_again=true;
	// 		                        }
	// 				}
	// 			}
	// 			if(check_collision_again)
	// 			{
	// 				a[i]->set_acceleration(acc);
	// 			}
	// 	}
	// }

        for(int i=0; i<a.size(); i++)
        {
                a[i]->update();
        }
	road->update(a);
}
