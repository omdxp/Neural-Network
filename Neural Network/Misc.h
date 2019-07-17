#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace utils {
	class Misc {
	public:
		// Helper method
		static vector<vector<double>> fetch_data(string path);
	};
}
