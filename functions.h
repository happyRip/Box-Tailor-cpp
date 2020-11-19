#include <utility>
#include <cstdlib>
#include <string>

using std::pair;
using std::string;
using std::vector;
using std::ofstream;

//function declarations go here
pll getValues( string line );

string getFileName( string filePath );

void getExtremes( ll x, ll y, vector<pii> & Extremes );

pll calculateSize( string fileName );

string line( ll * originX, ll * originY, ll distanceX, ll distanceY );

string lineX( ll * originX, ll * originY, ll distanceX );

string lineY( ll * originX, ll * originY, ll distanceY );

string move( ll * originX, ll * originY, ll distanceX, ll distanceY );

string moveX( ll * originX, ll * originY, ll distanceX );

string moveY( ll * originX, ll * originY, ll distanceY );

void tailor( string * outputFileName, ll originX, ll originY, ll sizeX, ll sizeY, ll sizeZ );

void writeToFile( string fileName, vector<pll> & sourceDimensions );