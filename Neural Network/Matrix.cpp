#include "pch.h"
#include "Matrix.h"

// Constructor
Matrix::Matrix(int num_rows, int num_col, bool is_random) {
	this->num_rows = num_rows;
	this->num_cols = num_cols;

	for (int i = 0; i < num_rows; i++) {
		vector<double> col_values;

		for (int j = 0; j < num_cols; j++) {
			double r = is_random == true ? this->generte_random_number() : 0.0;
			col_values.push_back(r);
		}

		this->values.push_back(col_values);
	}
}

// Helper methods
/// This method do a transpose to the matrix
Matrix* Matrix::transpose() {
	Matrix* m = new Matrix(this->num_cols, this->num_rows, false);

	for (int i = 0; i < this->num_rows; i++) {
		for (int j = 0; j < this->num_cols; j++) {
			m->set_val(j, i, this->get_val(i, j));
		}
	}

	return m;
}

/// This method copy a matrix to another
Matrix* Matrix::copy() {
	Matrix* m = new Matrix(this->num_rows, this->num_cols, false);

	for (int i = 0; i < this->num_rows; i++) {
		for (int j = 0; j < this->num_cols; j++) {
			m->set_val(i, j, this->get_val(i, j));
		}
	}

	return m;
}

/// This method generate a random number
double Matrix::generte_random_number() {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(-.0001, .0001);

	return dis(gen);
}

/// This method print a matrix to console
void Matrix::print_to_console() {
	for (int i = 0; i < this->num_rows; i++) {
		for (int j = 0; j < this->num_cols; j++) {
			cout << this->values.at(i).at(j) << '\t';
		}
		cout << endl;
	}
}