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

	writeToFile( outputFileName, boxDimensions );
	
	return 0;
}