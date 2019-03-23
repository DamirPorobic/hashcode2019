#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "fileHandling/FileParser.h"
#include "fileHandling/FileWriter.h"
#include "algorithm/Solver.h"
#include "storage/TagStorage.h"

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
	FileWriter fileWriter{};
	Solver solver{};
	int overallPoints = 0;
	auto startTime = chrono::high_resolution_clock::now();
	for(const auto &filename : filenames) {
		cout << "Parsing: " << filename << endl;
		tagStorage.clear();
		auto photos = fileParser.parse("../in/" + filename, tagStorage);
		auto slides = solver.solve(photos, tagStorage.tagCount());
		auto points = fileWriter.write("../out/" + filename, slides);
		overallPoints += points;
		cout << "Points in " << filename << ": " << to_string(points) << endl;
		cout << "----------------------------------" << endl;
	}
	auto currentTime = chrono::high_resolution_clock::now();
	auto runtimeInSeconds = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
	cout << "Overall Points: " << overallPoints << endl;
	cout << "Runtime: " << runtimeInSeconds/60 << "min " << runtimeInSeconds % 60 << "s" << endl;

	return 0;
}
