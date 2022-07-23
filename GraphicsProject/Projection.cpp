#include "Projection.h"

Vec4 get2d(Vec4 point) {
	return(scale(point, { 1 / point[2], 1 / point[2] , 1 , 1}));
}

