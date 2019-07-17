#include "pch.h"
#include "NeuralNetwork.h"
#include "Math.h"

// Helper method
/// This method do the feed forward operation
void NeuralNetwork::feed_forward() {
	Matrix* a; // Matrix of neurons to the left
	Matrix* b; // Matrix of weights to the right of layer
	Matrix* c; // Matrix of neurons to the next layers

	for (int i = 0; i < (this->topology_size - 1); i++) {
		a = this->get_neuron_matrix(i);
		b = this->get_weight_matrix(i);
		c = new Matrix(
			a->get_num_rows(),
			b->get_num_cols(),
			false
		);

		if (i != 0) {
			a = this->get_activated_neuron_matrix(i);
		}

		utils::Math::multiply_matrix(a, b, c);

		for (int c_index = 0; c_index < c->get_num_cols(); c_index++) {
			this->set_neuron_val(i + 1, c_index, c->get_val(0, c_index) + this->bias);
		}

		delete a;
		delete b;
		delete c;
	}
}