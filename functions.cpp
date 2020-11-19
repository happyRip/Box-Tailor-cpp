#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
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

//function code goes here

pii getValues( string line ){ //looks for X Y coordinates in a single line of HPGL code
	pii result( 0, 0 );
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

string getFileName( string filePath ){
	const size_t lastSlash = filePath.find_last_of( "\\/" );
	
	if ( string::npos != lastSlash )
	{
		filePath.erase( 0, lastSlash + 1 );
	}
	
	return filePath;
}

void getExtremes( int x, int y, vector<pii> & Extremes ){ 
	Extremes[MAX].X = max( Extremes[MAX].X, x );
	Extremes[MAX].Y = max( Extremes[MAX].Y, y );
	Extremes[MIN].X = min( Extremes[MIN].X, x );
	Extremes[MIN].Y = min( Extremes[MIN].Y, y );
}


pii calculateSize( string fileName ){ //looks for extreme values of an object in a *.plt file to find its dimensions for box fitting purposes
	ifstream inputFile;
	
	inputFile.open( fileName );
	
	string line;	
	vector<pii> Extremes; // [0].first = [MIN].X; [1].second = [MAX].Y
	Extremes.push_back( make_pair( INT_MAX, INT_MAX ) );
	Extremes.push_back( make_pair( INT_MIN, INT_MIN ) );
	
	while( getline( inputFile, line ) ){
		pii value;

		if( line[0] == 'P' ){
			value = getValues( line );
			getExtremes( value.X, value.Y, Extremes );
		}
	}
	cout << "  " << getFileName( fileName ) << ":\n	X: " << ( Extremes[MAX].X - Extremes[MIN].X ) / Unit << "mm\n	Y: " << ( Extremes[MAX].Y  - Extremes[MIN].Y  ) / Unit << "mm\n";
	
	inputFile.close();
	
	pii result( Extremes[MAX].X - Extremes[MIN].X, Extremes[MAX].Y  - Extremes[MIN].Y );
	return result;
}

string line( pii & origin, pii distance ){
	origin.X += distance.X;
	origin.Y += distance.Y;
	
	string result = "PD"; //pen down
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string lineX( pii & origin, int distanceX ){
	origin.X += distanceX;
	
	string result = "PD"; //pen down
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string lineY( pii & origin, int distanceY ){
	origin.Y += distanceY;
	
	string result = "PD"; //pen down
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string move( pii & origin, pii distance ){
	origin.X += distance.X;
	origin.Y += distance.Y;
	
	string result = "PU"; //pen up
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string moveX( pii & origin, int distanceX ){
	origin.X += distanceX;
	
	string result = "PU"; //pen up
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string moveY( pii & origin, int distanceY ){
	origin.Y += distanceY;
	
	string result = "PU"; //pen up
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

void tailor( string * outputFileName, pii & origin, pair <double,double> size, double sizeZ ){
	ofstream outputFile;
	outputFile.open( *outputFileName, std::ios::app );
	
	pii basePoint = origin;
	
	outputFile << "SP1;\n"; //select pen 1: cutting
	
	outputFile << moveX( origin, 3 * wallThk + sizeZ ); 
	outputFile << lineX( origin, 2 * sizeZ + size.X );
	outputFile << lineY( origin, -sizeZ );
	outputFile << lineX( origin, -sizeZ );
	outputFile << lineY( origin, -wallThk );
	outputFile << lineX( origin, 2 * wallThk + sizeZ );
	outputFile << lineY( origin, sizeZ );
	outputFile << lineX( origin, size.X );
	outputFile << lineY( origin,  -sizeZ );
	outputFile << lineX( origin, sizeZ );
	outputFile << lineY( origin, -size.Y );
	outputFile << lineX( origin, -sizeZ );
	outputFile << lineY( origin, -sizeZ );
	outputFile << lineX( origin, -size.X );
	outputFile << lineY( origin, sizeZ );
	outputFile << lineX( origin, -( 2 * wallThk + sizeZ ) );
	outputFile << lineY( origin, -wallThk );
	outputFile << lineX( origin, sizeZ );
	outputFile << lineY( origin, -sizeZ );
	outputFile << lineX( origin, -( 2 * sizeZ + size.X ) );
	outputFile << lineY( origin, sizeZ );
	outputFile << lineX( origin, sizeZ );
	outputFile << lineY( origin, wallThk );
	outputFile << lineX( origin, -( 2 * ( sizeZ + wallThk ) ) );
	outputFile << lineY( origin, size.Y / 5 );
	outputFile << lineX( origin, -( 1.5 * wallThk ) );
	outputFile << lineY( origin, size.Y / 5 );
	outputFile << lineX( origin, 1.5 * wallThk );
	outputFile << lineY( origin, size.Y / 5 );
	outputFile << lineX( origin, -( 1.5 * wallThk ) );
	outputFile << lineY( origin, size.Y / 5 );
	outputFile << lineX( origin, 1.5 * wallThk );
	outputFile << lineY( origin, size.Y / 5 );
	outputFile << lineX( origin, 2 * ( wallThk + sizeZ ) );
	outputFile << lineY( origin, wallThk );
	outputFile << lineX( origin, -sizeZ );
	outputFile << lineY( origin, sizeZ );
	
	origin = basePoint;
	
	outputFile << move( origin, make_pair( 4 * wallThk + 2 * sizeZ, -( sizeZ + wallThk + 0.4 * size.Y ) ) );
	outputFile << lineY( origin, size.Y / 5 );
	outputFile << lineX( origin, wallThk );
	outputFile << lineY( origin, -size.Y / 5 );
	outputFile << lineX( origin, -wallThk );
	
	outputFile << moveY( origin, -2 * size.Y / 5 );
	outputFile << lineY( origin, size.Y / 5 );
	outputFile << lineX( origin, wallThk );
	outputFile << lineY( origin, -size.Y / 5 );
	outputFile << lineX( origin, -wallThk );
	
	outputFile << "SP2;\n"; //select pen 2: engraving
	
	origin = basePoint;
	
	outputFile << move( origin, make_pair( 1.5 * wallThk + sizeZ, -sizeZ - wallThk ) );
	outputFile << lineY( origin, -size.Y );
	
	outputFile << moveX( origin, wallThk );
	outputFile << lineY( origin, size.Y );
	
	outputFile << move( origin, make_pair( sizeZ + 0.5 * wallThk, wallThk + sizeZ ) );
	outputFile << lineY( origin, -sizeZ );
	
	outputFile << moveY( origin, -wallThk );
	outputFile << lineY( origin, -size.Y );
	
	outputFile << moveY( origin, -wallThk );
	outputFile << lineY( origin, -sizeZ );
	
	outputFile << moveY( origin, sizeZ + wallThk / 2 );
	outputFile << lineX( origin, size.X );
	
	outputFile << moveY( origin, -wallThk / 2 - sizeZ );
	outputFile << lineY( origin, sizeZ );

	outputFile << moveY( origin, wallThk );
	outputFile << lineY( origin, size.Y );
	
	outputFile << moveY( origin, wallThk + sizeZ );
	outputFile << lineY( origin, -sizeZ );
	
	outputFile << moveY( origin, -wallThk / 2 );
	outputFile << lineX( origin, -size.X );
	
	outputFile << move( origin, make_pair( size.X + sizeZ + 3 * wallThk / 2, -wallThk / 2 ) );
	outputFile << lineY( origin, -size.Y );
	
	outputFile << moveX( origin, wallThk / 2 );
	outputFile << lineX( origin, size.X );
	
	outputFile << lineY( origin, size.Y );
	
	outputFile << lineX( origin, -size.X );
	
	origin = basePoint;
	
	outputFile.close();
}

void writeToFile( string fileName, vector<pii> & sourceDimensions ){
	ofstream outputFile;
	
	outputFile.open( fileName );
	outputFile << "IN;\nLT;\n"; //initialize file
	outputFile.close();
	
	pii origin( 0, 0 );
	for( int i = 0; i < sourceDimensions.size(); ++i ){
		pii boxDimensions( 
			4 * packThk + 6 * wallThk + 2 * ( sourceDimensions[i].X + foamThk ),
			2 * packThk + 3 * wallThk + ( sourceDimensions[i].Y + foamThk ) 
		);
		
		tailor( 
			&fileName, 
			origin, 
			make_pair( (double)( sourceDimensions[i].X + foamThk ), (double)( sourceDimensions[i].Y + foamThk ) ), 
			packThk
		);
				
		origin = make_pair( 0, origin.Y + boxDimensions.Y );
		
	}
	outputFile.open ( fileName, std::ios::app );
	outputFile << "SP0;\n";
	outputFile.close();
}
/*
int lessOrEqual( double * array, int n, double target ){
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

int getRand( int min, int max ){ //generates a random number between min and max values
	return rand() % ( max - min + 1 ) + min;
}
*/