#include <iostream>
#include <vector>

#define X 0
#define Y 1

using std::cin, std::cout, std::endl, std::vector;

unsigned int howManyObjects;
vector<vector<double> > sourceDimensions[2];


int main(){
	cout << "Wprowadź ilosc obiektow:" << endl;
	while( cin >> howManyObjects < 0 )
		cout << "Wprowadzona liczba jest mniejsza niz zero.\nWprowadz poprawna ilosc obiektow:" << endl;
	
	for( int i = 0; i < howManyObjects; ++i ){
		double tempX, tempY;
		
		cout << "Wprowadź wymiary obiektu ( x, y ):" << endl;
		cin >> tempX >> tempY;
		
		sourceDimensions[X].push_back( tempX );
		sourceDimensions[Y].push_back( tempY );
	}
	
	
}