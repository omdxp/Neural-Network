// Neural Network.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <string>
#include <time.h>

using namespace std;
using json = nlohmann::json;

/// This function print the syntax to use this program
void print_syntax() {
	cout << "Syntax:" << endl;
	cout << "./main [config_file]" << endl;
}

// Main function
int main(int argc, char** argv)
{
	if (argc != 2) {
		print_syntax();
		exit(-1);
	}
	// Neural Network architecture
	ifstream config_file(argv[1]);
	string str((istreambuf_iterator<char>(config_file)),
		istreambuf_iterator<char>()
	);

	auto config = json::parse(str);

	double learning_rate = config["learning_rate"];
	double momentum      = config["momentum"];
	double bias          = config["bias"];
	int epoch            = config["epoch"];
	string training_file = config["training_data"];
	string weights_file  = config["weights"];

	vector<int> topology = config["topology"];

	cout << "Learning rate: " << learning_rate << endl;
	cout << "Momentum: " << momentum << endl;
	cout << "Bias: " << bias << endl;
	cout << "Epoch: " << epoch << endl;
	cout << endl;
	cout << "\tTopology:" << endl;
	for (int i = 0; i < topology.size(); i++) {
		cout << topology.at(i);
		if (i == topology.size() - 1)
			break;
		cout << " ---> ";
	}
	cout << endl;
	// Instanciation of a Neural Network
	NeuralNetwork *n = new NeuralNetwork(topology, 2, 3, 1, bias, learning_rate, momentum);

	vector<vector<double>> training_data = utils::Misc::fetch_data(training_file);

	cout << "Training data size: " << training_data.size() << endl;

	// Training the Neural Network
	cout << "Training..." << endl;
	for (int i = 0; i < epoch; i++) {
		for (int t_index = 0; t_index < training_data.size(); t_index++) {

			vector<double> input  = training_data.at(t_index);
			vector<double> target = training_data.at(t_index);

			n->train(
				input,
				target,
				bias,
				learning_rate,
				momentum
			);
		}
		cout << "Error at epoch " << i + 1 << " : " << n->error << endl;
	}

	// Saving weights to a json file
	cout << "Done! writing to " << weights_file << "..." << endl;
	n->save_weights(weights_file);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
