#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "defines.h"
#include "functions.h"

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::vector;
using std::string;

unsigned int howManyObjects;
vector<pii> boxDimensions;

int main(){
	cout << " Enter object count: ";
	cin >> howManyObjects;
	while( cin.fail() ){
		cin.clear();
		cin.ignore();
		cout << "  Incorrect value.\n Enter object count: ";
		cin >> howManyObjects;
	}
	
	for( unsigned int i = 0; i < howManyObjects; ++i ){
		string inputFileName;
		cout << " Enter input file name: ";
		cin >> inputFileName;
		
		boxDimensions.push_back( calculateSize( inputFileName ) );
	}
	
	string outputFileName;
	cout << " Enter output file name: ";
	cin >> outputFileName;
<<<<<<< HEAD

	writeToFile( outputFileName, boxDimensions );
	
	return 0;
=======
	
	ofstream outputFile;
	outputFile.open ( outputFileName );
	
	outputFile << "IN;\n";
	outputFile << "SP0;\n";
	
	outputFile << "PD" << sourceDimensions[X][0] << ",0;\n";
	outputFile << "PD" << sourceDimensions[X][0] << "," << sourceDimensions[Y][0] << ";\n";
	outputFile << "PD0," << sourceDimensions[Y][0] << ";\n";
	outputFile << "PD0,0;\n";
	
	outputFile << "PU;";
	
	outputFile.close();
>>>>>>> parent of 83c23ea... it works!
}