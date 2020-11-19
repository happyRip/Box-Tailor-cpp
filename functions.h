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

string line( double * originX, double * originY, double distanceX, double distanceY );

string lineX( double * originX, double * originY, double distanceX );

string lineY( double * originX, double * originY, double distanceY );

string move( double * originX, double * originY, double distanceX, double distanceY );

string moveX( double * originX, double * originY, double distanceX );

string moveY( double * originX, double * originY, double distanceY );

void tailor( string * outputFileName, double originX, double originY, double sizeX, double sizeY, double sizeZ );

void writeToFile( string fileName, vector<pii> & sourceDimensions );

int lessOrEqual( double * array, int n, double target );

double getRand( double min, double max );