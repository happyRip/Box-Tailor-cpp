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
using std::swap;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::to_string;
using std::make_pair;

//function code goes here

bool sortBySecond( const pii a, const pii b )
{
	return ( a.Y < b.Y );
}

int area( pii box )
{
	return box.X * box.Y;
}

pii getValues( string line )
{
	pii result( 0, 0 );

	bool second = false;
	
	for( int i = 0; i < line.length(); ++i ){
			if( !isdigit( line[i] ) ){
				if( line[i] == ' ' && ( isdigit( line[i+1] ) || isdigit( line[i+2] ) ) ) //X and Y coordinates are separated by ' '
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

string getFileName( string filePath )
{
	const size_t lastSlash = filePath.find_last_of( "\\/" );
	
	if ( string::npos != lastSlash )
	{
		filePath.erase( 0, lastSlash + 1 );
	}
	
	return filePath;
}

void getExtremes( int x, int y, vector<pii> & Extremes )
{ 
	Extremes[MAX].X = max( Extremes[MAX].X, x );
	Extremes[MAX].Y = max( Extremes[MAX].Y, y );
	Extremes[MIN].X = min( Extremes[MIN].X, x );
	Extremes[MIN].Y = min( Extremes[MIN].Y, y );
}

pii calcBoxSize( pii objDimensions )
{
	//cout << "boxX: " << 4 * packThk + 5.8 * wallThk + 2 * ( objDimensions.X + foamThk ) << " boxY: " << 2 * packThk + 2.5 * wallThk + ( objDimensions.Y + foamThk ) << endl;
	
	return make_pair( 
			4 * packThk + 5.8 * wallThk + 2 * ( objDimensions.X + foamThk ),
			2 * packThk + 2.5 * wallThk + ( objDimensions.Y + foamThk )
	);
}

pii calcObjSize( pii boxDimensions )
{
	//cout << "objX: " << ( boxDimensions.X - 4 * packThk - 5.8 * wallThk - 2 * foamThk ) / 2 << " objY: " << ( boxDimensions.Y - 2 * packThk - 2.5 * wallThk - foamThk ) << endl;
	
	return make_pair( 
			( boxDimensions.X - 4 * packThk - 5.8 * wallThk - 2 * foamThk ) / 2,
			//4 * packThk + 5.8 * wallThk + 2 * ( objDimensions.X + foamThk ),
			( boxDimensions.Y - 2 * packThk - 2.5 * wallThk - foamThk )
			//2 * packThk + 2.5 * wallThk + ( objDimensions.Y + foamThk )
	);
}

pii calculateSize( string fileName )
{ //looks for extreme values of an object in a *.plt file to find its dimensions for box fitting purposes
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
	
	pii size( ( Extremes[MAX].X - Extremes[MIN].X ),( Extremes[MAX].Y  - Extremes[MIN].Y  ));
	
	if( size.X > size.Y )
		swap( size.X, size.Y );
		
	pii box( calcBoxSize( size ) );
	
	cout << "  " << getFileName( fileName ) << ":\n	X: "<< size.X / Unit << "mm, boxX: " << box.X / Unit << "mm;\n 	Y: " << size.Y / Unit << "mm, boxY: " << box.Y / Unit << "mm;\n";
	
	inputFile.close();
	
	pii result( Extremes[MAX].X - Extremes[MIN].X, Extremes[MAX].Y  - Extremes[MIN].Y );
	return result;
}

string line( pii & origin, pii distance )
{
	origin.X += distance.X;
	origin.Y += distance.Y;
	
	string result = "PD"; //pen down
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string lineX( pii & origin, int distanceX )
{
	origin.X += distanceX;
	
	string result = "PD"; //pen down
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string lineY( pii & origin, int distanceY )
{
	origin.Y += distanceY;
	
	string result = "PD"; //pen down
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string move( pii & origin, pii distance )
{
	origin.X += distance.X;
	origin.Y += distance.Y;
	
	string result = "PU"; //pen up
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string moveX( pii & origin, int distanceX )
{
	origin.X += distanceX;
	
	string result = "PU"; //pen up
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

string moveY( pii & origin, int distanceY )
{
	origin.Y += distanceY;
	
	string result = "PU"; //pen up
	
	result += to_string( origin.X );
	result += " ";
	result += to_string( origin.Y );
	result += ";\n";
	
	return result;
}

void tailor( string outputFileName, pii origin, pair <int,int> size, int sizeZ )
{
	ofstream outputFile;
	outputFile.open( outputFileName, std::ios::app );
	//outputFile << "aaa\n";
	if( outputFile.is_open() )
		cout << "\n THE FILE IS OPEN!\n\n";
		
	pii basePoint = origin;
	
	cout << "oXx: " << origin.X << " oYy: " << origin.Y << endl;
	
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
	
	//cout << "done\n";
	
	outputFile.close();
}

int lessOrEqual( vector<pii> boxDimensions, int target, char argument )
{
	int L = 0;
	int R = boxDimensions.size() - 1;

	switch( argument )
	{
		case 'X':
			while( L < R ){
				int M = ( L + R + 1 ) / 2;
				
				if( boxDimensions[M].X > target )
					R = M - 1;
				else
					L = M;
			}
			
			if( boxDimensions[L].X > target )
				return -1;
			return L;
			
		case 'Y':
			while( L < R ){
				int M = ( L + R + 1 ) / 2;
				
				if( boxDimensions[M].Y > target )
					R = M - 1;
				else
					L = M;
			}
			
			if( boxDimensions[L].Y > target )
				return -1;
			return L;
			
		default:
			cout << "  Wrong case argument!\n";
	}
}

vector<vpii> shelfPack( vpii boxDimensions,  pii boardSize )
{
	vector<vpii> sortedDimensions;
	vpii bottomLeftCorner;
	int rowHeight = 0;
	pii currentPosition( 0, 0 );
	
	while( !boxDimensions.empty() ){
		int i = lessOrEqual( boxDimensions, boardSize.X - currentPosition.X, 'X' );
		//int j = lessOrEqual( boxDimensions, boardSize.X - currentPosition.X, 'Y' );
/*
		if( ( ( area( boxDimensions[j] ) > area( boxDimensions[i] ) ) && j >= 0 ) || i < 0 ){
			if( boxDimensions[j].X <= rowHeight ){
				//cout << " ROW HEIGHT: " << rowHeight / Unit << " Y: " << boxDimensions[j].Y / Unit << endl; 
				i = j;
				swap( boxDimensions[i].X, boxDimensions[i].Y );
			}
		}
*/
		
		//cout << "i: " << i << endl;
		if( i == -1 ){
			currentPosition.X = 0;
			//cout << "  rowHeight: " << rowHeight << endl;
			currentPosition.Y += rowHeight;
			//cout << "CP:\n  X: " << currentPosition.X << " Y: " << currentPosition.Y << endl;

			sortedDimensions.push_back( bottomLeftCorner );
			bottomLeftCorner.clear();

			i = 0;
		}
		
		if( currentPosition.X == 0 )	
			rowHeight = boxDimensions[i].Y;
		
		//cout << "H: " << rowHeight << endl;
			
		currentPosition.X += boxDimensions[i].X;
		bottomLeftCorner.push_back( boxDimensions[i] );
		
		boxDimensions.erase( boxDimensions.begin() + i );
		
		if( boxDimensions.empty() ){
			sortedDimensions.push_back( bottomLeftCorner );
			bottomLeftCorner.clear();
		}
		
		//cout << "cpX: " << currentPosition.X << " cpY: " << currentPosition.Y << endl;
	}
	
	for( int i = 0; i < sortedDimensions.size(); ++i ){
		//cout << "i: " << i << endl;
        for( int j = 0; j < sortedDimensions[i].size(); ++j ){
            cout << "X: " << sortedDimensions[i][j].X / Unit << ", Y: " << sortedDimensions[i][j].Y / Unit << ";   "; 
		}
        cout << endl; 
	} 
	
	//cout << "S: " << sortedDimensions.size() << endl;
	//cout << "S0: " << sortedDimensions[0].size() << endl;
	
	return sortedDimensions;
}
/*
vector<vpii> splitToBoards( vector<vpii> sortedDimensions, pii boardSize )
{
	int sum = 0, i = 0;
	vector<vpii> board;
	while( !sortedDimensions.empty() ){
		if( sum + sortedDimensions[i]][0].Y < boardSize.Y ){
			board.push_back( sortedDimensions[i] );
			sortedDimensions.erase( sortedDimensions.begin() + i );
		}else {
			writeToFile( , board
		}
	}
}
*/
void writeToFile( string fileName, vpii objDimensions )
{
	pii boardSize( 3200 * Unit, 2100 * Unit );
	
	for( int i = 0; i < objDimensions.size(); ++i )
		objDimensions[i] = calcBoxSize( objDimensions[i] );
	
	vector<vpii> sortedDimensions = shelfPack( objDimensions, boardSize );
	
	ofstream outputFile;
	
	outputFile.open( fileName );
	outputFile << "IN;\nLT;\n"; //initialize file
	outputFile.close();
	
	pii origin( 0, 0 );
	
	for( int i = 0; i < sortedDimensions.size(); ++i ){
		cout << ".size: " << sortedDimensions.size() << endl;
		cout << "[i].size: " << sortedDimensions[i].size() << endl;
		for( int j = 0; j < sortedDimensions[i].size(); ++j ){
			cout << "S" << endl;
			tailor(
				fileName,
				origin,
				calcObjSize( sortedDimensions[i][j] ),
				packThk
			);
			cout << "origin.X: " << origin.X << " origin.Y: " << origin.Y << endl;
			origin.X += sortedDimensions[i][j].X;
		}
		origin.X = 0;
		origin.Y -= sortedDimensions[i][0].Y;
	}

	outputFile.open ( fileName, std::ios::app );
	outputFile << "SP0;\n";
	outputFile.close();
}