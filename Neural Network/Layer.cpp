#include "pch.h"
#include "Layer.h"

// Constructors
/// Constructor with size
Layer::Layer(int size){
	this->size = size;

	for (int i = 0; i < size; i++) {
		Neuron* n = new Neuron(0.0);
		this->neurons.push_back(n);
	}
}

/// Constructor with size and activation type
Layer::Layer(int size, int activation_type) {
	this->size = size;

	for (int i = 0; i < size; i++) {
		Neuron* n = new Neuron(0.0, activation_type);
		this->neurons.push_back(n);
	}
}

// Setter
void Layer::set_val(int i, double v) {
	this->neurons.at(i)->set_val(v);
}

// Getter
vector<double> Layer::get_activated_vals() {
	vector<double> ret;

	for (int i = 0; i < this->neurons.size(); i++) {
		double v = this->neurons.at(i)->get_activated_val();

		ret.push_back(v);
	}

	return ret;
}

// Helper methods
/// This method write the values in a matrix form aka a layer
Matrix* Layer::matrixify_vals() {
	Matrix* m = new Matrix(1, this->neurons.size(), false);

	for (int i = 0; i < this->neurons.size(); i++) {
		m->set_val(0, i, this->neurons.at(i)->get_val());
	}

	return m;
}

/// This method write the activated values in a matrix form aka a layer
Matrix* Layer::matrixify_activated_vals() {
	Matrix* m = new Matrix(1, this->neurons.size(), false);

	for (int i = 0; i < this->neurons.size(); i++) {
		m->set_val(0, i, this->neurons.at(i)->get_activated_val());
	}

	return m;
}

/// This method write the derived values in a matrix form aka a layer
Matrix* Layer::matrixify_derived_vals() {
	Matrix* m = new Matrix(1, this->neurons.size(), false);

	for (int i = 0; i < this->neurons.size(); i++) {
		m->set_val(0, i, this->neurons.at(i)->get_derived_val());
	}

	return m;
}