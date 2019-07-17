#include "pch.h"
#include "NeuralNetwork.h"

// Setters
void NeuralNetwork::set_errors() {
	if (this->target.size() == 0) {
		cerr << "No target for this neural network" << endl;
		assert(false);
	}

	if (this->target.size() != this->layers.at(this->layers.size() - 1)->get_neurons().size()) {
		cerr << "Target size (" << this->target.size() << ") is not the same as output layer size : " << this->layers.at(this->layers.size() - 1)->get_neurons().size() << endl;
		for (int i = 0; i < this->target.size(); i++) {
			cout << this->target.at(i) << endl;
		}

		assert(false);
	}

	switch (cost_function_type) {
	case(COST_MSE): this->set_error_MSE(); break;
	default:        this->set_error_MSE(); break;
	}
}

void NeuralNetwork::set_error_MSE() {
	int output_layer_index         = this->layers.size() - 1;
	vector<Neuron*> output_neurons = this->layers.at(output_layer_index)->get_neurons();

	this->error = 0.0;

	for (int i = 0; i < this->target.size(); i++) {
		double t = target.at(i);
		double y = output_neurons.at(i)->get_activated_val();

		this->errors.at(i)         = 0.5 * pow(abs((t - y)), 2);
		this->derived_errors.at(i) = (y - t);

		this->error += this->errors.at(i);
	}
}