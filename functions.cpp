#include <string>
#include <vector>
#include <time.h>
#include <climits>
#include <utility>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "defines.h"

using std::min;
using std::max;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::to_string;
using std::make_pair;

//functions code goes here

pair<int,int> getValues( string line ){
	pair<int,int> result( 0, 0 );
	bool second = false;
	
	for( int i = 0; i < line.length(); ++i ){
			if( !isdigit( line[i] ) ){
				if( line[i] == ' ' && isdigit( line[i+1] ) ) //X and Y coordinates are separated by ' '
					second = true;
				continue;
			}
			if( second ){
				result.Y *= 10;
				result.Y += ( line[i] - '0' );
			}else {
				result.X *= 10;
				result.X += ( line[i] - '0' );
			}
		}
	return result;
}

void getExtremes( int x, int y, vector<pii> & Extremes ){
	Extremes[MAX].X = max( Extremes[MAX].X, x );
	Extremes[MAX].Y = max( Extremes[MAX].Y, y );
	Extremes[MIN].X = min( Extremes[MIN].X, x );
	Extremes[MIN].Y = min( Extremes[MIN].Y, y );
}


pair<int,int> calculateSize( string fileName ){ //looks for extreme values of an object in a *.plt file to find its dimensions for box fitting purposes
	ifstream inputFile;
	
	inputFile.open( fileName );
	
	string line;	
	vector<pii> Extremes; // [0].first - [MIN].X; [1].second - [MAX].Y
	Extremes.push_back( make_pair( INT_MAX, INT_MAX ) );
	Extremes.push_back( make_pair( INT_MIN, INT_MIN ) );
	
	while( getline( inputFile, line ) ){
		pair<int,int> value;

		if( line[0] == 'P' ){
			value = getValues( line );
			getExtremes( value.X, value.Y, Extremes );
		}
	}
	cout << fileName << ":\n	X: " << ( Extremes[MAX].X - Extremes[MIN].X ) / Unit << "mm\n	Y: " << ( Extremes[MAX].Y  - Extremes[MIN].Y  ) / Unit << "mm\n";
	
	inputFile.close();
	
	pair<int,int> result( Extremes[MAX].X - Extremes[MIN].X, Extremes[MAX].Y  - Extremes[MIN].Y );
	return result;
}

string line( double * originX, double * originY, double distanceX, double distanceY ){
	*originX += distanceX;
	*originY += distanceY;
	
	string result = "PD"; //pen down
	
	result += to_string( *originX );
	result += " ";
	result += to_string( *originY );
	result += ";\n";
	
	return result;
}

string move( double * originX, double * originY, double distanceX, double distanceY ){
	*originX += distanceX;
	*originY += distanceY;
	
	string result = "PU"; //pen up
	
	result += to_string( *originX );
	result += " ";
	result += to_string( *originY );
	result += ";\n";
	
	return result;
}

void tailor( string * outputFileName, double originX, double originY, double sizeX, double sizeY, double sizeZ ){
	
	ofstream outputFile;
	outputFile.open( *outputFileName, std::ios::app );
	
	outputFile << move( &originX, &originY, 3 * wallThk + sizeZ, 0 ); 
	outputFile << line( &originX, &originY, 2 * sizeZ + sizeX, 0 );
	outputFile << line( &originX, &originY, 0, -sizeZ );
	outputFile << line( &originX, &originY, -sizeZ, 0 );
	outputFile << line( &originX, &originY, 0, -wallThk );
	outputFile << line( &originX, &originY, 2 * wallThk + sizeZ, 0 );
	outputFile << line( &originX, &originY, 0, sizeZ );
	outputFile << line( &originX, &originY, sizeX, 0 );
	outputFile << line( &originX, &originY, 0, -sizeZ );
	outputFile << line( &originX, &originY, sizeZ, 0 );
	outputFile << line( &originX, &originY, 0, -sizeY );
	outputFile << line( &originX, &originY, -sizeZ, 0 );
	outputFile << line( &originX, &originY, 0, -sizeZ );
	outputFile << line( &originX, &originY, -sizeX, 0 );
	outputFile << line( &originX, &originY, 0, sizeZ );
	outputFile << line( &originX, &originY, -( 2 * wallThk + sizeZ ), 0 );
	outputFile << line( &originX, &originY, 0, -wallThk );
	outputFile << line( &originX, &originY, sizeZ, 0 );
	outputFile << line( &originX, &originY, 0, -sizeZ );
	outputFile << line( &originX, &originY, -( 2 * sizeZ + sizeX ), 0 );
	outputFile << line( &originX, &originY, 0, sizeZ );
	outputFile << line( &originX, &originY, sizeZ, 0 );
	outputFile << line( &originX, &originY, 0, wallThk );
	outputFile << line( &originX, &originY, -( 2 * ( sizeZ + wallThk ) ), 0 );
	outputFile << line( &originX, &originY, 0, sizeY / 5 );
	outputFile << line( &originX, &originY, -( 1.5 * wallThk ), 0 );
	outputFile << line( &originX, &originY, 0, sizeY / 5 );
	outputFile << line( &originX, &originY, 1.5 * wallThk, 0 );
	outputFile << line( &originX, &originY, 0, sizeY / 5 );
	outputFile << line( &originX, &originY, -( 1.5 * wallThk ), 0 );
	outputFile << line( &originX, &originY, 0, sizeY / 5 );
	outputFile << line( &originX, &originY, 1.5 * wallThk, 0 );
	outputFile << line( &originX, &originY, 0, sizeY / 5 );
	outputFile << line( &originX, &originY, 2 * ( wallThk + sizeZ ), 0 );
	outputFile << line( &originX, &originY, 0, wallThk );
	outputFile << line( &originX, &originY, -sizeZ, 0 );
	outputFile << line( &originX, &originY, 0, sizeZ );
	
	outputFile.close();
}

int lessOrEqual( double * array, int n, double target ){ //binary search for a value less or equal to the target value in a sorted array
	int L = 0;
	int R = n - 1;
	
	while( L < R ){
		int M = ( L + R + 1 ) / 2;
		
		if( array[M] > target )
			R = M - 1;
		else
			L = M;
	}
	
	if( array[L] > target )
		return -1; //if no such value that is less or equal to the target value
	return L;
}

double getRand( double min, double max ){ //generates a random number between min and max values
	return ( max - min ) * ( (double)rand() / (double)RAND_MAX ) + min;
}