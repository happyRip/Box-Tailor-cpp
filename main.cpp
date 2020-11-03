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

double originX, originY, packThk;
unsigned int howManyObjects;
vector<double> sourceDimensions[2];

int main(){
	cout << "Wprowadz ilosc obiektow:" << endl;
	while( cin >> howManyObjects ){
		if( howManyObjects > 0 )
			break;
		else
			cout << "Wprowadzono nieprawidlowa ilosc obiektow.\nWprowadz ilosc obiektow:" << endl;
	}
	
	for( unsigned int i = 0; i < howManyObjects; ++i ){
		double tempX, tempY;
		
		cout << "Wprowadz wymiary obiektu ( x, y )[mm]:" << endl;
		cin >> tempX >> tempY;
		
		sourceDimensions[X].push_back( tempX * Unit );
		sourceDimensions[Y].push_back( tempY * Unit );
	}
//resultant file	
	string outputFileName;
	cout << "Jak ma sie nazywac plik wynikowy?" << endl;
	cin >> outputFileName;

	originX = originY = 0;

	ofstream outputFile;
	outputFile.open ( outputFileName );
	outputFile << "IN;\nLT;\nSP1;\n"; //initialize file
	outputFile.close();
	
	packThk = 1000; //sizeZ
	tailor( &outputFileName, originX, originY, sourceDimensions[X][0] + foamThk, sourceDimensions[Y][0] + foamThk, packThk );
	
	outputFile.open ( outputFileName, std::ios::app );
	outputFile << "SP0;\n";
	outputFile.close();
}