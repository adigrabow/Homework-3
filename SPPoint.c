/*
 * SPPoint.c
 *
 *  Created on: May 13, 2016
 *      Author: adigrabow
 */

#include "SPPoint.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


struct sp_point_t{
	double * data;
	int dim;
	int index;
};

SPPoint spPointCreate(double* data, int dim, int index){
	if(data == NULL || dim <= 0 || index <= 0){
		return NULL;
	}
	SPPoint point = (SPPoint) malloc(sizeof(struct sp_point_t)); /*allocate space for the new point*/
	if(point == NULL)
		return NULL;

	double* dataCopy = (double*) malloc(sizeof(double) * dim);
	memcpy(dataCopy, data, sizeof(double) * dim); /*copies info from 'data' to 'dataCopy'*/
	point->data = dataCopy;
	point->dim = dim;
	point->index = index;
	return point;

}

SPPoint spPointCopy(SPPoint source){
	assert(source != NULL);
	SPPoint target = malloc(sizeof(struct sp_point_t));
	if(target == NULL)
		return NULL;

	target = spPointCreate(source->data, source->dim, source->index);
	return target;

}


void spPointDestroy(SPPoint point){
	free(point->data);
	free(point);
}

int spPointGetDimension(SPPoint point){
	assert(point != NULL);
	return point->dim;
}

int spPointGetIndex(SPPoint point){
	assert(point != NULL);
	return point->index;
}

double spPointGetAxisCoor(SPPoint point, int axis){
	assert (point != NULL && axis < point->dim);
	return point->data[axis];
}

double spPointL2SquaredDistance(SPPoint p, SPPoint q){
	assert(p != NULL && q != NULL && p->dim == q->dim);
	double sum = 0;
	int i;
	for(i = 0; i < p->dim; i++){
		sum += pow((p->data[i] - q->data[i]),2);
	}
	return sum;

}
