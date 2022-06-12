#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
};

void find_minmax(const vector<double>& numbers, double& min, double& max);
void show_histogram_text(vector<size_t> bins);
vector <size_t> make_histogram(const Input& input);


#endif // HISTOGRAM_H_INCLUDED
