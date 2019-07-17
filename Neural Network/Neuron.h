#pragma once

#define TANH 1
#define RELU 2
#define SIGM 3

#include <math.h>

class Neuron {
public:
	// Constructors
	Neuron(double val);
	Neuron(double val, int activation_type);

	// Setter
	void set_val(double val);

	// Getters
	double get_val() { return this->val; }
	double get_activated_val() { return this->activated_val; }
	double get_derived_val() { return this->derived_val; }

	// Helper methods
	void activate();
	void derive();

private:
	double val;
	double activated_val;
	double derived_val;
	int activation_type = 3;
};

