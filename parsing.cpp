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
    
    vector<int> pos(2,0);
    
    //to make a vector of vehicles to be sent on road
    vector<Vehicle > sig_vehicles;
    xml_node<> * vehicles_node = root_node->first_node("Vehicles");
    for (xml_node<> * vehicle_node = vehicles_node->first_node("vehicle"); vehicle_node; vehicle_node = vehicle_node->next_sibling())
    {
        int wid = stoi(vehicle_node->first_node("length")->value());
        int len = stoi(vehicle_node->first_node("width")->value());
        string col = vehicle_node->first_node("color")->value();
        int max_v = stoi(vehicle_node->first_node("max_v")->value());
        int acc = stoi(vehicle_node->first_node("acc")->value());
        char disp = vehicle_node->first_node("display")->value()[0];
        int id = sig_vehicles.size();
        
        Vehicle v(&r, len, wid, col, max_v, acc, disp, id, pos);
        sig_vehicles.push_back(v);
    }
    cout<<sig_time.size()<<endl;
    cout<<sig_vehicles.size()<<endl;
    
    
    
    //every vehicle in sig_vehicles has initial position (0,0)
    //find sig_vehicles and sig_time
    
    
                    // Quite reading of xml file
//    vector<int> pos(2,0);
//
//    vector<int> sig_time;
//    vector<vector <Vehicle> > sig_vehicles;
//
//    for (xml_node<> * signal_node = root_node->first_node("signal"); signal_node; signal_node = signal_node->next_sibling())
//    {
////        if (stoi(signal_node->first_attribute("end")->value())==-1)
////        {
////            sig_time.push_back(15);
////        }
////        else
////        {
//            sig_time.push_back(stoi(signal_node->first_attribute("end")->value()));
////        }
//        vector<Vehicle> sig_v;
//
//        for(xml_node<> * vehicle_node = signal_node->first_node("vehicle"); vehicle_node; vehicle_node = vehicle_node->next_sibling())
//        {
//                int wid = stoi(vehicle_node->first_node("length")->value());
//                int len = stoi(vehicle_node->first_node("width")->value());
//                string col = vehicle_node->first_node("color")->value();
//                int max_v = stoi(vehicle_node->first_node("max_v")->value());
//                int acc = stoi(vehicle_node->first_node("acc")->value());
//                char disp = vehicle_node->first_node("display")->value()[0];
//                int id = sig_vehicles.size();
//
//                Vehicle v(&r, len, wid, col, max_v, acc, disp, id, pos);
//                sig_v.push_back(v);
//        }
//            sig_vehicles.push_back(sig_v);
//    }
//
//    for (int i = 0; i< sig_vehicles.size(); i++)
//    {
//        random_shuffle(sig_vehicles[i].begin(),sig_vehicles[i].end());
//    }

    
//It was placement of vehicles on road
//    int next_x = 0;
//    int next_y = length - 1;
//    int max_length = 0;
    
//    for (int i=0; i<sig_vehicles.size(); i++)
//    {
//        for (int j = 0; j < sig_vehicles[i].size(); j++)
//        {
//
//            if (next_y - sig_vehicles[i][j].get_length() < 0)
//            {
//                if (i%2 == 0)
//                {
//                    next_y = length -2;
//                }
//                else
//                {
//                    next_y = length - 1;
//                }
//
//                next_x = next_x -max_length-1;
//                max_length = sig_vehicles[i][j].get_width();
//                sig_vehicles[i][j].set_pos(next_x, next_y);
//                next_y = next_y - sig_vehicles[i][j].get_length() - 1;
//            }
//            else
//            {
//                sig_vehicles[i][j].set_pos(next_x, next_y);
//                next_y = next_y - sig_vehicles[i][j].get_length() - 1;
//                if (sig_vehicles[i][j].get_width() > max_length)
//                {
//                    max_length = sig_vehicles[i][j].get_width();
//                }
//            }
//
//        }
//    }
            // to send the vehicles on road
//    vector<Vehicle *> on_road;
//    for (int i = 0; i < sig_vehicles.size(); i++)
//    {
//        for (int j = 0; j< sig_vehicles[i].size(); j++)
//        {
//            on_road.push_back(&sig_vehicles[i][j]);
//        }
//        r.update(on_road);
//        int iter = 0;
//
//        //To end the program if end time is -1
//        if (sig_time[i]==-1)
//        {
//            bool road_empty = false;
//            while (road_empty == false)
//            {
//                interaction_update(&r, on_road);
//                road_empty = true;
//                for (int m = 0; m < r.road_map.size(); m++)
//                {
//                    for (int n = 0; n < r.road_map[0].size(); n++)
//                    {
//                        if ((r.road_map[m][n]) != ' ')
//                        {
//                            road_empty = false;
//                        }
//                    }
//                }
//            }
//        }
//        else
//        {
//            for (int k = 0; k< sig_time[i]; k++)
//            {
//                //r.update(&on_road);
//                interaction_update(&r, on_road);
//            }
//        }
<<<<<<< HEAD
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

			if (next_y - sig_vehicles[i][j].get_length() < 0)
			{
                if (i%2 == 0)
                {
                    next_y = length -2;
                }
                else
                {
                    next_y = length - 1;
                }

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
		r.update(on_road);
        int iter = 0;

        //To end the program if end time is -1
        if (sig_time[i]==-1)
        {
            bool road_empty = false;
            while (road_empty == false)
            {
                // interaction_update(&r, on_road, 20);
                road_empty = true;
                for (int m = 0; m < r.road_map.size(); m++)
                {
                    for (int n = 0; n < r.road_map[0].size(); n++)
                    {
                        if ((r.road_map[m][n]) != ' ')
                        {
                            road_empty = false;
                        }
                    }
                }
            }
        }
        else
        {
            // for (int k = 0; k< sig_time[i]; k++)
            // {
            //     //r.update(&on_road);
            //     interaction_update(&r, on_road);
            // }
	    // interaction_update(&r, on_road, 20);
        }
        if (sig_time[i+1] == -1)
        {
            t_signal = 1;
        }
        else
        {
            t_signal = 1 - t_signal;
        }
		r.set_sig_colour(t_signal);
	}
	interaction_update(&r, on_road, 20);
=======
//        if (sig_time[i+1] == -1)
//        {
//            t_signal = 1;
//        }
//        else
//        {
//            t_signal = 1 - t_signal;
//        }
//        r.set_sig_colour(t_signal);
//    }

>>>>>>> 08f9007ed879222668a18669f698817dfd73dbce
}

int main(int argc, char *argv[])
{
	parser("XML_config.xml");
}
