#include "pch.h"
#include "NeuralNetwork.h"

// Helper method
/// This method train the neural network
void NeuralNetwork::train(
	vector<double> input,
	vector<double> target,
	double bias,
	double learning_rate,
	double momentum
) {
	this->learning_rate = learning_rate;
	this->momentum      = momentum;
	this->bias          = bias;

	this->set_current_input(input);
	this->set_current_target(target);

	this->feed_forward();
	this->set_errors();
	this->back_propagation();
}