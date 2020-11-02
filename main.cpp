#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define X 0
#define Y 1
#define Unit 40 //40 units per mm, 1016 units per inch

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::vector;
using std::string;

unsigned int howManyObjects;
vector<double> sourceDimensions[2];

void tailor( double x, double y );
string drawLine( double originX, double originY, double length, double angle );

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
		
		cout << "Wprowadz wymiary obiektu ( x, y )[mm]:" << endl;
		cin >> tempX >> tempY;
		
		sourceDimensions[X].push_back( tempX * Unit );
		sourceDimensions[Y].push_back( tempY * Unit );
	}
//plik wynikowy	
	string outputFileName;
	cout << "Jak ma sie nazywac plik wynikowy?" << endl;
	cin >> outputFileName;
	
	ofstream outputFile;
	outputFile.open ( outputFileName );
	
	outputFile << "IN;\n";
	outputFile << "SP0;\n";
	
	outputFile << "PD" << sourceDimensions[X][0] << ",0;\n";
	outputFile << "PD" << sourceDimensions[X][0] << "," << sourceDimensions[Y][0] << ";\n";
	outputFile << "PD0," << sourceDimensions[Y][0] << ";\n";
	outputFile << "PD0,0;\n";
	
	outputFile << "PU;";
	
	outputFile.close();
}

string drawLine( double originX, double originY, double length, double angle )
{
	
}