#include "mpi.h"
#include <iostream>
#include <map>
#include <iterator>
#include <vector>

#include <fstream>

using namespace std;

void fill_text_map(string path) {

	fstream file;

	string word;

	file.open(path.c_str())

	while(file >> word) {
		cout << word << endl;
	}

}

int main(int argc, char** argv) {

	fill_text_map('./sample.txt');

	return 0;

}