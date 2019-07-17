#include "pch.h"
#include "NeuralNetwork.h"

// Constructors
NeuralNetwork::NeuralNetwork(
	vector<int> topology,
	int hidden_activation_type,
	int output_activation_type,
	int cost_type_function,
	double bias,
	double learning_rate,
	double momentum
) {
	this->topology      = topology;
	this->topology_size = topology.size();
	this->learning_rate = learning_rate;
	this->momentum      = momentum;
	this->bias          = bias;

	this->hidden_activation_type = hidden_activation_type;
	this->output_activation_type = output_activation_type;
	this->cost_function_type     = cost_function_type;

	for (int i = 0; i < topology_size; i++) {
		if (i > 0 && i < (topology_size - 1)) {
			this->layers.push_back(new Layer(topology.at(i), this->hidden_activation_type));
		}
		else if (i == (topology_size - 1)) {
			this->layers.push_back(new Layer(topology.at(i), this->output_activation_type));
		}
		else {
			this->layers.push_back(new Layer(topology.at(i)));
		}
	}

	for (int i = 0; i < (topology_size - 1); i++) {
		Matrix* weight_matrix = new Matrix(topology.at(i), topology.at(i + 1), true);
		this->weight_matrices.push_back(weight_matrix);
	}

	for (int i = 0; i < topology.at((topology_size - 1)); i++) {
		errors.push_back(0.0);
		derived_errors.push_back(0.0);
	}

	this->error = 0.0;
}

NeuralNetwork::NeuralNetwork(
	vector<int> topology,
	double bias,
	double learning_rate,
	double momentum
) {
	this->topology      = topology;
	this->topology_size = topology.size();
	this->learning_rate = learning_rate;
	this->momentum      = momentum;
	this->bias          = bias;

	for (int i = 0; i < topology_size; i++) {
		if (i > 0 && i < (topology_size - 1)) {
			this->layers.push_back(new Layer(topology.at(i), this->hidden_activation_type));
		}
		else if (i == (topology_size - 1)) {
			this->layers.push_back(new Layer(topology.at(i), this->output_activation_type));
		}
		else {
			this->layers.push_back(new Layer(topology.at(i)));
		}
	}

	for (int i = 0; i < (topology_size - 1); i++) {
		Matrix* weight_matrix = new Matrix(topology.at(i), topology.at(i + 1), true);
		this->weight_matrices.push_back(weight_matrix);
	}

	for (int i = 0; i < topology.at((topology_size - 1)); i++) {
		errors.push_back(0.0);
		derived_errors.push_back(0.0);
	}

	this->error = 0.0;
}

// Helper methods
/// This method load weights from a json file
void NeuralNetwork::load_weights(string file) {
	ifstream i(file);
	json j_weights;
	i >> j_weights;

	vector<vector<vector<double>>> temp = j_weights["weights"];

	for (int i = 0; i < this->weight_matrices.size(); i++) {
		for (int r = 0; r < this->weight_matrices.at(i)->get_num_rows(); r++) {
			for (int c = 0; c < this->weight_matrices.at(i)->get_num_cols(); c++) {
				this->weight_matrices.at(i)->set_val(r, c, temp.at(i).at(r).at(c));
			}
		}
	}
}

/// This method save weights to a json file
void NeuralNetwork::save_weights(string file) {
	json j = {};

	vector<vector<vector<double>>> weight_set;

	for (int i = 0; i < this->weight_matrices.size(); i++) {
		weight_set.push_back(this->weight_matrices.at(i)->get_vals());
	}

	j["weight"] = weight_set;

	ofstream o(file);
	o << setw(4) << j << endl;
}

// Setters
/// This method set the current input
void NeuralNetwork::set_current_input(vector<double> input) {
	this->input = input;

	for (int i = 0; i < input.size(); i++) {
		this->layers.at(0)->set_val(i, input.at(i));
	}
}