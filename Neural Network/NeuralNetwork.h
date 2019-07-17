#pragma once

#define COST_MSE 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
#include "Matrix.h"
#include "Layer.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class NeuralNetwork {
public:
	// Constructors
	NeuralNetwork(
		vector<int> topology,
		double bias = 1,
		double learning_rate = 0.05,
		double momentum = 1
	);
	NeuralNetwork(
		vector<int> topology,
		int hidden_activation_type,
		int output_activation_type,
		int cost_function_type,
		double bias = 1,
		double learning_rate = 0.05,
		double momentum = 1
	);

	// Setters
	void set_neuron_val(int index_layer, int index_neuron, double val) { this->layers.at(index_layer)->set_val(index_neuron, val); }
	void set_errors();
	void set_current_input(vector<double> input);
	void set_current_target(vector<double> target) { this->target = target; }

	// Getters
	vector<double> get_activated_vals(int index) { return this->layers.at(index)->get_activated_vals(); }
	Matrix* get_neuron_matrix(int index) { return this->layers.at(index)->matrixify_vals(); }
	Matrix* get_activated_neuron_matrix(int index) { return this->layers.at(index)->matrixify_activated_vals(); }
	Matrix* get_derived_neuron_matrix(int index) { return this->layers.at(index)->matrixify_derived_vals(); }
	Matrix* get_weight_matrix(int index) { return new Matrix(*this->weight_matrices.at(index)); }

	// Helper methods
	void save_weights(string file);
	void load_weights(string file);
	void feed_forward();
	void back_propagation();
	void train(
		vector<double> input,
		vector<double> target,
		double bias,
		double learning_rate,
		double momentum
	);

	// public attributes
	int topology_size;
	int hidden_activation_type = RELU;
	int output_activation_type = SIGM;
	int cost_function_type     = COST_MSE;

	vector<int>     topology;
	vector<Layer*>  layers;
	vector<Matrix*> weight_matrices;
	vector<Matrix*> gradient_matrices;

	vector<double> input;
	vector<double> target;
	vector<double> errors;
	vector<double> derived_errors;

	double error = 0;
	double bias  = 1;
	double momentum;
	double learning_rate;
private:
	void set_error_MSE();
};

