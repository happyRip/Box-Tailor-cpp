#include <bits/stdc++.h>
#include <time.h>

//functions code goes here

//void tailor( double x, double y );

//string drawLine( double originX, double originY, double length, double angle );

int lessOrEqual( double * array, int n, double target ){ //binary search for a value less or equal to the target value in a sorted array
	int L = 0;
	int R = n - 1;
	
	while( L < R ){
		int M = ( L + R + 1 ) / 2;
		
		if( array[M] > target )
			R = M - 1;
		else
			L = M;
	}
	
	if( array[L] > target )
		return -1; //if no such value that is less or equal to the target value
	return L;
}

double getRand( double min, double max ){ //generates a random number between min and max values
	return ( max - min ) * ( (double)rand() / (double)RAND_MAX ) + min;
}