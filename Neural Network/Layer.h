#pragma once

#include "Neuron.h"
#include "Matrix.h"

using namespace std;

class Layer
{
public:
	// Constructor
	Layer(int size);
	Layer(int size, int activation_type);

	// Setter
	void set_val(int i, double v);
	void set_neuron(vector<Neuron*> neurons) { this->neurons = neurons; }

	// Getters
	vector<double> get_activated_vals();
	vector<Neuron*> get_neurons() { return this->neurons; }

	// Helper methods
	Matrix* matrixify_vals();
	Matrix* matrixify_activated_vals();
	Matrix* matrixify_derived_vals();

private:
	int size;
	vector<Neuron*> neurons;
};

