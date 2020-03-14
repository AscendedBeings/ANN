#pragma once
#include "Matrix.h"
#include <vector>


enum Active_type
{
	sigmond,
};

class Active_function
{
private:
	
public:
	Active_type type = sigmond;
	void Set_type(const Active_type parameter);
	Matrix Active(const Matrix &parameter);
};

void Active_function::Set_type(const Active_type parameter)
{
	type = parameter;
}

Matrix Active_function::Active(const Matrix &parameter)
{
	Matrix temp;
	temp = parameter;
	switch (type)
	{
	case sigmond:
		for (int i = 0; i < temp.raws; i++)
		{
			for (int j = 0; j < temp.cols; j++)
			{
				temp.element[i][j] = (double)1 / ((double)1 + exp(-parameter.element[i][j]));
			}
		}
		break;
	default:
		break;
	}
	return temp;
}

class Neural_network
{
private:
	int layers_of_network;
	int *each_layer_size;
	double learning_rate = 0.5;
	double error_bound = 0.1;
	double training_error = DBL_MAX;
	vector<Matrix> Layers_node;
	vector<Matrix> Layers_bias;
	vector<Matrix> Weight;
	vector<Matrix> Layers_deviation;

	vector<Matrix> Training_data;
	vector<Matrix> Training_target;
	Active_function AF;

	bool check_error();
	void Set_training_data(int number = 0);
public:
	Neural_network(int layers, int each_layer_size[]);
	
	void Set_training_parameter(double parameter_learning, double parameter_error);
	void Push_training_data(int input_size, double input[], int target_size, double target[]);

	void forward_calculate();
	void back_update();

	void Training(bool auto_analyze = true, int max_loop = 1000);

	void network_display();
	void weight_display();
	void training_data_display();
};

bool Neural_network::check_error()
{
	Matrix error;
	error = Layers_node[layers_of_network] - Layers_node[layers_of_network - 1];
	error = error.multi_element(error);
	training_error = error.distance();
	if (training_error > error_bound)
		return false;
	else
		true;
}

Neural_network::Neural_network(int layers, int each_layer[])
{
	if (each_layer_size != NULL)
	{
		free(each_layer_size);
		each_layer_size = NULL;
	}
	layers_of_network = layers;
	each_layer_size = new int[layers_of_network];
	for (int i = 0; i < layers_of_network; i++)
	{
		each_layer_size[i] = each_layer[i];
	}
	Layers_node.clear();
	Layers_bias.clear();
	Weight.clear();
	Layers_deviation.clear();
	for (int i = 0; i < layers_of_network; i++)
	{
		Matrix temp1(1, each_layer_size[i], 0.1);
		Matrix temp2(1, each_layer_size[i], 0.1);
		Matrix temp3(1, each_layer_size[i], 0.1);
		Layers_node.push_back(temp1);
		Layers_bias.push_back(temp2);
		Layers_deviation.push_back(temp3);
	}
	Matrix target1(1, each_layer_size[layers_of_network - 1], 0.1);
	Matrix target2(1, each_layer_size[layers_of_network - 1], 0.1);
	Matrix target3(1, each_layer_size[layers_of_network - 1], 0.1);
	Layers_node.push_back(target1);
	Layers_bias.push_back(target2);
	Layers_deviation.push_back(target3);
	for (int i = 1; i < layers_of_network; i++)
	{
		Matrix temp(each_layer[i - 1], each_layer[i], 0.2);
		Weight.push_back(temp);
	}
}

void Neural_network::Set_training_data(int number)
{
	Layers_node[0] = Training_data[number];
	Layers_node[layers_of_network] = Training_target[number];
}

void Neural_network::Set_training_parameter(double parameter_learning, double parameter_error)
{
	learning_rate = parameter_learning;
	error_bound = parameter_error;
}

void Neural_network::Push_training_data(int input_size, double input[], int target_size, double target[])
{
	if (input_size != each_layer_size[0])
	{
		cout << "Input data not match ANN." << endl;
	}
	else if (target_size != each_layer_size[layers_of_network - 1])
	{
		cout << "Target data not match ANN." << endl;
	}
	else
	{
		Matrix input_data(1, input_size, 0.1);
		input_data.one_demation_set(input_size, input);
		Training_data.push_back(input_data);
		Matrix target_data(1, target_size, 0.1);
		target_data.one_demation_set(target_size, target);
		Training_target.push_back(target_data);
	}
}

void Neural_network::forward_calculate()
{
	Matrix temp;
	for (int i = 1; i < layers_of_network; i++)
	{
		temp = Layers_node[i - 1] * Weight[i - 1];
		temp = temp + Layers_bias[i];
		switch (AF.type)
		{
		case sigmond:
			temp = AF.Active(temp);
			break;
		default:
			break;
		}
		Layers_node[i] = temp;
	}
}

void Neural_network::back_update()
{
	Matrix Deviation_weight;
	Matrix Deviation_node;
	Layers_deviation[layers_of_network - 1] = Layers_node[layers_of_network] - Layers_node[layers_of_network - 1];
	int weight_signal = Weight.size() - 1;
	for (int i = layers_of_network - 2; i >= 0; i--)
	{
		Deviation_node = Layers_deviation[i + 1] * Weight[weight_signal].Transpose();
		switch (AF.type)
		{
		case sigmond:
			Deviation_node = Deviation_node.multi_element(Layers_node[i].multi_element((1 - Layers_node[i])));
			Deviation_weight = Deviation_node.Transpose()*Layers_node[i + 1];
			Weight[weight_signal] = Weight[weight_signal] - learning_rate * Deviation_weight;
			Layers_bias[i] = Layers_bias[i] - learning_rate * Deviation_node;
			break;
		default:
			break;
		}
		weight_signal--;

		//cout << "deviation:" << endl;
		//Deviation_node.display();
		//Deviation_weight.display();

	}
}

void Neural_network::Training(bool auto_analyze, int max_loop)
{
	int run_times = 1;
	double error = DBL_MAX;
	int current_traing_number = 0;
	int match_times = 0;
	while (run_times < max_loop)
	{
		cout << "The " << run_times << "th training..." << endl;
		Set_training_data(current_traing_number);
		forward_calculate();
		back_update();
		current_traing_number++;
		if (current_traing_number == Training_data.size())
		{
			current_traing_number = 0;
		}
		run_times++;	
		check_error();
		cout << "MSE is: " << training_error << endl;
		if (training_error < error_bound)
		{
			match_times++;
			if (match_times > 15 && auto_analyze == true)
			{
				break;
			}
		}
		weight_display();
	}
}


void Neural_network::network_display()
{
	int begin_index = 0;
	int current_layer_units = 0;
	cout << "This ANN system has " << layers_of_network << " layers." << endl;
	for (int i = 0; i < layers_of_network; i++)
	{
		current_layer_units = each_layer_size[i];
		if (i == layers_of_network - 1)
		{
			cout << "The last layer: " << endl;
		}
		else
		{
			cout << "The " << i << "th layer: " << endl;
		}
		Layers_node[i].display();
	}
	cout << "The target is: " << endl;
	Layers_node[layers_of_network].display();
}

void Neural_network::weight_display()
{
	for (int i = 0; i < layers_of_network - 1; i++)
	{
		cout << "Between " << i << "th layer to " << i + 1 << "th layer: " << endl;
		Weight[i].display();
	}
}

void Neural_network::training_data_display()
{
	for (int i = 0; i < Training_data.size(); i++)
	{
		cout << "The " << i << "th Training data is: " << endl;
		Training_data[i].display();
		Training_target[i].display();
	}
}