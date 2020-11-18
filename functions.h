#include <utility>
#include <cstdlib>
#include <string>

using std::pair;
using std::string;
using std::vector;
using std::ofstream;

//function declarations go here
pair<int,int> getValues( string line );

void getExtremes( int x, int y, vector<pii> & Extremes );

pair<int,int> calculateSize( string fileName );

string line( double * originX, double * originY, double distanceX, double distanceY );

string move( double * originX, double * originY, double distanceX, double distanceY );

void tailor( string * outputFileName, double originX, double originY, double sizeX, double sizeY, double sizeZ );

int lessOrEqual( double * array, int n, double target );

double getRand( double min, double max );