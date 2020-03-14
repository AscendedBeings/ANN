#include "Neural_network.h"
#include <string>
#include <fstream>


vector<string> Input;
vector<string> Target;

vector<vector<double>> Input_D;
vector<vector<double>> Target_D;

void readfile(string input_file, string target_file)
{
	string temp;
	ifstream input_data(input_file);
	ifstream target_data(target_file);
	while (input_data >> temp)
	{
		Input.push_back(temp);
	}
	input_data.close();
	while (target_data >> temp)
	{
		Target.push_back(temp);
	}
	target_data.close();
}

void main()
{
	int s[2] = { 2,1 };
	Neural_network test(2, s);
	string input_file_name;
	string target_file_name;
	int input_size = 1;
	int target_size = 1;
	double *input_data;
	double *target_data;
	input_file_name = "input.txt";
	target_file_name = "target.txt";
	readfile(input_file_name,target_file_name);
	string temp = Input[0];
	while (true)
	{
		int signal = string::npos;
		signal = temp.find_first_of(",");
		if (signal == string::npos)
		{
			break;
		}
		else
		{
			input_size++;
			temp = temp.substr(signal + 1, temp.size());
			signal = string::npos;
		}
		
	}
	temp = Target[0];
	while (true)
	{
		int signal = string::npos;
		signal = temp.find_first_of(",");
		if (signal == string::npos)
		{
			break;
		}
		else
		{
			input_size++;
			temp = temp.substr(signal, temp.size());
			signal = string::npos;
		}

	}

	input_data = new double[input_size];
	target_data = new double[target_size];
	for (int i = 0; i < Input.size(); i++)
	{
		temp = Input[i];
		int save_singal = 0;
		while (true)
		{
			int signal = string::npos;
			signal = temp.find_first_of(",");
			if (signal == string::npos)
			{
				input_data[save_singal] = stod(temp);
				break;
			}
			else
			{
				string deal = temp.substr(0, signal);
				input_data[save_singal] = stod(deal);
				temp = temp.substr(signal + 1, temp.size());
				save_singal++;
			}		
		}
		temp = Target[i];
		save_singal = 0;
		while (true)
		{
			int signal = string::npos;
			signal = temp.find_first_of(",");
			if (signal == string::npos)
			{
				target_data[save_singal] = stod(temp);
				break;
			}
			else
			{
				string deal = temp.substr(0, signal);
				target_data[save_singal] = stod(deal);
				temp = temp.substr(signal + 1, temp.size());
				save_singal++;
			}
		}
		test.Push_training_data(input_size, input_data, target_size, target_data);
	}

	test.Set_training_parameter(0.001, 0.0001);
	test.Training(false,1000);

	system("pause");
}