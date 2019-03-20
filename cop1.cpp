#include "interaction.hpp"
using namespace std;

vector<int> check_movable_zone(Vehicle a,vector<vector<char>> rd)
{
	int x_pos=a.get_pos()[0];
	int y_pos=a.get_pos()[1];
	int length=a.get_length();
	int width=a.get_width();
	int x_velocity=a.get_velocity()[0];
	int rd_width=rd[0].size()-1;

	int x_new_pos=x_pos+x_velocity;
	int y_new_pos=y_pos;
	int lane_change=5; //0 not possible, decelerate. -1 right. 1 left. 5 move_forward. 4 signal_stop.
	bool is_signal=false;
	int m;
	// for(int i=x_new_pos; i>x_new_pos - width; i--)
	// cout << x_pos << " " << x_new_pos << endl;
	for(int i=x_pos+1; i<=x_new_pos; i++)

	{
		// for(int j=y_new_pos; j>y_new_pos - length; j--)
		for(int j=y_pos; j>y_pos-length; j--)

		{
			if(i<rd.size() && i>=0 && j<rd[0].size() && j>=0)
			{
				if(rd[i][rd_width-j]!=' ')
				{
					m=i-1;
					lane_change=0;
					if(rd[i][rd_width-j]=='|')
					{
						is_signal=true;
						break;
					}
				}
			}
		}
	}

	if(lane_change==5)
	{
		vector<int> a{0,5};
		return a;
	}
	if(lane_change==0)
	{
		if(is_signal)
		{
			vector<int> a{m,4};
			return a;
		}
	}

	x_new_pos=m;
	bool move_right=true;
	if(y_pos-length>=0)//can move right
	{
		for(int i=x_pos-width+1;i<=x_new_pos;i++)
		{
			for(int j=y_pos;j>=y_pos-length;j--)
			{
				if(i<rd.size() && i>=0)
				{
					if(!((i >= x_pos-width+1) && (i<=x_pos) && (rd_width-j<=y_pos) && (rd_width-j>y_pos-length+1)))
					{
						if(rd[i][rd_width-j]!=' ')
						{
							move_right=false;
						}
					}
				}
			}
		}
	}
	else
	{
		move_right=false;
	}

	if(move_right)
	{
		vector<int> a{m,-1};
		return a;
	}
	else
	{
		bool move_left=true;
		if(y_pos+1<rd[0].size())
		{
			for(int i=x_pos-width+1;i<=x_new_pos;i++)
			{
				for(int j=y_pos-length+1;j<=y_pos+1;j++)
				{
					if(i<rd.size() && i>=0)
					{
						if(!((i >= x_pos-width+1) && (i<=x_pos) && (rd_width-j<=y_pos) && (rd_width-j>y_pos-length+1)))
						{
							if(rd[i][rd_width-j]!=' ')
							{
								move_left=false;
							}
						}
					}
				}
			}
		}
		else
		{
			move_left=false;
		}
		if(move_left)
		{
			vector<int> a{m,1};
			return a;
		}
		else
		{
			vector<int> a{m,0};
			return a;
		}
	}

}

void interaction_update(Road *r, vector<Vehicle *> a, vector<int> sig_time)
{

	//////To be removed after poorva alters code.
	for(int i=0; i<a.size();i++)
	{
		a[i]->set_pos(-1,-1);
	}
	r->update(a);

	//////
	int max_no_vehicles=0;
	int max_width=0;
	srand(time(0));
	for(int i=0; i<a.size(); i++)
	{
		if(max_width<a[i]->get_length())
		{
			max_width=a[i]->get_length();
		}
	}
	max_no_vehicles=r->get_length()/max_width;

	bool road_empty=false;
	int vehicle_counter=a.size()-1;
	int time_step=0;
	int sig_time_counter=0;
	while(!road_empty)
	{
		int road_length=r->get_length();
		int road_width=r->get_width();
		vector<vector<char>> *road_map = &r->road_map;
		bool is_start_line_empty=true;
		for(int i=0;i<road_length;i++)
		{
			if((*road_map)[0][i]!=' ')
			{
				is_start_line_empty=false;
				break;
			}
		}
		if(is_start_line_empty && vehicle_counter>=0)
		{
			int start_point=r->get_length()-1;
			while(vehicle_counter>=0)
			{
				a[vehicle_counter]->set_pos(0,start_point);
				if(start_point-a[vehicle_counter]->get_length()+1<0)
				{
					a[vehicle_counter]->set_pos(-1,-1);
					break;
				}

				start_point=start_point - a[vehicle_counter]->get_length() - (3-(rand()%3));
				vehicle_counter--;
			}
		}
		r->update(a);
		vector<Vehicle> list;
		for(int i=0; i<a.size(); i++)
		{
			list.push_back(*a[i]);
		}
		for(int i=0;i<a.size();i++)
		{
			if(a[i]->get_pos()[1]!=-1)
			{
				// Vehicle cur=*a[i];
				Vehicle cur = list[i];
				int signal_distance=r->get_sig_distance();
				int max=0;
				int x = cur.get_pos()[0];
				if(x<signal_distance/3 && r->get_signal_color()==0)
				{
					max=cur.get_max_speed();
				}
				else if(x<2*signal_distance/3 && r->get_signal_color()==0)
				{
					max=cur.get_max_speed()/2;
				}
				else if(x<signal_distance && r->get_signal_color()==0)
				{
					max=cur.get_max_speed()/3;
				}
				else if(r->get_signal_color()==1)
				{
					max=cur.get_max_speed();
				}
				if(max==0)
				{
					max=1;
				}
				if(cur.get_acceleration() >= max)
		                {
		                        cur.set_acceleration(0);
					cur.set_velocity(max,0);
		                }
				else
				{
					int temp_ax = cur.get_acceleration()+1;
					int temp_vx = temp_ax+cur.get_velocity()[0];
					if(temp_vx>max)
					{
						temp_vx=max;
						temp_ax=0;
					}
					cur.set_acceleration(temp_ax);
					cur.set_velocity(temp_vx,0);
				}

				vector<int> option = check_movable_zone(cur, *road_map);
				// cout<<option[0]<<" "<<option[1]<<" "<<(char)cur.get_display_char()<<" "<<cur.get_velocity()[0]<<" "<<cur.get_pos()[0]<<" "<<cur.get_pos()[1]<<endl;
				if(option[1] == 5)
				{
					a[i]->set_velocity(cur.get_velocity());
					a[i]->set_acceleration(cur.get_acceleration());
					int px = cur.get_pos()[0]+cur.get_velocity()[0];
					int py = cur.get_pos()[1];
					a[i]->set_pos(px,py);
					// r->update(a);
				}
				else if(option[1] == 4)
				{
					a[i]->set_velocity(0,0);
					a[i]->set_acceleration(0);
					int px = option[0];
					int py = cur.get_pos()[1];
					a[i]->set_pos(px,py);
					// r->update(a);
				}
				else if (option[1] == 0)
				{
					a[i]->set_velocity(cur.get_velocity());
					a[i]->set_acceleration(0);
					int px = option[0];
					int py = cur.get_pos()[1];
					a[i]->set_pos(px,py);
				}
				else if(option[1] == -1 || option[1] == 1)
				{
					a[i]->set_velocity(cur.get_velocity());
					a[i]->set_acceleration(cur.get_acceleration());
					int px = option[0];
					int py = cur.get_pos()[1]+option[1];
					a[i]->set_pos(px,py);
					// r->update(a);
				}
			}
		}

		// for(int i=0; i<a.size();i++)
		// {
		// 	a[i]->set_acceleration(list[i].get_acceleration());
		// 	a[i]->set_velocity(list[i].get_velocity());
		// 	a[i]->set_pos(list[i].get_pos()[0],list[i].get_pos()[1]);
		// }
		r->update(a);
		r->display();
		cout<<endl;
		time_step++;
		cout<<"Time step = "<<time_step<<endl<<endl;
		if(time_step==sig_time[sig_time_counter] && sig_time_counter<sig_time.size())
		{
			r->set_sig_colour(1-r->get_signal_color());
			sig_time_counter++;
		}
		road_empty=true;
		for(int i=0;i<road_width;i++)
		{
			for(int j=0;j<road_length;j++)
			{
				if((*road_map)[i][j]!=' ' && (*road_map)[i][j]!='|')
				{
					road_empty=false;
					break;
				}
			}
		}
	}
}
