/**
* @file         bezier1.cpp
* @brief       	This is the header file which implments the CastelJau Algorithm program    
* @author       Shreeya, Gunpreet and Sriram
* @include      standard C++ libraries
*/
# include <iostream>
# include <bits/stdc++.h>

using namespace std;
/**
 *  Point struct
 *  @brief Structure for representation of Point
 * @detail Attributes: x and y coordinates
 */

struct Point {
	float x;
	float y;
};

// evaluate a Point on a bezier-curve. t goes from 0 to 1.0
// @param t 	 : at which t ranging from 0 - 1 , we need to find the Point 
// @return Point : returning the calculated the Point thorugh de castelau algorithm
/**
* @fn           CastelJau
* @brief        Function that evaluates a Point on a bezier-curve.
* @parameters   t : ranges from 0-1, total_cp :total number of conrol points, ControlPoints: structure of contro points,
*				arr: temporary structure
* @return type  Point (struct)
*/

Point CastelJau(const float t, int total_cp, Point *ControlPoints, Point *arr){
	for(int i=0;i<total_cp;i++){
		arr[i] = ControlPoints[i];
	}

	for (int k = 1; k < total_cp; k++) {
		for (int i = 0; i < total_cp - k; i++) {
			arr[i].x = (1 - t)* arr[i].x + t * arr[i + 1].x;
			arr[i].y = (1 - t)* arr[i].y + t * arr[i + 1].y;
		}
	}

	return arr[0];

}
