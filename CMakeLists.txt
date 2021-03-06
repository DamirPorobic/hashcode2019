cmake_minimum_required(VERSION 3.12)
project(hashcode2019)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE( Boost 1.61 REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
link_directories(${Boost_LIBRARY_DIR})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")


set(HASHCODE_SRC
		src/main.cpp
		src/fileHandling/FileParser.cpp
		src/fileHandling/LineParser.cpp
		src/objects/Slide.cpp
		src/objects/Photo.cpp
		src/algorithm/Solver.cpp
		src/storage/TagStorage.cpp
		src/fileHandling/FileWriter.cpp
		src/algorithm/InterestFactorCalculator.cpp
		src/storage/SlideStorage.cpp
		)

add_executable(hashcode2019 ${HASHCODE_SRC})


TARGET_LINK_LIBRARIES( hashcode2019 ${Boost_LIBRARIES} )
