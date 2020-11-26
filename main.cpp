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
vpii objDimensions;
pii boardSize( 3200 * Unit, 2100 * Unit );

int main( int argc, char * argv[] ){
	
	if( argc == 1 ){
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
			
			objDimensions.push_back( calculateSize( inputFileName ) );
		}
	}else {
		for( int i = 1; i < argc; ++i ){
			objDimensions.push_back( calculateSize( argv[i] ) );
		}
	}

	string outputFileName = "output.plt";

	vpii boxDimensions = calculateBoxesDimensions( objDimensions );
	
	vector<vpii> sortedDimensions = shelfPack( boxDimensions, boardSize );
	
	splitToBoards( sortedDimensions, boardSize );
	
	return 0;
}