#pragma once

#include <vector>
#include "Matrix.h"

using namespace std;

namespace utils {
	class Math {
	public:
		// Helper method
		static void multiply_matrix(Matrix* a, Matrix* b, Matrix* c);
	};
}


