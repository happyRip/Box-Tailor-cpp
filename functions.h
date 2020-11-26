#include <utility>
#include <cstdlib>
#include <string>

using std::pair;
using std::string;
using std::vector;
using std::ofstream;

//function declarations go here

bool sortBySecond( const pii a, const pii b );

int area( pii box );

pii getValues( string line );

string getFileName( string filePath );

void getExtremes( int x, int y, vector<pii> & Extremes );

pii calculateSize( string fileName );

pii calcBoxSize( pii objDimensions );

pii calcObjSize( pii boxDimensions );

string line( pii & origin, pii distance );

string lineX( pii & origin, int distanceX );

string lineY( pii & origin, int distanceY );

string move( pii & origin, pii distance );

string moveX( pii & origin, int distanceX );

string moveY( pii & origin, int distanceY );

void tailor( string * outputFileName, pii origin, pair <int,int> size, int sizeZ );

int lessOrEqual( vector<pii> boxDimensions, int target, char argument );

vector<vpii> shelfPack( vector<pii> boxDimensions,  pii boardSize );

vector<vpii> splitToBoards( vector<vpii> sortedDimensions, pii boardSize );

void writeToFile( string fileName, vector<pii> boxDimensions );