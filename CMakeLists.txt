cmake_minimum_required(VERSION 3.12)
project(hashcode2019)

set(CMAKE_CXX_STANDARD 11)

add_executable(hashcode2019
			   src/main.cpp
			   src/FileParser.cpp
			   src/LineParser.cpp
			   src/Slide.cpp
			   src/Photo.cpp
			   src/Solver.cpp
			   src/TagStorage.cpp
			   src/FileWriter.cpp
        src/InterestFactorCalculator.cpp src/InterestFactorCalculator.h)