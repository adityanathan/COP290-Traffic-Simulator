#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "interaction.hpp"
#include <algorithm>
#include "/home/aditya/rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

int vehicle_counter;
void parser(string config)
{
	vector < vector < string> > ans;
	cout << "Start" << endl;
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile (config);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("road");

	int width = stoi(root_node->first_attribute("length")->value());
	int length = stoi(root_node->first_attribute("width")->value());
	int dist = stoi(root_node->first_attribute("sig_dist")->value());

	Road r = Road(length,width,dist);

    //sees the initial colour for the signal;
	string initial_color = ((root_node->first_node("signals"))->first_attribute("initial_color")->value());
	int t_signal; //0 for red, 1 for green

	if (initial_color.compare("green")==0)
	{
		t_signal = 1;
	}
	else
	{
		t_signal = 0;
	}

	r.set_sig_colour(t_signal);

    //to make a vector which stores the time after which you need to change the signal, taken care of last signal not being red
    vector<int> sig_time;
    xml_node<> * signals_node = root_node->first_node("signals");
    for (xml_node<> * signal_node = signals_node->first_node("signal"); signal_node; signal_node = signal_node->next_sibling())
    {
        sig_time.push_back(stoi(signal_node->first_attribute("time")->value()));
    }
    if ((sig_time.size() % 2 == 0 and t_signal == 1) or (sig_time.size() % 2 == 1 and t_signal == 0))
    {
        sig_time.push_back(1);
    }

    vector<int> pos(2,-1);

    //to make a vector of vehicles to be sent on road
    vector<Vehicle > sig_vehicles;
    xml_node<> * vehicles_node = root_node->first_node("Vehicles");
    for (xml_node<> * vehicle_node = vehicles_node->first_node("vehicle"); vehicle_node; vehicle_node = vehicle_node->next_sibling())
    {
        int wid = stoi(vehicle_node->first_node("length")->value());
        int len = stoi(vehicle_node->first_node("width")->value());
	int height = stoi(vehicle_node->first_node("height")->value());
        string col = vehicle_node->first_node("color")->value();
        int max_v = stoi(vehicle_node->first_node("max_v")->value());
        int acc = stoi(vehicle_node->first_node("acc")->value());
        char disp = vehicle_node->first_node("display")->value()[0];
        int id = sig_vehicles.size();

        Vehicle v(&r, len, wid, col, max_v, acc, disp, id, pos);
        sig_vehicles.push_back(v);
    }
	vector<Vehicle *>vehicles;
	for(int i=0;i<sig_vehicles.size();i++)
	{
	    vehicles.push_back(&sig_vehicles[i]);
	}
//////////My code
	bool road_empty=false;
	int time_step=0;
	int sig_time_counter=0;
	vehicle_counter=vehicles.size()-1;
	while(!road_empty)
	{
		road_empty=true;
		vector<Vehicle *> a = interaction_update(&r,vehicles,sig_time);
		r.display();
		for(int i=0;i<r.get_width();i++)
		{
			for(int j=0;j<r.get_length();j++)
			{
				if((r.road_map)[i][j]!=' ' && (r.road_map)[i][j]!='|')
				{
					road_empty=false;
					break;
				}
			}
		}
		time_step++;
		cout<<"Time step = "<<time_step<<endl<<endl;
		if(time_step==sig_time[sig_time_counter] && sig_time_counter<sig_time.size())
		{
			r.set_sig_colour(1-r.get_signal_color());
			sig_time_counter++;
		}
	}
}

int main(int argc, char *argv[])
{
	parser("XML_config.xml");
}

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

vector<Vehicle *> interaction_update(Road *r, vector<Vehicle *> a, vector<int> sig_time)
{
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
	r->update(a);
	return a;
}
