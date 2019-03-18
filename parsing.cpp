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


	string initial_color = ((root_node->first_node("signal"))->first_attribute("color")->value());
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

	vector<int> pos(2,0);

	vector<int> sig_time;
	vector<vector <Vehicle> > sig_vehicles;

	for (xml_node<> * signal_node = root_node->first_node("signal"); signal_node; signal_node = signal_node->next_sibling())
	{
		if (stoi(signal_node->first_attribute("end")->value())==-1)
		{
			sig_time.push_back(15);
		}
		else
		{
			sig_time.push_back(stoi(signal_node->first_attribute("end")->value()));
		}
		vector<Vehicle> sig_v;

	    for(xml_node<> * vehicle_node = signal_node->first_node("vehicle"); vehicle_node; vehicle_node = vehicle_node->next_sibling())
	    {
				int wid = stoi(vehicle_node->first_node("length")->value());
				int len = stoi(vehicle_node->first_node("width")->value());
				string col = vehicle_node->first_node("color")->value();
				int max_v = stoi(vehicle_node->first_node("max_v")->value());
				int acc = stoi(vehicle_node->first_node("acc")->value());
				char disp = vehicle_node->first_node("display")->value()[0];
				int id = sig_vehicles.size();

				Vehicle v(&r, len, wid, col, max_v, acc, disp, id, pos);
				sig_v.push_back(v);
	    }
			sig_vehicles.push_back(sig_v);
	}

	for (int i = 0; i< sig_vehicles.size(); i++)
	{
		random_shuffle(sig_vehicles[i].begin(),sig_vehicles[i].end());
	}



	int next_x = 0;
	int next_y = length - 1;
	int max_length = 0;
	for (int i=0; i<sig_vehicles.size(); i++)
	{
		for (int j = 0; j < sig_vehicles[i].size(); j++)
		{

			if (next_y - sig_vehicles[i][j].get_length() <=0)
			{
				next_y = length - 1;
				next_x = next_x -max_length-1;
				max_length = sig_vehicles[i][j].get_width();
				sig_vehicles[i][j].set_pos(next_x, next_y);
				next_y = next_y - sig_vehicles[i][j].get_length() - 1;
			}
			else
			{
				sig_vehicles[i][j].set_pos(next_x, next_y);
				next_y = next_y - sig_vehicles[i][j].get_length() - 1;
				if (sig_vehicles[i][j].get_width() > max_length)
				{
					max_length = sig_vehicles[i][j].get_width();
				}
			}

		}
	}

	vector<Vehicle *> on_road;
	for (int i = 0; i < sig_vehicles.size(); i++)
	{
		for (int j = 0; j< sig_vehicles[i].size(); j++)
		{
			on_road.push_back(&sig_vehicles[i][j]);
		}
		for (int k = 0; k< sig_time[i]; k++)
		{
			//r.update(&on_road);
			interaction_update(&r, on_road);
		}
		t_signal = 1 - t_signal;
		r.set_sig_colour(t_signal);
	}

}

int main(int argc, char *argv[])
{
	parser("XML_config.xml");
}
