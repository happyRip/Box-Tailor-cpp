#include <bits/stdc++.h>
#include <time.h>
#include "functions.h"

using namespace std;

double target, A[1000000];
int n, result;

int main()
{
	srand( time( NULL ) );
	
	cout << "How many?\n";
	cin >> n;
	
	cout << "Values:\n";
	for( int i = 0; i < n; ++i ){
		A[i] = getRand( 1, 500 );
	}	
	sort( A, A + n );
	
	for( int i = 0; i < n; ++i )
		cout << A[i] << " ";
	cout << endl;

	target = getRand( 1, 500 );
	cout << "The target is: " << target << endl;
	
	result = lessOrEqual( A, n, target );
	
	cout << "Your result is: " << A[result] << endl;
}