#include <iostream>
#include <vector>

#define X 0
#define Y 1

using std::cin;
using std::cout;
using std::endl;
using std::vector;

unsigned int howManyObjects;
vector<double> sourceDimensions[2];


int main(){
	cout << "Wprowadz ilosc obiektow:" << endl;
	while( cin >> howManyObjects ){
		if( howManyObjects > 0 )
			break;
		else
			cout << "Wprowadzono nieprawidlowa ilosc obiektow.\nWprowadz ilosc obiektow:" << endl;
	}
	
	for( unsigned int i = 0; i < howManyObjects; ++i ){
		double tempX, tempY;
		
		cout << "Wprowadz wymiary obiektu ( x, y ):" << endl;
		cin >> tempX >> tempY;
		
		sourceDimensions[X].push_back( tempX );
		sourceDimensions[Y].push_back( tempY );
	}
	
	
}