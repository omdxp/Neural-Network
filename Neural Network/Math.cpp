#include "pch.h"
#include "Math.h"


// Helper method
/// This method multiply matrix a with matrix b and write the result to matrix c
void utils::Math::multiply_matrix(Matrix* a, Matrix*b, Matrix* c) {
	for (int i = 0; i < a->get_num_rows(); i++) {
		for (int j = 0; j < b->get_num_cols(); j++) {
			for (int k = 0; k < b->get_num_rows(); k++) {
				double p = a->get_val(i, k) * b->get_val(k, j);
				double new_val = c->get_val(i, j) + p;
				c->set_val(i, j, new_val);
			}

			c->set_val(i, j, c->get_val(i, j));
		}
	}
}