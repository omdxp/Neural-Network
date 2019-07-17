#include "pch.h"
#include "NeuralNetwork.h"
#include "Math.h"

// Helper method
/// This method do the backpropagation operation
void NeuralNetwork::back_propagation() {
	vector<Matrix*> new_weights;
	Matrix* delta_weights;
	Matrix* gradients;
	Matrix* derived_values;
	Matrix* gradients_transposed;
	Matrix* z_activated_vals;
	Matrix* temp_new_weights;
	Matrix* p_gradients;
	Matrix* transposed_p_weights;
	Matrix* hidden_derived;
	Matrix* transposed_hidden;
	/*
		PART 1: Output to last hidden layer
	*/
	int index_output_layer = this->topology.size() - 1;

	gradients = new Matrix(
		1,
		this->topology.at(index_output_layer),
		false
	);

	derived_values = this->layers.at(index_output_layer)->matrixify_derived_vals();

	for (int i = 0; i < this->topology.at(index_output_layer); i++) {
		double e = this->derived_errors.at(i);
		double y = derived_values->get_val(0, i);
		double g = e * y;
		gradients->set_val(0, i, g);
	}

	gradients_transposed = gradients->transpose();
	z_activated_vals     = this->layers.at(index_output_layer - 1)->matrixify_activated_vals();

	delta_weights = new Matrix(
		gradients_transposed->get_num_rows(),
		z_activated_vals->get_num_cols(),
		false
	);

	utils::Math::multiply_matrix(gradients_transposed, z_activated_vals, delta_weights);

	/*
		Compute for new weight (Last hidden <-> Output)
	*/
	temp_new_weights = new Matrix(
		this->topology.at(index_output_layer - 1),
		this->topology.at(index_output_layer),
		false
	);

	for (int r = 0; r < this->topology.at(index_output_layer - 1); r++) {
		for (int c = 0; c < this->topology.at(index_output_layer); c++) {

			double original_value = this->weight_matrices.at(index_output_layer - 1)->get_val(r, c);
			double delta_value    = delta_weights->get_val(c, r);

			original_value = this->momentum * original_value;
			delta_value = this->learning_rate * delta_value;

			temp_new_weights->set_val(r, c, (original_value - delta_value));
		}
	}

	new_weights.push_back(new Matrix(*temp_new_weights));

	delete gradients_transposed;
	delete z_activated_vals;
	delete temp_new_weights;
	delete delta_weights;
	delete derived_values;

	///////////////////////////////////////////////////////////////////////
	/*
		Part 2: Last hidden layer to input layer
	*/
	for (int i = (index_output_layer - 1); i > 0; i--) {

		p_gradients = new Matrix(*gradients);

		delete gradients;

		transposed_p_weights = this->weight_matrices.at(i)->transpose();

		gradients = new Matrix(
			p_gradients->get_num_rows(),
			transposed_p_weights->get_num_cols(),
			false
		);

		utils::Math::multiply_matrix(p_gradients, transposed_p_weights, gradients);

		hidden_derived = this->layers.at(i)->matrixify_derived_vals();

		for (int c = 0; c < hidden_derived->get_num_rows(); c++) {
			double g = gradients->get_val(0, c) * hidden_derived->get_val(0, c);
			gradients->set_val(0, c, g);
		}

		if (i == 1) {
			z_activated_vals = this->layers.at(0)->matrixify_vals();
		}
		else {
			z_activated_vals = this->layers.at(0)->matrixify_activated_vals();
		}

		transposed_hidden = z_activated_vals->transpose();

		delta_weights = new Matrix(
			transposed_hidden->get_num_rows(),
			gradients->get_num_cols(),
			false
		);

		utils::Math::multiply_matrix(transposed_hidden, gradients, delta_weights);

		// Update weights
		temp_new_weights = new Matrix(
			this->weight_matrices.at(i - 1)->get_num_rows(),
			this->weight_matrices.at(i - 1)->get_num_cols(),
			false
		);

		for (int r = 0; r < temp_new_weights->get_num_rows(); r++) {
			for (int c = 0; c < temp_new_weights->get_num_cols(); c++) {

				double original_value = this->weight_matrices.at(i - 1)->get_val(r, c);
				double delta_value    = delta_weights->get_val(r, c);

				original_value = this->momentum * original_value;
				delta_value    = this->learning_rate * delta_value;

				temp_new_weights->set_val(r, c, (original_value - delta_value));
			}
		}
		new_weights.push_back(new Matrix(*temp_new_weights));

		delete p_gradients;
		delete transposed_p_weights;
		delete hidden_derived;
		delete z_activated_vals;
		delete transposed_hidden;
		delete temp_new_weights;
		delete delta_weights;
	}

	for (int i = 0; i < this->weight_matrices.size(); i++) {
		delete this->weight_matrices.at(i);
	}

	this->weight_matrices.clear();

	reverse(new_weights.begin(), new_weights.end());

	for (int i = 0; i < new_weights.size(); i++) {
		this->weight_matrices.push_back(new Matrix(*new_weights[i]));
		delete new_weights[i];
	}
}