#include <cstdlib>
#include <fstream>
#include <string>
#include <time.h>
#include "defines.h"

using std::string;
using std::ofstream;
using std::to_string;

//functions code goes here

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