#pragma once

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Matrix
{
public:
	// Constructor
	Matrix(int num_rows, int num_cols, bool is_random);

	// Setter
	void set_val(int r, int c, double v) { this->values.at(r).at(c) = v; }

	// Getters
	double get_val(int r, int c) { return this->values.at(r).at(c); }
	int get_num_rows() { return this->num_rows; }
	int get_num_cols() { return this->num_cols; }
	vector<vector<double>> get_vals() { return this->values; }

	// Helper methods
	Matrix* transpose();
	Matrix* copy();
	void print_to_console();

private:
	double generte_random_number();
	int num_rows;
	int num_cols;
	vector<vector<double>> values;
};

