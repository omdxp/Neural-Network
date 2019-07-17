#include "pch.h"
#include "Misc.h"


// Helper method
/// This method fetch data from a json file
vector<vector<double>> utils::Misc::fetch_data(string path) {
	vector<vector<double>> data;

	ifstream infile(path);

	string line;
	while (getline(infile, line)) {
		vector<double> d_row;
		string		   tok;
		stringstream   ss(line);

		while (getline(ss, tok, ',')) {
			d_row.push_back(stof(tok));
		}

		data.push_back(d_row);
	}

	return data;
}
