#include "Projection.h"

Vector<2> get2d(Vector<4> point) {
	Vector<4> point2 = scale(point, { 1 / point[2], 1 / point[2] , 1 , 1});
	return(Vector<2>{point2[0], point2[1]});
}

