#include <iostream>
#include <fstream>
#include <string>

#include "FileParser.h"
#include "FileWriter.h"
#include "Solver.h"
#include "TagStorage.h"

using namespace std;

int main()
{
	vector<string> filenames = {
		"a_example.txt",
	    "b_lovely_landscapes.txt",
	    "c_memorable_moments.txt",
	    "d_pet_pictures.txt",
	    "e_shiny_selfies.txt"
	};
	TagStorage tagStorage;
	FileParser fileParser{};
	FileWriter fileWriter;
	Solver solver;
	for(const auto &filename : filenames) {
		cout << "Parsing: " << " " << filename << endl;
		tagStorage.clear();
		auto photos = fileParser.parse("../in/" + filename, tagStorage);
		auto slides = solver.solve(photos);
		fileWriter.write("../out/" + filename, slides);
		cout << "----------------------------------" << endl;
	}

	return 0;
}
