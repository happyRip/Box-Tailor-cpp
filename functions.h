#include <cstdlib>
#include <string>

using std::string;
using std::ofstream;

//function declarations go here

string line( double * originX, double * originY, double distanceX, double distanceY );

string move( double * originX, double * originY, double distanceX, double distanceY );

void tailor( string * outputFileName, double originX, double originY, double sizeX, double sizeY, double sizeZ );

int lessOrEqual( double * array, int n, double target );

double getRand( double min, double max );