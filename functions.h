#include <utility>
#include <cstdlib>
#include <string>

using std::pair;
using std::string;
using std::vector;
using std::ofstream;

//function declarations go here
pii getValues( string line );

string getFileName( string filePath );

void getExtremes( int x, int y, vector<pii> & Extremes );

pii calculateSize( string fileName );

string line( int * originX, int * originY, int distanceX, int distanceY );

string lineX( int * originX, int * originY, int distanceX );

string lineY( int * originX, int * originY, int distanceY );

string move( int * originX, int * originY, int distanceX, int distanceY );

string moveX( int * originX, int * originY, int distanceX );

string moveY( int * originX, int * originY, int distanceY );

void tailor( string * outputFileName, pii origin, pair <int,int> size, int sizeZ );

void writeToFile( string fileName, vector<pii> & sourceDimensions );