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

double originX, originY;
unsigned int howManyObjects;
vector<pii> sourceDimensions;

int main(){
	cout << "Enter the number of objecs: ";
	while( cin >> howManyObjects ){
		if( howManyObjects > 0 )
			break;
		else
			cout << "Wprowadzono nieprawidlowa ilosc obiektow.\nWprowadz ilosc obiektow:" << endl;
	}
	
	for( unsigned int i = 0; i < howManyObjects; ++i ){
		string inputFileName;
		cout << "Enter input file name: ";
		cin >> inputFileName;
		
		sourceDimensions.push_back( calculateSize( inputFileName ) );
	}
//resultant file	
	string outputFileName;
	cout << "Enter output file name: ";
	cin >> outputFileName;

	originX = originY = 0;

	ofstream outputFile;
	outputFile.open ( outputFileName );
	outputFile << "IN;\nLT;\nSP1;\n"; //initialize file
	outputFile.close();

	tailor( &outputFileName, originX, originY, sourceDimensions[0].X + foamThk, sourceDimensions[0].Y + foamThk, packThk );
	
	outputFile.open ( outputFileName, std::ios::app );
	outputFile << "SP0;\n";
	outputFile.close();
}