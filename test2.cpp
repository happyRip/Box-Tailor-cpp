#include <bits/stdc++.h>
#include <time.h>
#include "functions.h"
#include "defines.h"

using namespace std;

int main()
{
	string fileName;
	cout << "Input the name of the file or path. ";
	cin >> fileName;
	
	ifstream inputFile;
	
	inputFile.open( fileName );
	
	string line;
	int maxX = INT_MIN, maxY = INT_MIN, minX = INT_MAX, minY = INT_MAX;
	while( getline( inputFile, line ) ){
		int tempX = 0, tempY = 0;
		bool second = false, anyNumb = false;
		//cout << line << endl;
		if( line[0] == 'P' ){
			for( int i = 0; i < line.length(); ++i ){
				if( isdigit( line[i] ) == false ){
					//cout << line[i] << endl;
					if( line[i] == ' ' && isdigit( line[i+1] ) )
						second = true;
						
					continue;
				}
				if( second == true ){
					tempY *= 10;
					tempY += ( line[i] - '0' );
				}else {
					tempX *= 10;
					tempX += ( line[i] - '0' );
				}
				//cout << "i: " << i << " n: " << line[i] << " tmpX: " << tempX << " tmpY: " << tempY << endl;
			}
			if( anyNumb = true ){			
				maxX = max( maxX, tempX );
				maxY = max( maxY, tempY );
				minX = min( minX, tempX );
				minY = min( minY, tempY );
				//cout << "maxX: " << maxX << " maxY: " << maxY << endl;
				//cout << "minX: " << minX << " minY: " << minY << endl;
			}
		}
	}
	
	cout << "X: " << ( maxX - minX ) / Unit << "mm\nY: " << ( maxY - minY ) / Unit << "mm\n";
	
	inputFile.close();
}