#include <bits/stdc++.h>
#include <time.h>
#include "functions.h"
#include "defines.h"

using namespace std;

vector<pii> V;
vector<pii> FreeSquares;

bool sortBySecond( const pair<int,int> &x, const pair<int,int> &y );
int getRand(int a, int b);

int main()
{
	srand( time( 0 ) );
	
	cout << "How many rectangles?";
	int n;
	cin >> n;
	
	cout << "What are the dimensions of the board?";
	int boardDimensions[2];
	cin >> boardDimensions[X] >> boardDimensions[Y];
	
	for( int i = 0; i < n; ++i ){
		int tempX = getRand( 1, boardDimensions[X] * 2 / 3 );
		int tempY = getRand( tempX, boardDimensions[Y] * 2 / 3 );
		int temp = tempY;
		
		//tempY = max( tempX, tempY );
		//tempX = min( temp, tempX  );
		
		V.push_back( make_pair( tempX, tempY ) );
		
		//cout << "X: " << tempX << " Y: " << tempY << endl;
	}
	
	sort( V.begin(), V.end(), sortBySecond );
	
	cout << endl;
	
	for( int i = 0; i < n; i++ )
		cout << "X: " << V[i].first << " Y: " << V[i].second << endl;
	
	
}

bool sortBySecond( const pair<int,int> &V1, const pair<int,int> &V2 ){
	return( V1.second > V2.second );
}

int getRand( int a, int b ){
    return rand() % ( b - a + 1 ) + a;
}