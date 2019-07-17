#include "pch.h"
#include "Neuron.h"

// Constructors
Neuron::Neuron(double val) {
	this->set_val(val);
}
Neuron::Neuron(double val, int activation_type) {
	this->activation_type = activation_type;
	this->set_val(val);
}

// Setter
void Neuron::set_val(double val) {
	this->val = val;
	activate();
	derive();
}

// Helper methods
/// This method activated the neuron on the specefied activation type : tanh, relu, sigmoid
void Neuron::activate() {
	if (this->activation_type == TANH) {
		this->activated_val = tanh(this->val);
	}
	else if (this->activation_type == RELU) {
		if (this->val > 0) {
			this->activated_val = this->val;
		}
		else {
			this->activated_val = 0;
		}
	}
	else if (this->activation_type == SIGM) {
		this->activated_val = (1 / (1 + exp(-this->val)));
	}
	else {
		this->activated_val = (1 / (1 + exp(-this->val)));
	}
}

/// This method derive the neuron for the specefic activation type : tanh, relu, sigmoid
void Neuron::derive() {
	if (this->activation_type == TANH) {
		this->derived_val = (1.0 - (this->activated_val * this->activated_val));
	}
	else if (this->activation_type == RELU) {
		if (this->val > 0) {
			this->derived_val = 1;
		}
		else {
			this->derived_val = 0;
		}
	}
	else if (this->activation_type == SIGM) {
		this->derived_val = (this->activated_val * (1 - this->activated_val));
	}
	else {
		this->derived_val = (this->activated_val * (1 - this->activated_val));
	}
}