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
vector<pii> sourceDimensions;

int main(){
	cout << " Enter the number of objecs: ";
	while( cin >> howManyObjects ){
		if( howManyObjects > 0 )
			break;
		else
			cout << "  Incorrect value.\n";
	}
	
	for( unsigned int i = 0; i < howManyObjects; ++i ){
		string inputFileName;
		cout << " Enter input file name: ";
		cin >> inputFileName;
		
		sourceDimensions.push_back( calculateSize( inputFileName ) );
	}
	
	string outputFileName;
	cout << " Enter output file name: ";
	cin >> outputFileName;

	writeToFile( outputFileName, sourceDimensions );
	
	return 0;
}